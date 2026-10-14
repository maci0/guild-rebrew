

#include "Develop/DieGildeAddOn/game/spiel.h"
void __cdecl m_FreeTracked(void*);

void __cdecl fcn_004be280(char* p)
{
	char* q;

	while (p != 0) {
		q = p;
		p = *(char**) (p + 0x3c);
		m_FreeTracked(q);
	}
}
