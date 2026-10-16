#include "g_10058a0.h"

// SIZE 0x40
typedef struct Node_4bf8e0 {
	int f0;
	int f4;
	char pad8[0x38];
} Node_4bf8e0;

extern char s_681730[];
extern int g_772514;
extern int g_14b5e9c;
extern int g_14b5eac;
extern int g_14b5ed8[];
extern int g_14b5eb4;
extern int g_14b5eb8;
extern int g_14b5ebc;
extern int g_14b5ec0;
extern int g_14b5ec4;
extern int g_14ce8e0;
extern int g_100f1dc;
extern int g_67d370;
extern int g_774654;
extern Node_4bf8e0* g_772908;
extern IdSlot10058a0 g_10058a0[8];
extern int g_772900;
extern int g_6816d8;
#include "client_packet_builder.h"

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00472250(int, int, int);
void __cdecl fcn_00533a60(int, int, int*, int, ...);
void __cdecl fcn_0046f9b0(int, int);
void __cdecl fcn_00472380(int, int, int, int);
void __cdecl fcn_00468cd0(int, int);
void __cdecl fcn_00468bb0(int, int, int, int, int, int, int);
int __cdecl fcn_005373e0(void*, int);
#include "Develop/DieGildeAddOn/game/spiel.h"
void __cdecl fcn_004bfc70(int);
void __cdecl fcn_004be360(void);
Node_4bf8e0* __cdecl fcn_004be1f0(Node_4bf8e0*);
void __cdecl fcn_004be3d0(int, char*, Node_4bf8e0*, Node_4bf8e0*);
void __cdecl fcn_004695a0(int, int);

int __cdecl fcn_004c4700(unsigned char, unsigned char, short, void*);
void __cdecl fcn_004c53a0(void);
int __cdecl fcn_00471f80(int);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_004116d0(void);

/* ADDRESS: GOLDTL 0x004bf8e0 */
void __cdecl fcn_004bf8e0(char* p, int arg)
{
	int ids[10];
	int ok;
	int clear;
	int flip;
	int dlg;
	int list;
	int i;

	dlg = fcn_00470820(0, 0, s_681730);
	fcn_00471b60(dlg);
	fcn_004727a0(dlg, 1);
	fcn_00519190(0x42e2);
	list = fcn_00472250(dlg, 2, 0);
	fcn_004727a0(dlg, 4);
	fcn_00519190(*(unsigned char*) (p + 0x33) + 0x42ec);
	fcn_004727a0(dlg, 3);
	fcn_00533a60(g_772514, 0, ids, 3, g_14b5e9c, g_14b5eac, g_14b5ed8[*(unsigned char*) (p + 0x33)]);
	ok = ids[0];
	clear = ids[1];
	flip = ids[2];
	fcn_0046f9b0(flip, g_14b5ed8[*(unsigned char*) (p + 0x33)]);
	fcn_00472380(list, 0, 4, *(unsigned char*) (p + 0x31));
	fcn_00468cd0(list, 0x82);
	fcn_00468bb0(list, 5, g_14b5eb4, g_14b5eb8, g_14b5ebc, g_14b5ec0, g_14b5ec4);
	while (fcn_005373e0(fcn_004bf8e0, 0x657c7) != 0) {
		if (g_14ce8e0 != 0 || (g_100f1dc != -1 && g_67d370 == ok)) {
			g_774654 = 1;
		}
		fcn_004727a0(dlg, 4);
		fcn_00519190(*(unsigned char*) (p + 0x33) + 0x42ec);
		fcn_0046f9b0(flip, g_14b5ed8[*(unsigned char*) (p + 0x33)]);
		if (g_100f1dc != -1 && g_67d370 == clear) {
			if (g_772908 != 0) {
				fcn_004be280((char*) g_772908);
			}
			for (i = 0; i < 8; i++) {
				if (g_10058a0[i].id != -1) {
					fcn_004bfc70(i);
				}
			}
			g_772900 = 0;
			fcn_004be360();
			g_772908 = fcn_004be1f0(0);
			g_772908->f4 = *(int*) (p + 0x1c);
			g_772908->f0 = *(int*) (p + 2);
			fcn_004be3d0(arg, p, g_772908, g_772908);
			fcn_004695a0(g_6816d8, 0);
			g_774654 = 2;
		}
		if (g_100f1dc != -1 && g_67d370 == flip) {
			unsigned char b;

			b = *(unsigned char*) (p + 0x33) == 0;
			fcn_004c4510(p, *(int*) (p + 2));
			fcn_004c4700(1, 1, (short) (p + 0x33 - g_aed32c), &b);
			fcn_004c53a0();
		}
	}
	if (fcn_00471f80(list) != *(unsigned char*) (p + 0x31)) {
		unsigned char b;

		b = fcn_00471f80(list);
		fcn_004c4510(p, *(int*) (p + 2));
		fcn_004c4700(1, 1, (short) (p + 0x31 - g_aed32c), &b);
		fcn_004c53a0();
	}
	fcn_00471e30(dlg);
	fcn_004116d0();
}
