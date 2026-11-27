#include "client_lighting.h"
void __cdecl d3_ReleaseSceneResourceRef(void*);
void __cdecl d3_InvalidateFloorChunks(void*);

/* ADDRESS: GOLD 0x0043f990 */
void __cdecl d3_ResetFloorTileCache(void)
{
	unsigned int i;
	unsigned int offset;
	char* resource;
	char* base;
	char* fillDst;
	int fillCount;

	for (i = 0; i < *(unsigned int*) 0x633744; i++) {
		offset = i * 0x44;
		base = *(char**) 0x63374c;
		resource = *(char**) (base + offset);
		if (resource != 0) {
			if (*resource == '*') {
				while (*(int*) (resource + 0x40) > 0) {
					d3_ReleaseSceneResourceRef(resource);
					base = *(char**) 0x63374c;
					resource = *(char**) (base + offset);
				}
			}
			*(int*) (base + offset) = 0;
			base = *(char**) 0x63374c;
		}
		*(char*) (base + offset + 0x40) = 0;
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
		d3_InvalidateFloorChunks((void*) g_6b8300);
	for (offset = 0; offset < 0xf800; offset += 0x3e0) {
		resource = *(char**) (0xfd7c4c + offset);
		if (resource != 0 && resource != (char*) g_6b8300)
			d3_InvalidateFloorChunks(resource);
	}
}
