#pragma once
/**
 * CWClockface_0x07.h — Adapter for Canvas clockface (cw-cf-0x07)
 *
 * Canvas is special: it reads canvasServer + canvasFile from CWPreferences
 * at setup() time. For multi-canvas slots, we subclass and override those
 * values so each slot can point at a different file.
 */
#ifndef CW_CF_0x07_INCLUDED
#define CW_CF_0x07_INCLUDED

#define Clockface CWClockface_0x07_Base
#include <cw-cf-0x07/Clockface.h>
#undef Clockface

#include <CWPreferences.h>

/**
 * CWClockface_0x07 — Canvas clockface with optional server/file override.
 *
 * When constructed with empty strings, behaves exactly like the original
 * (reads from CWPreferences). When constructed with explicit server/file,
 * those override the global prefs — enabling multiple independent Canvas
 * slots pointing at different JSON files.
 */
class CWClockface_0x07 : public CWClockface_0x07_Base {
public:
    CWClockface_0x07(Adafruit_GFX* display,
                     const String& serverOverride = "",
                     const String& fileOverride   = "")
        : CWClockface_0x07_Base(display),
          _serverOverride(serverOverride),
          _fileOverride(fileOverride)
    {}

    void setup(CWDateTime* dt) override {
        // If overrides are set, temporarily patch CWPreferences so the base
        // class picks them up during setup(). Restore afterwards.
        String savedServer, savedFile;
        bool hasOverride = (_serverOverride.length() > 0 && _fileOverride.length() > 0);

        if (hasOverride) {
            savedServer = ClockwiseParams::getInstance()->canvasServer;
            savedFile   = ClockwiseParams::getInstance()->canvasFile;
            ClockwiseParams::getInstance()->canvasServer = _serverOverride;
            ClockwiseParams::getInstance()->canvasFile   = _fileOverride;
        }

        CWClockface_0x07_Base::setup(dt);

        if (hasOverride) {
            ClockwiseParams::getInstance()->canvasServer = savedServer;
            ClockwiseParams::getInstance()->canvasFile   = savedFile;
        }
    }

private:
    String _serverOverride;
    String _fileOverride;
};

#endif // CW_CF_0x07_INCLUDED
