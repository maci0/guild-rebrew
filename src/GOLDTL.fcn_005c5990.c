// FUNCTION: GOLD 0x005b9f00
// SIZE: 382
// FUNCTION: GOLDTL 0x005c5990
// SIZE: 382

#include <string.h>
#pragma intrinsic(memset)

typedef struct {
	short s[7];
} Stamp5c59;
// SIZE 0xe

typedef struct {
	int pad0;
	int f4;
	char pad8[0x180];
	char active;
	char pad189[0x93];
} Ent5c59;
// SIZE 0x21c

typedef struct {
	char* name;
	int pad;
} Name5c59;
// SIZE 0x8

extern Ent5c59 g_7f4ca0[768];
extern unsigned short g_774970;
extern Stamp5c59 g_7f4c00;
extern int g_7746a4;
extern int g_7746f0;
extern int g_774800;
extern int g_14ce8cc;
extern char* g_14a555c;
extern char* g_14a5558;
extern Name5c59 g_14a79c0[];

char* __cdecl fcn_004bcc20(int, int);
void __cdecl fcn_004c5530(char*);
void __cdecl cm_ExProdObjekt(void);
int __cdecl fcn_0064d41a(char*, char*, ...);
void __cdecl fcn_00475220(char*);

void __cdecl fcn_005c5990(char* who, int id)
{
	char* e;
	int i;

	if (g_7746a4 == 0) {
		return;
	}
	e = fcn_004bcc20(id, g_7746a4);
	if (g_7746f0 != 0) {
		if (e == 0) {
			return;
		}
		if ((e[0xd] > 1 || g_774800 != 0) && g_14ce8cc != 0) {
			for (i = 0; i < 768; i++) {
				if (g_7f4ca0[i].active) {
					char msg[0xf8];

					memset(msg, 0, sizeof(msg));
					*(int*) (msg + 8) = g_7f4ca0[g_774970].f4;
					msg[4] = 0x28;
					*(int*) (msg + 0x10) = 1;
					*(int*) (msg + 0x14) = 0;
					msg[0x36] = 1;
					*(int*) (msg + 0xc) = *(int*) (who + 1);
					*(Stamp5c59*) (msg + 0x28) = g_7f4c00;
					*(int*) (msg + 0x64) = *(int*) e;
					*(int*) (msg + 0x5c) = g_7f4ca0[i].f4;
					*(int*) (msg + 0x58) = *(int*) (who + 1);
					fcn_004c5530(msg);
					cm_ExProdObjekt();
				}
			}
			return;
		}
	}
	if (e == 0) {
		return;
	}
	if (e[0xd] > 1) {
		char text[0xf8];

		fcn_0064d41a(text, g_14a555c, g_14a79c0[*(unsigned short*) (e + 0xa)].name);
		fcn_00475220(text);
	} else {
		fcn_00475220(g_14a5558);
	}
}
