#pragma once

/**
 * ClockfaceDispatcher — runtime clockface selection for Clockwise
 *
 * Wraps each compiled-in clockface inside a unique namespace to resolve
 * the linker collision (every clockface defines `class Clockface`).
 *
 * Usage:
 *   ClockfaceDispatcher dispatcher(dma_display);
 *   dispatcher.begin(&cwDateTime);
 *   dispatcher.setIndex(0);          // select by 0-based index
 *   dispatcher.update();             // call in loop()
 *
 * Clockface index mapping (matches web UI 1-based numbering, stored as 0-based):
 *   0 = Super Mario   (cw-cf-0x01)
 *   1 = Time in Words (cw-cf-0x02)
 *   2 = World Map     (cw-cf-0x03)
 *   3 = Castlevania   (cw-cf-0x04)
 *   4 = Pac-Man       (cw-cf-0x05)
 *   5 = Pokedex       (cw-cf-0x06)
 *   6 = Canvas        (cw-cf-0x07)  -- slots 6..10 for multi-canvas
 */

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include "IClockface.h"
#include "CWDateTime.h"

// ─── Namespace-wrap each clockface header ────────────────────────────────────
// Each repo defines `class Clockface : public IClockface`.
// We include them inside unique namespaces to avoid ODR violations.

namespace CF_Mario {
  #include <Clockface.h>   // cw-cf-0x01 must be first in INCLUDE path
}
// Note: because each clockface is in its own component directory,
// the build system resolves #include <Clockface.h> to the correct file
// per component. However, to include *all* simultaneously we need
// per-component wrapper headers. See CWClockface_*.h files below.

// ─── Per-clockface thin wrapper headers ──────────────────────────────────────
// Each CWClockface_N.h re-exports the face under a stable interface.
// These are generated/maintained in this directory.

#include "CWClockface_0x01.h"
#include "CWClockface_0x02.h"
#include "CWClockface_0x03.h"
#include "CWClockface_0x04.h"
#include "CWClockface_0x05.h"
#include "CWClockface_0x06.h"
#include "CWClockface_0x07.h"

// ─── Max Canvas slots ─────────────────────────────────────────────────────────
#define CW_MAX_CANVAS_SLOTS 5
#define CW_HARDCODED_FACES  6
#define CW_TOTAL_FACES      (CW_HARDCODED_FACES + CW_MAX_CANVAS_SLOTS)

class ClockfaceDispatcher {
public:
    ClockfaceDispatcher(Adafruit_GFX* display) : _display(display), _active(nullptr), _index(0) {}

    void begin(CWDateTime* dt) {
        _dt = dt;
        _faces[0] = new CWClockface_0x01(_display);
        _faces[1] = new CWClockface_0x02(_display);
        _faces[2] = new CWClockface_0x03(_display);
        _faces[3] = new CWClockface_0x04(_display);
        _faces[4] = new CWClockface_0x05(_display);
        _faces[5] = new CWClockface_0x06(_display);
        // Canvas slots 6..10 are instantiated dynamically via setCanvasSlot()
        for (int i = CW_HARDCODED_FACES; i < CW_TOTAL_FACES; i++) {
            _faces[i] = nullptr;
        }
        setIndex(0);
    }

    /** Set canvas slot (0-based slot within canvas slots, so global index = slot + 6) */
    void setCanvasSlot(uint8_t slot, const String& server, const String& file) {
        if (slot >= CW_MAX_CANVAS_SLOTS) return;
        uint8_t globalIdx = CW_HARDCODED_FACES + slot;
        delete _faces[globalIdx];
        _faces[globalIdx] = new CWClockface_0x07(_display, server, file);
    }

    void setIndex(uint8_t index) {
        if (index >= CW_TOTAL_FACES) return;
        if (_faces[index] == nullptr) return;
        _index = index;
        _active = _faces[index];
        _active->setup(_dt);
    }

    void update() {
        if (_active) _active->update();
    }

    uint8_t getIndex() const { return _index; }
    uint8_t getCount() const { return CW_TOTAL_FACES; }

    /** Count of actually available faces (non-null) */
    uint8_t getAvailableCount() const {
        uint8_t count = 0;
        for (int i = 0; i < CW_TOTAL_FACES; i++) {
            if (_faces[i] != nullptr) count++;
        }
        return count;
    }

private:
    Adafruit_GFX*   _display;
    CWDateTime*     _dt;
    IClockface*     _active;
    IClockface*     _faces[CW_TOTAL_FACES] = {};
    uint8_t         _index;
};
