


typedef struct
{
	int x0;
	unsigned char type;
	char pad5[3];
	int x8;
	char padc[0x2a];
	unsigned char x36;
	char pad37;
	int ids[8];
	int x58;
	int x5c;
	char pad60[0x98];
} Packet;
// SIZE 0xf8

#include "Develop/DieGildeAddOn/game/entity_record.h"











#include "Develop/DieGildeAddOn/game/game_player.h"
extern char* g_7746c4;
extern int g_14abab4;
extern int g_14abaac;
extern int g_100f1dc;
extern int d2_CurrentElementId;
extern int g_14ce8e0;
#include "client_dialog_state.h"
extern char s_6aa464[];

int __cdecl fcn_0055c050(char*);
void __cdecl io_FormatTextBuffer(char*, int, ...);
int __cdecl fcn_00526120(char*, int);
int __cdecl fcn_0050c550(char*, char*);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_004c5530(Packet*);
void __cdecl cm_ExProdObjekt(void);
void __cdecl sv_ClearObjectSelection(void);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);

int __cdecl d2_ConfirmEinbruch(int unused, char* e)
{
	int r;
	int btn1;
	Packet pkt;
	char buf[0x400];
	ENTITY_RECORD* p;
	int dlg;
	int s;
	int btn2;
	int n;
	int i;

	r = 0;
	if (e == 0) {
		return 0;
	}
	p = &((ENTITY_RECORD*)g_7f4ca0)[*(unsigned short*) (e + 0x27)];
	if (fcn_0055c050(e) == 0) {
		io_FormatTextBuffer(buf, 0x1a92, *(unsigned short*) (e + 0x27), e);
		fcn_00526120(buf, 0);
		return 0;
	}
	if (fcn_0050c550(g_7746c4, e) == 0) {
		fcn_00526120((char*) g_14abab4, 0);
		return 0;
	}
	dlg = fcn_00470820(0, 0, s_6aa464);
	d2_CenterDialogWindows(dlg);
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(dlg, 1);
	s = io_AppendText(0x19e4, p->entity_index, e);
	btn1 = fcn_00472250(dlg, 1, s);
	btn2 = fcn_00472250(dlg, 1, s + 1);
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_100f1dc != -1) {
			if (d2_CurrentElementId == btn1) {
				pkt.type = 0x3f;
				pkt.x36 = 1;
				n = 0;
				pkt.x8 = ((ENTITY_RECORD*)g_7f4ca0)[g_774970].entity_id;
				pkt.x58 = *(int*) (e + 1);
				pkt.x5c = *(int*) (g_7746c4 + 1);
				for (i = 0; i < 8; i++) {
					pkt.ids[i] = -1;
				}
				for (i = 0; i < 768; i++) {
					if (((ENTITY_RECORD*)g_7f4ca0)[i].unk_17c[12] != 0) {
						pkt.ids[n] = ((ENTITY_RECORD*)g_7f4ca0)[i].entity_id;
						n++;
					}
				}
				if (n != 0) {
					fcn_004c5530(&pkt);
					cm_ExProdObjekt();
				}
				else {
					fcn_00526120((char*) g_14abaac, 0);
				}
				sv_ClearObjectSelection();
				g_774654 = 1;
				r = 1;
			}
			else if (d2_CurrentElementId == btn2) {
				g_774654 = 1;
			}
		}
	} while (fcn_005373e0((void*) d2_ConfirmEinbruch, 0x677c7) != 0);
	fcn_00471e30(dlg);
	return r;
}
