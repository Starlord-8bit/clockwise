#pragma once
/**
 * CWClockface_0x03.h — Adapter for TimeInWords clockface (cw-cf-0x03)
 * Renames Clockface -> CWClockface_0x03 to avoid ODR violations when
 * all clockfaces are compiled together.
 */
#ifndef CW_CF_0x03_INCLUDED
#define CW_CF_0x03_INCLUDED
#define Clockface CWClockface_0x03
#include <cw-cf-0x03/Clockface.h>
#undef Clockface
#endif
