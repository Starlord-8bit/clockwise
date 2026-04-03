#include <Arduino.h>
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>

// Commons
#include <WiFiController.h>
#include <CWDateTime.h>
#include <CWPreferences.h>
#include <CWWebServer.h>
#include <StatusController.h>
#include <ClockfaceDispatcher.h>

#define MIN_BRIGHT_DISPLAY_ON 4
#define MIN_BRIGHT_DISPLAY_OFF 0

#define ESP32_LED_BUILTIN 2

MatrixPanel_I2S_DMA *dma_display = nullptr;

ClockfaceDispatcher *dispatcher = nullptr;

WiFiController wifi;
CWDateTime cwDateTime;

bool autoBrightEnabled;
long autoBrightMillis = 0;
uint8_t currentBrightSlot = -1;

// Auto-change: track last day to detect midnight rollover
int lastDay = -1;

bool isValidI2SSpeed(uint32_t speed) {
  return speed == 8000000 || speed == 16000000 || speed == 20000000;
}

bool isValidDriver(uint32_t drv) {
  return drv >= 0 && drv <= 5;
}

void displaySetup(bool swapBlueGreen, bool swapBlueRed, uint8_t displayBright, uint8_t displayRotation, uint8_t driver, uint32_t i2cSpeed, uint8_t E_pin)
{
  HUB75_I2S_CFG mxconfig(64, 64, 1);

  if (swapBlueGreen)
  {
    mxconfig.gpio.b1 = 26;
    mxconfig.gpio.b2 = 12;
    mxconfig.gpio.g1 = 27;
    mxconfig.gpio.g2 = 13;
  }

  if (swapBlueRed)
  {
    mxconfig.gpio.b1 = 25;
    mxconfig.gpio.b2 = 14;
    mxconfig.gpio.r1 = 27;
    mxconfig.gpio.r2 = 13;
  }

  mxconfig.gpio.e = E_pin;
  mxconfig.clkphase = false;

  if (isValidDriver(driver)) {
    mxconfig.driver = static_cast<HUB75_I2S_CFG::shift_driver>(driver);
  } else {
    Serial.printf("[ERROR] Invalid driver from config:%d\n", driver);
  }
  if (isValidI2SSpeed(i2cSpeed)) {
    mxconfig.i2sspeed = static_cast<HUB75_I2S_CFG::clk_speed>(i2cSpeed);
  } else {
    Serial.printf("[ERROR] Invalid I2S speed from config:%d\n", i2cSpeed);
  }

  dma_display = new MatrixPanel_I2S_DMA(mxconfig);
  dma_display->begin();
  dma_display->setBrightness8(displayBright);
  dma_display->clearScreen();
  dma_display->setRotation(displayRotation);
}

void automaticBrightControl()
{
  if (autoBrightEnabled) {
    if (millis() - autoBrightMillis > 3000)
    {
      int16_t currentValue = analogRead(ClockwiseParams::getInstance()->ldrPin);

      uint16_t ldrMin = ClockwiseParams::getInstance()->autoBrightMin;
      uint16_t ldrMax = ClockwiseParams::getInstance()->autoBrightMax;

      const uint8_t minBright = (currentValue < ldrMin ? MIN_BRIGHT_DISPLAY_OFF : MIN_BRIGHT_DISPLAY_ON);
      uint8_t maxBright = ClockwiseParams::getInstance()->displayBright;

      uint8_t slots = 10;
      uint8_t mapLDR = map(currentValue > ldrMax ? ldrMax : currentValue, ldrMin, ldrMax, 1, slots);
      uint8_t mapBright = map(mapLDR, 1, slots, minBright, maxBright);

      if (abs(currentBrightSlot - mapLDR) >= 2 || mapBright == 0) {
        dma_display->setBrightness8(mapBright);
        currentBrightSlot = mapLDR;
      }
      autoBrightMillis = millis();
    }
  }
}

void autoChangeClockfaceCheck()
{
  uint8_t mode = ClockwiseParams::getInstance()->autoChange;
  if (mode == 0) return;  // AUTO_CHANGE_OFF

  int today = cwDateTime.getDay();
  if (lastDay == -1) {
    lastDay = today;
    return;
  }
  if (today == lastDay) return;

  lastDay = today;

  // Build list of enabled face indices from faceControl bitmask
  String fc = ClockwiseParams::getInstance()->faceControl;
  uint8_t total = dispatcher->getAvailableCount();
  std::vector<uint8_t> enabled;
  for (uint8_t i = 0; i < total && i < (uint8_t)fc.length(); i++) {
    if (fc.charAt(i) == '1') enabled.push_back(i);
  }
  if (enabled.empty()) return;

  uint8_t current = ClockwiseParams::getInstance()->clockfaceIndex;
  uint8_t next;

  if (mode == 1) {
    // Sequence: find current in enabled list, pick next
    uint8_t pos = 0;
    for (uint8_t i = 0; i < enabled.size(); i++) {
      if (enabled[i] == current) { pos = i; break; }
    }
    next = enabled[(pos + 1) % enabled.size()];
  } else {
    // Random: avoid same face
    do {
      next = enabled[random(enabled.size())];
    } while (next == current && enabled.size() > 1);
  }

  ClockwiseParams::getInstance()->clockfaceIndex = next;
  ClockwiseParams::getInstance()->save();
  dispatcher->setIndex(next);
}

void setup()
{
  Serial.begin(115200);
  pinMode(ESP32_LED_BUILTIN, OUTPUT);

  StatusController::getInstance()->blink_led(5, 100);

  ClockwiseParams::getInstance()->load();

  pinMode(ClockwiseParams::getInstance()->ldrPin, INPUT);

  uint8_t driver    = ClockwiseParams::getInstance()->driver;
  uint32_t i2cSpeed = ClockwiseParams::getInstance()->i2cSpeed;
  uint8_t E_pin     = ClockwiseParams::getInstance()->E_pin;

  displaySetup(
    ClockwiseParams::getInstance()->swapBlueGreen,
    ClockwiseParams::getInstance()->swapBlueRed,
    ClockwiseParams::getInstance()->displayBright,
    ClockwiseParams::getInstance()->displayRotation,
    driver, i2cSpeed, E_pin
  );

  // Set up dispatcher with all compiled clockfaces
  dispatcher = new ClockfaceDispatcher(dma_display);

  // Register canvas slots
  uint8_t canvasCount = ClockwiseParams::getInstance()->canvasCount;
  for (uint8_t i = 0; i < canvasCount && i < 5; i++) {
    dispatcher->setCanvasSlot(
      i,
      ClockwiseParams::getInstance()->canvasSlotServer[i],
      ClockwiseParams::getInstance()->canvasSlotFile[i]
    );
  }

  autoBrightEnabled = (ClockwiseParams::getInstance()->autoBrightMax > 0);

  StatusController::getInstance()->clockwiseLogo();
  delay(1000);

  StatusController::getInstance()->wifiConnecting();
  if (wifi.begin())
  {
    StatusController::getInstance()->ntpConnecting();
    cwDateTime.begin(
      ClockwiseParams::getInstance()->timeZone.c_str(),
      ClockwiseParams::getInstance()->use24hFormat,
      ClockwiseParams::getInstance()->ntpServer.c_str(),
      ClockwiseParams::getInstance()->manualPosix.c_str()
    );

    dispatcher->begin(&cwDateTime);
    dispatcher->setIndex(ClockwiseParams::getInstance()->clockfaceIndex);
  }
}

void loop()
{
  wifi.handleImprovWiFi();

  if (wifi.isConnected())
  {
    ClockwiseWebServer::getInstance()->handleHttpRequest();
    ezt::events();
  }

  if (wifi.connectionSucessfulOnce)
  {
    dispatcher->update();
  }

  automaticBrightControl();
  autoChangeClockfaceCheck();
}
