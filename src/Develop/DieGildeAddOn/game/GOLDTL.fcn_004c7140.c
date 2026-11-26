#include "Develop/DieGildeAddOn/game/spiel.h"
int __cdecl cm_ResolveSpecialEntityId(char*, int);

char* __cdecl gm_LookupEntityRecordById(int);


/* ADDRESS: GOLDTL 0x004c7140 */
int __cdecl cm_ValidateAttributeDelta(unsigned char* packet)
{
	char* stat;
	unsigned int k;
	char* dyn;
	char* exist;
	char* base;
	char* e;
	unsigned char* p;
	char* addr;
	int size;
	unsigned int n;
	unsigned int j;

	*(int*) (packet + 0x10) = cm_ResolveSpecialEntityId((char*) packet, *(int*) (packet + 0x10));
	if (gm_ResolveEntityById((void**) (&dyn), (void**) (&exist), (void**) (&stat), *(int*) (packet + 0x10)) == 0)
		return 1;
	if (dyn != 0)
		base = dyn;
	else if (exist != 0)
		base = exist;
	else
		base = stat;
	p = packet + 0x15;
	for (k = 0; k < packet[0x14]; k++) {
		size = (signed char) *p++;
		n = (signed char) *p++;
		addr = base + *(unsigned short*) p;
		p += 2;
		if (stat != 0) {
			if (addr == stat + 4)
				return 1;
			if (addr == stat + 0x5c) {
				addr = (char*) *(int*) p;
				addr += *(int*) (stat + 0x5c);
				e = gm_LookupEntityRecordById((int) addr);
				if (e == 0)
					return 1;
				if (*(int*) (e + 0x5c) != -1 && *(int*) (e + 0x5c) != *(int*) (stat + 4))
					return 1;
			}
		}
		switch (size) {
		case 1:
			for (j = 0; j < n; j++)
				p++;
			break;
		case 2:
			for (j = 0; j < n; j++)
				p += 2;
			break;
		case 4:
			for (j = 0; j < n; j++)
				p += 4;
			break;
		}
	}
	return 0;
}
