#include "client_lighting.h"
void __cdecl fcn_0045fbb0(void*);
void __cdecl fcn_00440140(void*);

/* ADDRESS: GOLD 0x0043f990 */
void __cdecl fcn_0043f990(void)
{
	unsigned int i;
	int offset;
	char* resource;
	char* fillDst;
	int fillCount;

	for (i = 0, offset = 0; i < *(unsigned int*) 0x633744; i++, offset += 0x44) {
		resource = *(char**) (*(char**) 0x63374c + offset);
		if (resource != 0) {
			if (*resource == '*') {
				while (*(int*) (resource + 0x40) > 0) {
					fcn_0045fbb0(resource);
					resource = *(char**) (*(char**) 0x63374c + offset);
				}
			}
			*(int*) (*(char**) 0x63374c + offset) = 0;
		}
		*(char*) (*(char**) 0x63374c + offset + 0x40) = 0;
		*(int*) (*(char**) 0x63374c + offset + 4) = 0;
		*(int*) (*(char**) 0x63374c + offset + 8) = 0;
		*(int*) (*(char**) 0x63374c + offset + 0xc) = 0;
		fillCount = 0x19;
		fillDst = *(char**) 0x63374c + offset + 0x24;
		__asm {
			mov edi, fillDst
			mov ebx, fillCount
			xor eax, eax
			lea ecx, [edi+edi*2]
			and ecx, 3
			sub ebx, ecx
			jle short ClearFillTail
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		ClearFillTail:
			add ecx, ebx
			rep stosb
		}
	}
	if ((void*) g_6b8300 != 0)
		fcn_00440140((void*) g_6b8300);
	for (offset = 0; offset < 0xf800; offset += 0x3e0) {
		resource = *(char**) (0xfd7c4c + offset);
		if (resource != 0 && resource != (char*) g_6b8300)
			fcn_00440140(resource);
	}
}
