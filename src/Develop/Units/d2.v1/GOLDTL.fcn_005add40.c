#include "client_types.h"






// SIZE 0xe

typedef struct
{
	int x0;
	unsigned char type;
	char pad5[3];
	int x8;
	int xc;
	char pad10[0x18];
	pos14_7f4c00 name;
	unsigned char x36;
	char pad37;
	int ids[8];
	int x58;
	int x5c;
	char pad60[0x98];
} Packet;
// SIZE 0xf8

typedef struct
{
	unsigned short x0;
	char pad2[2];
	int x4;
	char pad8[0x180];
	unsigned char x188;
	char pad189[0x93];
} Player;
// SIZE 0x21c

extern char g_7f4ca0[];
extern char* ch_ContextCharacters[32];
#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern int g_14abc44;
extern int g_100f1dc;
extern int d2_CurrentElementId;
extern int g_14ce8e0;
#include "client_dialog_state.h"
extern char* g_7746c4;
extern char s_6aa490[];

int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl fcn_00472250(int, int, int);
char* __cdecl he_StartHandlungSearch(int, int, int, int, int, int, int);
char* __cdecl he_fn_Handlung(void);
int __cdecl fcn_004c5530(Packet*);
void __cdecl cm_ExProdObjekt(void);
int __cdecl fcn_00526120(int, int);
void __cdecl fcn_00529160(int, int, int, char*);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);

int __cdecl fcn_005add40(int unused, char* e)
{
	int r;
	int btn1;
	int btn2;
	Packet pkt;
	int dlg;
	int s;
	char* p;
	int n;
	int i;

	r = 0;
	dlg = fcn_00470820(0, 0, s_6aa490);
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 1);
	s = io_AppendText(0x19ee, *(unsigned short*) (e + 0x27), e);
	btn1 = fcn_00472250(dlg, 1, s);
	btn2 = fcn_00472250(dlg, 1, s + 1);
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_100f1dc != -1) {
			if (d2_CurrentElementId == btn1) {
				for (p = he_StartHandlungSearch(3, 0, 0x49, 2, *(unsigned short*) (g_7746c4 + 0x27), 3, *(int*) (g_7746c4 + 1)); p != 0; p = he_fn_Handlung()) {
					if (*(int*) (p + 0xac) == *(int*) (e + 1)) {
						break;
					}
				}
				if (p == 0) {
					pkt.type = 0x49;
					pkt.x8 = ((Player*)g_7f4ca0)[*(unsigned short*) (g_7746c4 + 0x27)].x4;
					pkt.xc = *(int*) (g_7746c4 + 1);
					pkt.name = (*(pos14_7f4c00*)&gm_GameTime);
					pkt.x36 = 1;
					pkt.x58 = *(int*) (e + 1);
					pkt.x5c = *(int*) (g_7746c4 + 1);
					for (i = 0; i < 8; i++) {
						pkt.ids[i] = -1;
					}
					n = 0;
					for (i = 0; i < 32; i++) {
						if (n >= 8) {
							break;
						}
						if (((Player**)ch_ContextCharacters)[i] != 0 && ((Player**)ch_ContextCharacters)[i]->x188 != 0) {
							pkt.ids[n] = ((Player**)ch_ContextCharacters)[i]->x4;
							n++;
						}
					}
					if (n == 0) {
						fcn_00526120(g_14abc44, 0);
					}
					else {
						r = 1;
						fcn_004c5530(&pkt);
						cm_ExProdObjekt();
						g_774654 = 2;
					}
				}
				else {
					r = 1;
					g_774654 = 2;
					for (i = 0; i < 32; i++) {
						if (((Player**)ch_ContextCharacters)[i] != 0 && ((Player**)ch_ContextCharacters)[i]->x188 != 0) {
							fcn_00529160(0, 0, ((Player**)ch_ContextCharacters)[i]->x0, p);
						}
					}
				}
			}
			else if (d2_CurrentElementId == btn2) {
				g_774654 = 1;
			}
		}
	} while (fcn_005373e0((void*) fcn_005add40, 0x677c7) != 0);
	fcn_00471e30(dlg);
	return r;
}
