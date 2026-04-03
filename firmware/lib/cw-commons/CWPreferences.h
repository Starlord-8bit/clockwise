#pragma once

#include <Preferences.h>

#ifndef CW_PREF_DB_NAME
    #define CW_PREF_DB_NAME "clockwise"
#endif


struct ClockwiseParams
{
    Preferences preferences;

    const char* const PREF_SWAP_BLUE_GREEN = "swapBlueGreen";
    const char* const PREF_SWAP_BLUE_RED = "swapBlueRed";
    const char* const PREF_USE_24H_FORMAT = "use24hFormat";
    const char* const PREF_DISPLAY_BRIGHT = "displayBright";
    const char* const PREF_DISPLAY_ABC_MIN = "autoBrightMin";
    const char* const PREF_DISPLAY_ABC_MAX = "autoBrightMax";
    const char* const PREF_LDR_PIN = "ldrPin";
    const char* const PREF_TIME_ZONE = "timeZone";
    const char* const PREF_WIFI_SSID = "wifiSsid";
    const char* const PREF_WIFI_PASSWORD = "wifiPwd";
    const char* const PREF_NTP_SERVER = "ntpServer";
    const char* const PREF_CANVAS_FILE = "canvasFile";
    const char* const PREF_CANVAS_SERVER = "canvasServer";
    const char* const PREF_MANUAL_POSIX = "manualPosix";
    const char* const PREF_DISPLAY_ROTATION = "displayRotation";
    const char* const PREF_DRIVER = "driver";
    const char* const PREF_I2CSPEED = "i2cSpeed";
    const char* const PREF_E_PIN = "E_pin";
    // Multi-clockface dispatcher
    const char* const PREF_CLOCKFACE_INDEX = "clockfaceIdx";
    const char* const PREF_FACE_CONTROL    = "faceControl";
    const char* const PREF_AUTO_CHANGE     = "autoChange";
    // Multi-canvas slots (up to 5)
    const char* const PREF_CANVAS_COUNT    = "canvasCount";
    // canvasServer_N and canvasFile_N are built dynamically    

    bool swapBlueGreen;
    bool swapBlueRed;
    bool use24hFormat;
    uint8_t displayBright;
    uint16_t autoBrightMin;
    uint16_t autoBrightMax;
    uint8_t ldrPin;
    String timeZone;
    String wifiSsid;
    String wifiPwd;
    String ntpServer;
    String canvasFile;
    String canvasServer;
    String manualPosix;
    uint8_t displayRotation;
    uint8_t driver;
    uint32_t i2cSpeed;
    uint8_t E_pin;
    // Multi-clockface
    uint8_t  clockfaceIndex;   // 0-based active face
    String   faceControl;      // bitmask string e.g. "1111111" (1 bit per face)
    uint8_t  autoChange;       // 0=off, 1=sequence, 2=random
    // Multi-canvas slots
    uint8_t  canvasCount;      // how many canvas slots are configured (0-5)
    String   canvasSlotServer[5];
    String   canvasSlotFile[5]; 

    ClockwiseParams() {
        preferences.begin("clockwise", false); 
        //preferences.clear();
    }

    static ClockwiseParams* getInstance() {
        static ClockwiseParams base;
        return &base;
    }

   
    void save()
    {
        preferences.putBool(PREF_SWAP_BLUE_GREEN, swapBlueGreen);
        preferences.putBool(PREF_SWAP_BLUE_RED, swapBlueRed);
        preferences.putBool(PREF_USE_24H_FORMAT, use24hFormat);
        preferences.putUInt(PREF_DISPLAY_BRIGHT, displayBright);
        preferences.putUInt(PREF_DISPLAY_ABC_MIN, autoBrightMin);
        preferences.putUInt(PREF_DISPLAY_ABC_MAX, autoBrightMax);
        preferences.putUInt(PREF_LDR_PIN, ldrPin);        
        preferences.putString(PREF_TIME_ZONE, timeZone);
        preferences.putString(PREF_WIFI_SSID, wifiSsid);
        preferences.putString(PREF_WIFI_PASSWORD, wifiPwd);
        preferences.putString(PREF_NTP_SERVER, ntpServer);
        preferences.putString(PREF_CANVAS_FILE, canvasFile);
        preferences.putString(PREF_CANVAS_SERVER, canvasServer);
        preferences.putString(PREF_MANUAL_POSIX, manualPosix);
        preferences.putUInt(PREF_DISPLAY_ROTATION, displayRotation);
        preferences.putUInt(PREF_DRIVER, driver);
        preferences.putUInt(PREF_I2CSPEED, i2cSpeed);
        preferences.putUInt(PREF_E_PIN, E_pin);
        preferences.putUInt(PREF_CLOCKFACE_INDEX, clockfaceIndex);
        preferences.putString(PREF_FACE_CONTROL, faceControl);
        preferences.putUInt(PREF_AUTO_CHANGE, autoChange);
        preferences.putUInt(PREF_CANVAS_COUNT, canvasCount);
        for (uint8_t i = 0; i < 5; i++) {
            preferences.putString((String("canvasSrv_") + i).c_str(), canvasSlotServer[i]);
            preferences.putString((String("canvasFile_") + i).c_str(), canvasSlotFile[i]);
        }
    }

    void load()
    {
        swapBlueGreen = preferences.getBool(PREF_SWAP_BLUE_GREEN, false);
        swapBlueRed = preferences.getBool(PREF_SWAP_BLUE_RED, false);
        use24hFormat = preferences.getBool(PREF_USE_24H_FORMAT, true);
        displayBright = preferences.getUInt(PREF_DISPLAY_BRIGHT, 32);
        autoBrightMin = preferences.getUInt(PREF_DISPLAY_ABC_MIN, 0);
        autoBrightMax = preferences.getUInt(PREF_DISPLAY_ABC_MAX, 0);
        ldrPin = preferences.getUInt(PREF_LDR_PIN, 35);        
        timeZone = preferences.getString(PREF_TIME_ZONE, "America/Sao_Paulo");
        wifiSsid = preferences.getString(PREF_WIFI_SSID, "");
        wifiPwd = preferences.getString(PREF_WIFI_PASSWORD, "");
        ntpServer = preferences.getString(PREF_NTP_SERVER, "time.google.com");
        canvasFile = preferences.getString(PREF_CANVAS_FILE, "");
        canvasServer = preferences.getString(PREF_CANVAS_SERVER, "raw.githubusercontent.com");
        manualPosix = preferences.getString(PREF_MANUAL_POSIX, "");
        displayRotation = preferences.getUInt(PREF_DISPLAY_ROTATION, 0);
        driver = preferences.getUInt(PREF_DRIVER, 0);
        i2cSpeed = preferences.getUInt(PREF_I2CSPEED, (uint32_t)8000000);
        E_pin = preferences.getUInt(PREF_E_PIN, 18);
        clockfaceIndex = preferences.getUInt(PREF_CLOCKFACE_INDEX, 0);
        faceControl = preferences.getString(PREF_FACE_CONTROL, "1111111");  // all 7 enabled by default
        autoChange = preferences.getUInt(PREF_AUTO_CHANGE, 0);
        canvasCount = preferences.getUInt(PREF_CANVAS_COUNT, 0);
        for (uint8_t i = 0; i < 5; i++) {
            canvasSlotServer[i] = preferences.getString((String("canvasSrv_") + i).c_str(), "");
            canvasSlotFile[i]   = preferences.getString((String("canvasFile_") + i).c_str(), "");
        }
    }

};
