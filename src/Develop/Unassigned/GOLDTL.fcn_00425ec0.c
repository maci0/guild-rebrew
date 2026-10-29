#include <string.h>

void __cdecl fcn_00425bf0(char* obj, int level, char* msg);
char* __cdecl fcn_00428720(char* obj);

/* ADDRESS: GOLDTL 0x00425ec0 */
char* __cdecl fcn_00425ec0(char* obj, int mode, int size, char* name)
{
	int* slot;
	char* rec = 0;
	int i;
	int sz;
	int hdr;

	i = 0;
	sz = 0;
	slot = (int*) (*(char**) (obj + 0xc28) + 0x10);
	while (*slot != 0) {
		i++;
		slot++;
		if (i >= 8) {
			fcn_00425bf0(obj, *(int*) (obj + 0x118) - 1, (char*) 0x67921c);
			return rec;
		}
	}
	if (mode == 1) {
		sz = 4;
	}
	else if (mode == 2) {
		sz = 1;
	}
	else if (mode == 7) {
		sz = 4;
	}
	else if (mode == 6) {
		sz = 0x60;
	}
	else {
		__asm { int 3 }
	}
	rec = *(char**) (obj + 0xc38);
	*(int*) (rec + 0x24) = size;
	*(int*) (rec + 0x28) = 1;
	*(char**) (rec + 0x2c) = rec + 0x30;
	hdr = *(int*) rec;
	*(int*) rec = (hdr ^ mode) & 0xf ^ hdr;
	strcpy(rec + 4, name);
	sz = sz * size + 0x30;
	*(int*) (obj + 0xc38) += sz;
	if (*(unsigned int*) (obj + 0xc38) > *(unsigned int*) (obj + 0xc34) + 0x400) {
		fcn_00425bf0(obj, *(int*) (obj + 0x118), (char*) 0x67920c);
		fcn_00428720(obj);
	}
	*(char**) (*(char**) (obj + 0xc28) + 0x10 + i * 4) = rec;
	return rec;
}
