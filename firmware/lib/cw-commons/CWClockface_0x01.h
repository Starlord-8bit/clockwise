#pragma once
/**
 * CWClockface_0x01.h — Adapter for  clockface (cw-cf-0x01)
 * Renames Clockface -> CWClockface_0x01 to avoid ODR violations when
 * all clockfaces are compiled together.
 */
#ifndef CW_CF_0x01_INCLUDED
#define CW_CF_0x01_INCLUDED
#define Clockface CWClockface_0x01
#include <cw-cf-0x01/Clockface.h>
#undef Clockface
#endif
