

#include "Develop/DieGildeAddOn/game/spiel.h"
void __cdecl m_FreeTracked(void*);

/* ADDRESS: GOLDDE 0x004abe00 */
void __cdecl rt_FreeRoutePoints(char* p)
{
	char* q;

	while (p != 0) {
		q = p;
		p = *(char**) (p + 0x3c);
		m_FreeTracked(q);
	}
}
