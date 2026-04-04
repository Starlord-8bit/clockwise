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
    // Night mode strategy
    const char* const PREF_NIGHT_MODE    = "nightMode";    // 0=nothing, 1=off, 2=big clock
    const char* const PREF_NIGHT_LEVEL   = "nightLevel";   // brightness 1-5 during night (used by nightMode=2)
    const char* const PREF_SUPER_COLOR   = "superColor";   // RGB565 color for big clock digits
    // Night schedule (start/end hours for night window)
    const char* const PREF_NIGHT_START_H = "nightStartH";
    const char* const PREF_NIGHT_START_M = "nightStartM";
    const char* const PREF_NIGHT_END_H   = "nightEndH";
    const char* const PREF_NIGHT_END_M   = "nightEndM";
    // Big clock canvas server (where bigclock.json is served from)
    const char* const PREF_BIGCLOCK_SERVER = "bigclockSrv";
    const char* const PREF_BIGCLOCK_FILE   = "bigclockFile";    

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
    // Night mode
    uint8_t  nightMode;      // 0=nothing, 1=display off, 2=big clock
    uint8_t  nightLevel;     // 1-5 brightness level during night (nightMode=2)
    uint16_t superColor;     // RGB565 color for big clock digits (default: dark white 16936)
    uint8_t  nightStartH;   
    uint8_t  nightStartM;
    uint8_t  nightEndH;
    uint8_t  nightEndM;
    String   bigclockServer; // server hosting bigclock.json
    String   bigclockFile;   // filename (without .json) 

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
        preferences.putUInt(PREF_NIGHT_MODE, nightMode);
        preferences.putUInt(PREF_NIGHT_LEVEL, nightLevel);
        preferences.putUInt(PREF_SUPER_COLOR, superColor);
        preferences.putUInt(PREF_NIGHT_START_H, nightStartH);
        preferences.putUInt(PREF_NIGHT_START_M, nightStartM);
        preferences.putUInt(PREF_NIGHT_END_H, nightEndH);
        preferences.putUInt(PREF_NIGHT_END_M, nightEndM);
        preferences.putString(PREF_BIGCLOCK_SERVER, bigclockServer);
        preferences.putString(PREF_BIGCLOCK_FILE, bigclockFile);
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
        nightMode    = preferences.getUInt(PREF_NIGHT_MODE, 0);       // default: nothing
        nightLevel   = preferences.getUInt(PREF_NIGHT_LEVEL, 1);      // dimmest
        superColor   = preferences.getUInt(PREF_SUPER_COLOR, 16936);  // dark white
        nightStartH  = preferences.getUInt(PREF_NIGHT_START_H, 22);
        nightStartM  = preferences.getUInt(PREF_NIGHT_START_M, 0);
        nightEndH    = preferences.getUInt(PREF_NIGHT_END_H, 7);
        nightEndM    = preferences.getUInt(PREF_NIGHT_END_M, 0);
        bigclockServer = preferences.getString(PREF_BIGCLOCK_SERVER, "raw.githubusercontent.com");
        bigclockFile   = preferences.getString(PREF_BIGCLOCK_FILE, "Starlord-8bit/clockwise/main/clockfaces/bigclock");
    }

};
