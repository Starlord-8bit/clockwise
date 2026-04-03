#pragma once
/**
 * CWClockface_0x02.h — Adapter for Mario clockface (cw-cf-0x02)
 * Renames Clockface -> CWClockface_0x02 to avoid ODR violations when
 * all clockfaces are compiled together.
 */
#ifndef CW_CF_0x02_INCLUDED
#define CW_CF_0x02_INCLUDED
#define Clockface CWClockface_0x02
#include <cw-cf-0x02/Clockface.h>
#undef Clockface
#endif
