


// SIZE 0x21c
struct house {
	unsigned short id;
	unsigned char type;
	char pad3;
	int handle;
	char pad8[0x164];
	char* owner;
	char pad170[0x14];
	int busy;
	char pad188[0x94];
};

#pragma pack(1)
// SIZE 0x24d
struct good {
	unsigned char kind;
	char pad1[0x24c];
};
#pragma pack()

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern char g_7f4ca0[];
extern unsigned char* lpGebaeudePROT;

unsigned char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
void __cdecl fcn_004c6650(int);
int __cdecl fcn_00500480(struct house*, int*, int*);
void __cdecl fcn_004c5da0(int, int, int, int, int, char*);
void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, char*);
void __cdecl fcn_004c5fd0(int);
void __cdecl fcn_00546190(char*);

void __cdecl fcn_00564210(char* e)
{
	int a;
	int b;
	char buf[0x400];
	unsigned char* t;
	int i;

	switch (*(int*) (e + 0x70)) {
	case 0:
		t = gm_StartFilteredEntitySearch(1, 1, *(int*) (e + 0xac));
		if (t == 0) {
			return;
		}
		for (i = 0; i < 768; i++) {
			if (((struct house*)g_7f4ca0)[i].owner == (char*) t) {
				if (((struct house*)g_7f4ca0)[i].busy != 0) {
					fcn_004c6650(((struct house*)g_7f4ca0)[i].handle);
				}
				if (fcn_00500480(&((struct house*)g_7f4ca0)[i], &a, &b) != 0) {
					if (b != -1) {
						fcn_004c5da0(((struct house*)g_7f4ca0)[i].handle, a, b, 0, 0, "GebAbreissen");
					} else {
						fcn_004c5da0(((struct house*)g_7f4ca0)[i].handle, a, -1, 0, 1, "GebAbreissen");
					}
				}
			}
		}
		*(pos14_7f4c00*) (e + 0x52) = g_7f4c00;
		fcn_00500bb0((pos14_7f4c00*) (e + 0x52), 0, 5, 0);
		*(int*) (e + 0x70) = *(int*) (e + 0x70) + 1;
		return;
	case 1:
		t = gm_StartFilteredEntitySearch(1, 1, *(int*) (e + 0xac));
		if (t != 0 && ((struct good*)lpGebaeudePROT)[*t].kind != 0xf) {
			for (i = 0; i < 768; i++) {
				if ((((struct house*)g_7f4ca0)[i].type == 6 || ((struct house*)g_7f4ca0)[i].type == 7) && ((struct house*)g_7f4ca0)[i].id != *(unsigned short*) (t + 0x27)) {
					fcn_0051af00(buf, 0x1c52, *(unsigned short*) (t + 0x27), t);
					fcn_00545d40(((struct house*)g_7f4ca0)[i].handle, -1, buf, 0, 0x5ed, "_NACHRICHTEN_HS_67");
				}
			}
			fcn_004c5fd0(*(int*) (t + 1));
		}
		fcn_00546190(e);
		return;
	case -2:
	case -1:
		fcn_00546190(e);
		return;
	}
}
