#include "Develop/Units/m_alloc/m_alloc.h"

/* ADDRESS: GOLD 0x004ebf60 */
void __cdecl fcn_004ebf60(void)
{
	if (*(int*) 0x6f0e2c != 0) {
		m_FreeTracked((void*) *(int*) 0x6f0e2c);
		*(int*) 0x6f0e2c = 0;
	}
	if (*(int*) 0x6f0e34 != 0) {
		m_FreeTracked((void*) *(int*) 0x6f0e34);
		*(int*) 0x6f0e34 = 0;
	}
	*(int*) 0x6f0e30 = 0;
	*(int*) 0x6f0e28 = 0;
}
