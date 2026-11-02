#include "Develop/DieGildeAddOn/game/ch_action.h"

/* TL character helper, not a command handler. Clears the sitting flag
 * (bit 0x10 of the byte at +0x8c, the bit CharacterSitting returns) and
 * releases the seat object held at +0x74. The name is inferred; no string
 * names this function. */

void __cdecl fcn_00402aa0(void*);
void __cdecl fcn_00435500(char*, char*);

void __cdecl ch_ClearSitting(unsigned char* ch)
{
	unsigned char* p;
	int* ent;
	char* q;

	if ((ch[0x8c] & 0x10) != 0) {
		p = *(unsigned char**) (ch + 0x74);
		if (p != 0) {
			if ((*(int**) (ch + 0x34))[0x73] == 0)
				fcn_00402aa0(ch);
			p = *(unsigned char**) (ch + 0x74);
			ent = *(int**) (ch + 0x34);
			q = *(char**) (p + 0x68);
			if (q != 0)
				fcn_00435500((char*) ent[0x7b] + 0xf4, q);
			*(void**) (ch + 0x74) = 0;
		}
		ch[0x8c] &= 0xef;
	}
}
