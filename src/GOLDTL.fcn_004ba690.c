#include <string.h>

typedef struct {
	char x0[2];
	char kind;
	char pad3[0x169];
	char* owner;
	char pad170[0xac];
} Ent;
// SIZE 0x21c

extern Ent g_7f4ca0[];

unsigned short* __cdecl fcn_00508e40(int);
unsigned char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
unsigned char* __cdecl gm_AddObjekt(void);
int __cdecl fcn_00504bd0(int);
unsigned short __cdecl fcn_0042e410(unsigned short);
void __cdecl fcn_004c6ba0(int, int, int);
void __cdecl fcn_0051af00(void*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, int);

// FUNCTION: GOLD 0x4ba2c0
// SIZE: 415
// FUNCTION: GOLDTL 0x004ba690
// SIZE: 415

int __cdecl fcn_004ba690(int* a1)
{
	char* ents[8];
	char buf[0x100];
	unsigned short* e;
	unsigned char* it;
	char* chosen;
	char* rec;
	int n;
	int i;
	int amount;

	n = 0;
	rec = 0;
	e = fcn_00508e40(a1[0]);
	if (e == 0)
		return 1;
	for (it = gm_StartFilteredEntitySearch(1, 3, *e); it != 0 && n < 8; it = gm_AddObjekt()) {
		if (fcn_00504bd0(it[0]) == 1)
			ents[n++] = (char*) it;
	}
	if (n == 0)
		return 0x400;
	chosen = ents[fcn_0042e410(n)];
	for (i = 0; i < 768; i++) {
		if (g_7f4ca0[i].kind == 1 && g_7f4ca0[i].owner == chosen) {
			rec = (char*) &g_7f4ca0[i];
			break;
		}
	}
	if (chosen == 0 || rec == 0)
		return 0x400;
	amount = 0xfc - *(unsigned char*) (rec + 0x81);
	if (amount <= 0)
		return 0x400;
	fcn_004c6ba0(*(int*) (rec + 4), 1,
	    (char) (amount < fcn_0042e410(10) + 5 ? amount : fcn_0042e410(10) + 5));
	fcn_0051af00(buf, *(unsigned short*) (a1 + 1) + 0x12e7, 0x16b8, *(unsigned short*) rec, chosen);
	fcn_00545d40(*(int*) (e + 2), *(int*) (e + 2), buf, strlen(buf) > 0x100, 0x603, 0);
	return 0;
}
