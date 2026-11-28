/* Float block used by the reward calculation. */
typedef struct Gfx {
	float f[10];
} Gfx;
// SIZE 0x28
#include "Develop/DieGildeAddOn/game/building_prototype.h"
extern char* lpGebaeudePROT;
extern unsigned char gm_ActiveTownIndex;
extern int d2_DialogButtonAction;
extern int g_100f884;
extern int gm_GameTime;
extern double dbl_1_5;
extern float flt_0_01;

char* __cdecl gm_LookupEntityRecordById(int id);
char* __cdecl gm_SearchTable67(int id);
void __cdecl he_FreeAction(char* e);
void __cdecl d2_CreateActionPopupSlot(char* e, int a, int b, char* tag, int c);
void __cdecl d2_SetForm(int dlg, int page);
int __cdecl io_AppendText(int id, ...);
int __cdecl gm_CompareGameTime(int* pos, int base);
int __cdecl gm_CalculateGebaeudeValue(char* e, int n);
char* __cdecl gm_StartFilteredEntitySearch(int a, int b, int id, int c, int d);
int __cdecl gm_FindNextFilteredEntity(void);
float __cdecl gm_CalcEntityFavor(unsigned int a0, unsigned int a1, unsigned int a2);
void __cdecl io_FormatTextBuffer(char* buf, int id, ...);
void __cdecl he_MessageBoxQuickjump(int a, int b, char* text, int c, int d, int e, int f, int g, int h);
void __cdecl cm_RequestChangeBits(int a, int b, int c, int d, int e);
void __cdecl cm_RequestTransferCurrencyNoKill(int a, int b, unsigned char k, int n);
void __cdecl cm_SendSetGebBesitzer(int a, int b, int c);
void __cdecl d2_CloseActionPopup(char* e);

/* ADDRESS: GOLDTL 0x00564460 */
void __cdecl he_RunGebaeudeKaufangebot(char* e)
{
	float f;
	int n;
	char buf[1024];
	unsigned char* p;
	unsigned char* rec;
	unsigned short* q;
	unsigned char type;
	int ptype;
	int k;
	int c;

	switch (*(int*) (e + 0x70)) {
	case 0:
		q = (unsigned short*) gm_LookupEntityRecordById(*(int*) (e + 0xb4));
		p = (unsigned char*) gm_SearchTable67(*(int*) (e + 0xac));
		if (q == 0 || p == 0) {
			he_FreeAction(e);
			return;
		}
		type = *(unsigned char*) (*(unsigned short*) (p + 0x25) * 0x21c + 0x7f4ca2);
		if (type == 6 || type == 7) {
			d2_CreateActionPopupSlot(e, 0, 0, "misc\\EventMessagebox_NULL", 0x5ec);
			d2_SetForm(*(int*) (*(char**) (e + 0x74) + 8), 0);
			io_AppendText(0x17e8, *q, p, *(int*) (e + 0xb0));
			*(int*) (e + 0x70) = *(int*) (e + 0x70) + 1;
			return;
		}
		if (gm_CompareGameTime((int*) (e + 0x52), 0x7f4c00) >= 0) {
			return;
		}
		f = 15.0f;
		q = (unsigned short*) gm_LookupEntityRecordById(*(int*) (e + 0xb4));
		p = (unsigned char*) gm_SearchTable67(*(int*) (e + 0xac));
		rec = (unsigned char*)&((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*p];
		n = gm_CalculateGebaeudeValue(p, (int) (char) p[0x5c]);
		if ((((BUILDING_PROTOTYPE*)rec)->category) == 2) {
			unsigned char* v4;

			v4 = *(unsigned char**) (*(unsigned short*) (p + 0x25) * 0x21c + 0x7f4e10);
			if (v4 != 0 && v4 == p) {
				f = 5.0f;
			} else if (v4 != 0 && *v4 < *p) {
				f = 1.2f;
			}
		} else {
			k = 0;
			ptype = ((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*p].category;
			c = *(unsigned short*) (*(unsigned short*) (p + 0x25) * 0x21c + 0x7f4ca0);
			if (gm_StartFilteredEntitySearch(2, 4, c, 5, ptype) != 0) {
				do {
					k++;
				} while (gm_FindNextFilteredEntity());
			}
			if (k <= 1) {
				ptype = *(unsigned char*) (*(unsigned short*) (p + 0x25) * 0x21c + 0x7f4ca2);
				if (ptype == 6 || ptype == 7 || ptype == 5) {
					f = 8.0f;
				} else {
					f = 1.6f;
				}
			} else {
				f = 1.6f;
			}
		}
		if ((double)n * ((double)f * (dbl_1_5 - (double)gm_CalcEntityFavor(*q, *(unsigned short*) (p + 0x25), 1) * flt_0_01)) < (double) *(int*) (e + 0xb0)) {
			io_FormatTextBuffer(buf, 0x17e9, *(unsigned short*) (p + 0x27), p);
			he_MessageBoxQuickjump(*(int*) (q + 2), -1, buf, 0, 0x5ec, *(int*) (p + 1), -1, 0, 0);
			cm_RequestChangeBits(*(int*) (p + 1), 0x5a, 2, 2, 0x200);
			cm_RequestTransferCurrencyNoKill(*(int*) (*(unsigned short*) (p + 0x25) * 0x21c + 0x7f4ca4),
				*(int*) (q + 2), gm_ActiveTownIndex, *(int*) (e + 0xb0));
			if (*(short*) (p + 0x27) == *(short*) (p + 0x25)) {
				cm_SendSetGebBesitzer(*(int*) (p + 1), *(int*) (q + 2), *(int*) (q + 2));
			} else {
				cm_SendSetGebBesitzer(*(int*) (p + 1), *(int*) (q + 2), -1);
			}
			cm_RequestChangeBits(*(int*) (p + 1), 0x5a, 2, 0, 2);
			he_FreeAction(e);
			return;
		}
		io_FormatTextBuffer(buf, 0x17ea, *(unsigned short*) (p + 0x27), p);
		he_MessageBoxQuickjump(*(int*) (q + 2), -1, buf, 0, 0x5ec, *(int*) (p + 1), -1, 0, 0);
		cm_RequestChangeBits(*(int*) (p + 1), 0x5a, 2, 0, 0x200);
		d2_CloseActionPopup(e);
		he_FreeAction(e);
		he_FreeAction(e);
		return;
	case 1:
		if (g_100f884 != *(int*) (*(char**) (e + 0x74) + 8)) {
			return;
		}
		if (d2_DialogButtonAction == -1) {
			return;
		}
		q = (unsigned short*) gm_LookupEntityRecordById(*(int*) (e + 0xb4));
		p = (unsigned char*) gm_SearchTable67(*(int*) (e + 0xac));
		if (d2_DialogButtonAction == 2) {
			io_FormatTextBuffer(buf, 0x17e9, *(unsigned short*) (p + 0x27), p);
			he_MessageBoxQuickjump(*(int*) (q + 2), -1, buf, 0, 0x5ec, *(int*) (p + 1), -1, 0, 0);
			cm_RequestChangeBits(*(int*) (p + 1), 0x5a, 2, 2, 0x200);
			cm_RequestTransferCurrencyNoKill(*(int*) (*(unsigned short*) (p + 0x25) * 0x21c + 0x7f4ca4),
				*(int*) (q + 2), gm_ActiveTownIndex, *(int*) (e + 0xb0));
			if (*(short*) (p + 0x27) == *(short*) (p + 0x25)) {
				cm_SendSetGebBesitzer(*(int*) (p + 1), *(int*) (q + 2), *(int*) (q + 2));
			} else {
				cm_SendSetGebBesitzer(*(int*) (p + 1), *(int*) (q + 2), -1);
			}
			cm_RequestChangeBits(*(int*) (p + 1), 0x5a, 2, 0, 2);
			d2_CloseActionPopup(e);
			he_FreeAction(e);
			return;
		}
		if (d2_DialogButtonAction != 1) {
			return;
		}
		io_FormatTextBuffer(buf, 0x17ea, *(unsigned short*) (p + 0x27), p);
		he_MessageBoxQuickjump(*(int*) (q + 2), -1, buf, 0, 0x5ec, *(int*) (p + 1), -1, 0, 0);
		cm_RequestChangeBits(*(int*) (p + 1), 0x5a, 2, 0, 0x200);
		break;
	case -2:
	case -1:
		p = (unsigned char*) gm_SearchTable67(*(int*) (e + 0xac));
		if (p != 0) {
			cm_RequestChangeBits(*(int*) (p + 1), 0x5a, 2, 0, 0x200);
		}
		break;
	default:
		return;
	}
	d2_CloseActionPopup(e);
	he_FreeAction(e);
}
