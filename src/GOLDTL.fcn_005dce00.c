// FUNCTION: GOLD 0x005d08d0
// SIZE: 317
// FUNCTION: GOLDTL 0x005dce00
// SIZE: 317

#include <string.h>

typedef struct Ent {
	char pad0[4];
	int f4;
	char pad8[0x16c - 8];
	int owner;
	char pad170[0x1c5 - 0x170];
	unsigned char level;
	char pad1c6[0x21c - 0x1c6];
} Ent;
// SIZE 0x21c

extern Ent g_7f4ca0[];
extern int g_aed32c;

void __cdecl fcn_0051af00(char*, int);
int __cdecl fcn_005bdc30(int, int*, char*, int, int);
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
void __cdecl fcn_004c4510(int, int);
int __cdecl fcn_004c4570(unsigned char, unsigned char, unsigned short, char*);
void __cdecl fcn_004c5360(void);

int __cdecl fcn_005dce00(char* cmd, char* arg)
{
	char val;
	int desc[20];
	char name[0x100];
	int obj;
	int ok;
	int i;

	ok = 0;
	if (cmd[2] == 6) {
		memset(desc, 0, sizeof(desc));
		memset(desc + 7, 0xff, 8 * sizeof(int));
		fcn_0051af00(name, 0x9b);
		desc[0] = 1;
		desc[1] = -1;
		desc[4] = 4;
		desc[2] = 0x90010;
		desc[3] = 0;
		obj = fcn_005bdc30(1, desc, name, 0, 0);
		if (obj == 0) {
			goto end;
		}
		ok = 1;
	} else {
		obj = (int) gm_StartFilteredEntitySearch(1, 1, *(int*) (arg + 4));
		if (obj == 0) {
			goto end;
		}
		ok = 1;
	}
	for (i = 0; i < 768; i++) {
		if (g_7f4ca0[i].owner == obj) {
			val = g_7f4ca0[i].level % 2 + g_7f4ca0[i].level / 2;
			fcn_004c4510((int) &g_7f4ca0[i], g_7f4ca0[i].f4);
			fcn_004c4570(1, 1, (unsigned short) ((int) &g_7f4ca0[i].level - g_aed32c), &val);
			fcn_004c5360();
		}
	}
end:
	return ok;
}
