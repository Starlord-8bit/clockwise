#pragma once
/**
 * CWClockface_0x05.h — Adapter for Castlevania clockface (cw-cf-0x05)
 * Renames Clockface -> CWClockface_0x05 to avoid ODR violations when
 * all clockfaces are compiled together.
 */
#ifndef CW_CF_0x05_INCLUDED
#define CW_CF_0x05_INCLUDED
#define Clockface CWClockface_0x05
#include <cw-cf-0x05/Clockface.h>
#undef Clockface
#endif
