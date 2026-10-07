// FUNCTION: GOLD 0x4cdf00
// FUNCTION: GOLDTL 0x4ceac0

#include <string.h>

typedef struct {
	int id;
	int f4;
	char pad8[0x24];
} ent2c;
// SIZE 0x2c

typedef struct {
	char pad0[0x94];
	ent2c slots[16];
} rec35c;
// SIZE 0x3d4

ent2c* __cdecl fcn_004ceac0(rec35c* rec, char* e)
{
	int i;

	for (i = 0; i < 16; i++) {
		if (rec->slots[i].id == *(int*) (e + 4))
			return &rec->slots[i];
	}
	for (i = 0; i < 16; i++) {
		if (rec->slots[i].id == -1) {
			memset(&rec->slots[i], 0, sizeof(ent2c));
			rec->slots[i].id = *(int*) (e + 4);
			rec->slots[i].f4 = 0;
			return &rec->slots[i];
		}
	}
	return 0;
}
