#include "client_types.h"

typedef struct {
	char* e;
	int tile;
	int bar;
	char pad0c[0x2c];
} SEL_54f600;

typedef struct {
	char pad0[0x5c];
	int f5c;
	char pad60[0x1d0 - 0x60];
	int f1d0;
	char pad1d4[0x2f0 - 0x1d4];
	char* owner;
} TILE_54f600;

extern pos14_7f4c00 gm_GameTime;
extern char* g_77255c;
extern int d2_CurrentWindowId;
extern char* g_1015ea0;
extern int g_100f884;
extern int g_100f1dc;
extern char g_774964;
extern char* g_7747b8;

int __cdecl he_StartHandlungSearch(int, int, int);
char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl gm_CompareGameTime(void*, void*);
void __cdecl he_DeclineDuell(char*, char*, unsigned char*);
void __cdecl he_AcceptDuell(char*, char*, char*);
void __cdecl fcn_00545780(char*);
void __cdecl he_FreeAction(char*);
int __cdecl d2_CreateActionPopupSlot(char*, int, int, char*, int);
void __cdecl sb_PlayVoice(char*, char*, int, int, int, int, int);
int __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
void __cdecl gm_AddTime(char*, int, int, int);
int __cdecl d2_BuildPersonStatusDesc(SEL_54f600*);
int __cdecl d2_DrawPersonTile(int, int, int, SEL_54f600*);
void __cdecl cm_SendSetHE(int, void*);
#include "Develop/Units/d2.v1/d2_gui.h"
/* ADDRESS: GOLDTL 0x0054f600 */
void __cdecl fcn_0054f600(char* o)
{
	char* entity;
	char* v4;
	char* v6;
	SEL_54f600 s;
	int state;

	v6 = 0;
	v4 = 0;
	entity = he_StartHandlungSearch(1, 1, *(int*) (o + 0xac));
	if (entity != 0) {
		v6 = gm_LookupEntityRecordById(*(int*) (entity + 0xb0));
		v4 = gm_LookupEntityRecordById(*(int*) (entity + 0xac));
	}
	state = *(int*) (o + 0x70);
	if (state != -1 && state != -2 && entity != 0 && v6 != 0 && v4 != 0) {
		switch (state) {
		case 1:
			if (gm_CompareGameTime(&gm_GameTime, o + 0x52) > 0) {
				he_DeclineDuell(entity, v4, (unsigned char*) v6);
				fcn_00545780(o);
				he_FreeAction(o);
				return;
			}
			if (g_100f884 != *(int*) (*(int*) (o + 0x74) + 8)) {
				return;
			}
			if (g_100f1dc == -1) {
				return;
			}
			if (g_100f1dc == 2) {
				he_AcceptDuell(entity, v4, v6);
			} else if (g_100f1dc == 1) {
				he_DeclineDuell(entity, v4, (unsigned char*) v6);
			}
			fcn_00545780(o);
			he_FreeAction(o);
			return;
		case 0:
			d2_CreateActionPopupSlot(o, 0, 0, "_DUELL_INTRO_EVENT_DUELLANTEN_HS_00", 0x5ec);
			if (*(int*) (o + 0x74) != 0) {
				if (g_774964 != 2) {
					sb_PlayVoice(g_7747b8, "NeueMessage_s_01", 1, 0x3f, 0x7f, 0, 0);
				}
				d2_SetForm(*(int*) (*(int*) (o + 0x74) + 8), 1);
				io_AppendText(0x1d6c);
				d2_SetForm(*(int*) (*(int*) (o + 0x74) + 8), 2);
				s.e = v4;
				if (d2_BuildPersonStatusDesc(&s) != 0) {
					d2_DrawPersonTile(*(int*) (g_77255c + 0xc) / 2 - 0x28, 0, d2_CurrentWindowId, &s);
					((D2_CONTROL_TL*) g_1015ea0)[s.tile].value_05c = 1;
					((D2_CONTROL_TL*) g_1015ea0)[s.tile].flags_1d0 = 3;
					((D2_CONTROL_TL*) g_1015ea0)[s.tile].associated_object = s.e;
				}
				d2_SetForm(*(int*) (*(int*) (o + 0x74) + 8), 3);
				io_AppendText(0x1d6b, (int) *(unsigned short*) (entity + 0xb4),
				    (int) *(unsigned short*) v4, (int) *(unsigned short*) (entity + 0xb6),
				    (int) *(unsigned short*) v4);
				*(pos14_7f4c00*) (o + 0x44) = gm_GameTime;
				*(pos14_7f4c00*) (o + 0x52) = gm_GameTime;
				gm_AddTime(o + 0x52, 2, 0, 0);
				(*(int*) (o + 0x70))++;
				return;
			}
			break;
		default:
			return;
		}
	} else {
		if (*(int*) (o + 0x74) != 0) {
			fcn_00545780(o);
		}
		if (entity != 0) {
			*(pos14_7f4c00*) (entity + 0x52) = gm_GameTime;
			cm_SendSetHE(-1, entity);
		}
	}
	he_FreeAction(o);
}
