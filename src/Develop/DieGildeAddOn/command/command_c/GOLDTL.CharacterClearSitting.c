#include "../command_internal.h"

/* TL character helper, not a command handler. Clears the sitting flag
 * (bit 0x10 of the byte at +0x8c, the bit CharacterSitting returns) and
 * releases the seat object held at +0x74. The name is inferred; no string
 * names this function. */

void* __cdecl fcn_00402aa0(void*);
void __cdecl fcn_00435500(void*, void*);

void __cdecl CharacterClearSitting(unsigned char* ch)
{
	unsigned char* p;
	int* ent;
	void* q;

	if ((ch[0x8c] & 0x10) != 0) {
		p = *(unsigned char**) (ch + 0x74);
		if (p != 0) {
			ent = *(int**) (ch + 0x34);
			if (ent[0x73] == 0)
				p = fcn_00402aa0(ch);
			q = *(void**) (p + 0x68);
			if (q != 0)
				fcn_00435500(q, (void*) (ent[0x7b] + 0xf4));
			*(void**) (ch + 0x74) = 0;
		}
		ch[0x8c] &= 0xef;
	}
}
