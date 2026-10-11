// FUNCTION: GOLD 0x0055b1c0
// FUNCTION: GOLDTL 0x5633e0

#pragma pack(1)
// SIZE 0x24d
struct good {
	unsigned char kind;
	char pad[0x24c];
};
#pragma pack()

// SIZE 0x21c
struct house {
	unsigned short id;
	unsigned char type;
	char pad3;
	int owner;
	char pad8[0x214];
};

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern unsigned char* g_868050;
extern char g_7f4ca0[];
extern unsigned char g_773d75;
extern char g_6b5c60[];
extern char g_6a65a4[];

unsigned short __cdecl gm_RandomMod(int);
void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);
unsigned char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
void __cdecl fcn_004c5420(int, int, int, int, int);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_00545e80(int, int, char*, int, int, int, int, char*, char*);
int __cdecl fcn_0050d270(int);
void __cdecl fcn_004c5150(int, int, unsigned char, int);
void __cdecl fcn_00546190(char*);

void __cdecl fcn_005633e0(char* u)
{
	struct good* gd;
	char text[0x800];
	struct house* h;
	unsigned char* e;
	int i;
	int v;

	h = 0;
	*(pos14_7f4c00*) (u + 0x52) = g_7f4c00;
	fcn_00500bb0((pos14_7f4c00*) (u + 0x52), gm_RandomMod(3) + 4, 0, 0);
	e = gm_StartFilteredEntitySearch(1, 1, *(int*) (u + 0xac));
	if (e != 0) {
		gd = &((struct good*)g_868050)[*e];
		if (gd->kind != 0xd && gd->kind != 0xc && gd->kind != 0xb) {
			fcn_004c5420(*(int*) (e + 1), 0x5a, 2, 2, 0);
			*(int*) (u + 0xb8) = 0;
			if (*(unsigned short*) (e + 0x25) != 0xffff) {
				h = &((struct house*)g_7f4ca0)[*(unsigned short*) (e + 0x25)];
				if (h != 0 && (u[0x78] & 2) != 0 && *e != 0x27) {
					for (i = 0; i < 768; i++) {
						if ((((struct house*)g_7f4ca0)[i].type == 6 || ((struct house*)g_7f4ca0)[i].type == 7) && ((struct house*)g_7f4ca0)[i].owner != h->owner) {
							fcn_0051af00(text, 0x17f4, h->id, e, *(int*) (u + 0xb0));
							fcn_00545e80(((struct house*)g_7f4ca0)[i].owner, -1, text, 0, 0x5ec, *(int*) (e + 1), -1, g_6b5c60, g_6a65a4);
						}
					}
				}
			}
			if (gd->kind == 5 && h != 0 && h->type != 6 && h->type != 7) {
				v = fcn_0050d270(*(int*) (e + 0x5d));
				if (v != 0) {
					fcn_004c5150(h->owner, *(int*) (e + 1), g_773d75, v);
				}
			}
			*(int*) (u + 0x84) = -1;
			return;
		}
	}
	fcn_00546190(u);
}
