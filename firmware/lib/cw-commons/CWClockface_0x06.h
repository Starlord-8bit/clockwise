#pragma once
/**
 * CWClockface_0x06.h — Adapter for PacMan clockface (cw-cf-0x06)
 * Renames Clockface -> CWClockface_0x06 to avoid ODR violations when
 * all clockfaces are compiled together.
 */
#ifndef CW_CF_0x06_INCLUDED
#define CW_CF_0x06_INCLUDED
#define Clockface CWClockface_0x06
#include <cw-cf-0x06/Clockface.h>
#undef Clockface
#endif
