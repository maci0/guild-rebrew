


// SIZE 0x194
typedef struct {
	char pad0[9];
	char kind;
	char pada[0xf4 - 0xa];
	void* data;
	char padf8[0x194 - 0xf8];
} Slot;

extern void* g_6b5c5c;
char* tp_ch_ActionQueue = 0;
#include "Develop/DieGildeAddOn/game/game_data.h"
void __cdecl ch_FreeMap(void* p);
void __cdecl m_FreeTracked(void* p);
void __cdecl ch_DestroyCharacter(char* e);

/* ADDRESS: GOLDDE 0x0040aed0 */
void __cdecl ch_ShutdownCharacters(void)
{
	int i;
	char** p;
	void** d;

	if (g_6b5c5c != 0) {
		ch_FreeMap(g_6b5c5c);
	}
	if ((*(Slot**)&tp_ch_ActionQueue) != 0) {
		for (i = 0; i < 2000; i++) {
			if ((*(Slot**)&tp_ch_ActionQueue)[i].kind == 0x2d && (*(Slot**)&tp_ch_ActionQueue)[i].data != 0) {
				d = &(*(Slot**)&tp_ch_ActionQueue)[i].data;
				m_FreeTracked(*d);
				*d = 0;
			}
		}
	}
	p = ((char**)ch_CharacterSlots);
	do {
		if (*p != 0) {
			ch_DestroyCharacter(*p);
		}
		p++;
	} while ((int) p < (int) &((char**)ch_CharacterSlots)[0x300]);
	if ((*(Slot**)&tp_ch_ActionQueue) != 0) {
		m_FreeTracked((*(Slot**)&tp_ch_ActionQueue));
		(*(Slot**)&tp_ch_ActionQueue) = 0;
	}
}
