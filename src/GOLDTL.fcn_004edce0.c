// FUNCTION: GOLDTL 0x4edce0

#include "g_772f90.h"

extern int g_772fd8;
extern Draw772* g_772fdc;
extern int g_772fe0;
extern Rec772fe4* g_772fe4;

void __cdecl m_FreeTracked(int);

void __cdecl fcn_004edce0(void)
{
	if (g_772fdc != 0) {
		m_FreeTracked((int) g_772fdc);
		g_772fdc = 0;
	}
	if (g_772fe4 != 0) {
		m_FreeTracked((int) g_772fe4);
		g_772fe4 = 0;
	}
	g_772fe0 = 0;
	g_772fd8 = 0;
}
