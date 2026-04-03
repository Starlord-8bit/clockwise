#pragma once
/**
 * CWClockface_0x04.h — Adapter for WorldMap clockface (cw-cf-0x04)
 * Renames Clockface -> CWClockface_0x04 to avoid ODR violations when
 * all clockfaces are compiled together.
 */
#ifndef CW_CF_0x04_INCLUDED
#define CW_CF_0x04_INCLUDED
#define Clockface CWClockface_0x04
#include <cw-cf-0x04/Clockface.h>
#undef Clockface
#endif
