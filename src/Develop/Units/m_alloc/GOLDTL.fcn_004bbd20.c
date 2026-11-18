#include "Develop/DieGildeAddOn/game/ambient_animal_slot.h"


void* __cdecl m_alloc(int, void*);

void __cdecl fcn_004bbd20(void)
{
	void* p;

	p = m_alloc(0x2480, (void*) 0x6813d0);
	g_7728e8 = (AMBIENT_ANIMAL_SLOT*) p;
	*(int*) 0x7728e4 = 0;
	((AMBIENT_ANIMAL_SLOT*) p)->objekt = 0;
}
