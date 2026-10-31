#include <string.h>

extern int* g_772f40;

void __cdecl fcn_004c4330(void* p);
char* __cdecl gm_LookupEntityRecordIn32SlotTable(int id);

/* ADDRESS: GOLDTL 0x004c6940 */
void __cdecl fcn_004c6940(void* a0, int a1, void* a2)
{
	char buf[0x9c];
	char* p;
	char* q;
	char* r;

	*(int*) (buf + 0x10) = *g_772f40;
	buf[0] = 0x55;
	buf[0x14] = (char) a1;
	memcpy(buf + 0x35, a2, 0x2c);
	if (a0 != 0) {
		p = *(char**) ((char*) a0 + 0x184);
		if (p != 0) {
			q = *(char**) (p + 0x34);
			*(int*) (buf + 0x15) = *(int*) (q + 0x4c);
			*(int*) (buf + 0x31) = *(int*) ((char*) a0 + 0x24);
			*(int*) (buf + 0x19) = *(int*) (q + 0x50);
			*(int*) (buf + 0x1d) = *(int*) (q + 0x54);
			*(int*) (buf + 0x25) = *(int*) (q + 0x84);
			*(int*) (buf + 0x29) = *(int*) (q + 0x88);
			*(int*) (buf + 0x2d) = *(int*) (q + 0x8c);
			if (a1 == 2) {
				r = gm_LookupEntityRecordIn32SlotTable(*(int*) (buf + 0x45));
				if (r != 0) {
					*(int*) (buf + 0x5d) = *(int*) (r + 0x24);
				}
			}
		}
	}
	fcn_004c4330(buf);
}
