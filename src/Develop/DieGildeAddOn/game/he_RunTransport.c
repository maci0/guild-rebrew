#include "client_types.h"

typedef struct Slot21c {
	char pad0[2];
	unsigned char kind;
	char pad3;
	int id;
	char pad8[0x214];
} Slot21c;
/* SIZE 0x21c */

extern pos14_7f4c00 gm_GameTime;
extern Slot21c g_7f4ca0[];
extern int g_7747cc;
extern char *g_7746c4;
extern char *g_7746c8;
extern unsigned char g_773d75;
extern unsigned short *gm_CityEntity;
extern int *g_7e453c;
extern int *g_7e4538;
extern float g_662cf8;
extern float g_662938;
extern float g_6640cc;
extern double g_6640e8;
extern char g_6a63ec[];
extern char g_6a63dc[];

char *__cdecl gm_StartFilteredEntitySearch(int, ...);
char *__cdecl gm_FindRecordById(int);
char *__cdecl gm_SearchTable67(int);
void __cdecl gm_ResolveEntityById(int, void *, int, int);
unsigned short __cdecl gm_RandomMod(int);
int __cdecl cm_GetCommandStatus(int);
int __cdecl cm_SendSetHE(int, char *);
char *__cdecl gm_GetChainNodeAtIndex(int, int);
int __cdecl he_LoadTransportCargoAtStop(void *, char);
int __cdecl he_BuyTransportCargoAtStop(void *, char);
void __cdecl cm_RequestSysMessage(int, void *);
void __cdecl cm_SendKillTransporter(int);
int __cdecl gm_AddTime(char *, int, int, int);
int __cdecl gm_CompareGameTime(char *, int);
char *__cdecl fcn_00502cd0(int, int, int, int, int);
int __cdecl gm_GetBuildingTechEffect(char *, int, int);
void __cdecl gm_ChangeObjektZustand(char *, int);
void __cdecl io_FormatTextBuffer(char *, int, ...);
void __cdecl he_PostEntityMessage(int, int, char *, int, int, int);
void __cdecl he_FreeAction(char *);
void __cdecl he_SetActionSubject(char *, int);
void __cdecl he_StepTransportCart(char *);
void __cdecl he_StepTransportCarrier(char *);
void __cdecl he_StepTransportEntry(char *);
void __cdecl he_TransportStadtStadt(char *);
void __cdecl ReportClientMessage(char *);
void __cdecl sb_PlayVoice(int, char *, int, int, int, int, int);
void __cdecl d2_CloseWindow(int);
int __cdecl gm_IsGebaeudeOpen(char *, int, int);

/* ADDRESS: GOLDTL 0x0055ea30 */
void __cdecl he_RunTransport(char *e)
{
	char *p44;
	char *p45;
	char *pB0;
	char *pB4;
	char *q;
	char *r;
	char c;
	float f;
	int n;
	int v;
	char buf[1024];
	pos14_7f4c00 stamp;

	if ((*(unsigned char *)(e + 0x78) & 2) && (n = *(int *)(e + 0x84)) != -1) {
		if (!cm_GetCommandStatus(n)) {
			return;
		}
		*(int *)(e + 0x84) = -1;
	}
	p44 = (char *)gm_StartFilteredEntitySearch(1, 0, 0x44);
	p45 = (char *)gm_StartFilteredEntitySearch(1, 0, 0x45);
	q = (char *)gm_StartFilteredEntitySearch(1, 1, *(int *)(e + 0xb0));
	pB4 = (char *)gm_StartFilteredEntitySearch(1, 1, *(int *)(e + 0xb4));
	if (p44 == 0 || q == 0 || pB4 == 0 || p45 == 0) {
		*(int *)(e + 0x70) = -1;
	}
	pB0 = gm_FindRecordById(*(int *)(e + 0xac));
	if (pB0 == 0) {
		goto ret190;
	}
	switch (*(int *)(e + 0x70)) {
	case 0:
		if ((*(unsigned char *)(e + 0x78) & 2) == 0) {
			break;
		}
		*(int *)(e + 0xe8) = -1;
		gm_AddTime(e + 0x52, 0, 0, 1);
		*(int *)(e + 0x84) = cm_SendSetHE(*(int *)(e + 0x70) + 1, e);
		return;
	case 1:
		if ((*(unsigned char *)(e + 0x78) & 2) == 0) {
			break;
		}
		r = e + 0x52;
		if (gm_CompareGameTime(r, (int) &gm_GameTime) >= 0) {
			break;
		}
		n = *(int *)(e + 0xec);
		if (n != -1 && !cm_GetCommandStatus(n)) {
			break;
		}
		n = *(int *)(e + 0xec);
		if (n != -1 && cm_GetCommandStatus(n) == 2) {
			goto ret_minus1;
		}
		n = *(int *)(e + 0xc8);
		*(int *)(e + 0xec) = -1;
		if (n == 2) {
			he_StepTransportCart(e);
		} else if (n == 1) {
			he_StepTransportCarrier(e);
		} else if (n == 3) {
			he_TransportStadtStadt(e);
		} else if (n == 4) {
			he_StepTransportEntry(e);
		} else {
			ReportClientMessage(g_6a63ec);
		}
		*(int *)(e + 0xd4) = *(int *)(e + 0xd4) + 1;
		*(pos14_7f4c00 *)(e + 0x60) = gm_GameTime;
		r = e + 0x52;
		*(pos14_7f4c00 *)r = gm_GameTime;
		gm_AddTime(r, 0, 5, 0);
		if (*(int *)(e + 0xd4) == 5) {
			gm_ResolveEntityById(0, &q, 0, *(int *)(e + 0xac));
			if ((unsigned short)gm_RandomMod(0x1e) > *(unsigned char *)(q + 0x12)) {
				io_FormatTextBuffer(buf, 0x1c46, *(unsigned short *)q * 2 + 0x9a8);
				he_PostEntityMessage(g_7f4ca0[(unsigned short)*(unsigned short *)(e + 8)].id, -1, buf, 0, 0x5ec, 0);
				cm_SendKillTransporter(*(int *)(q + 2));
				*(int *)(e + 0x84) = cm_SendSetHE(-1, e);
				return;
			}
		}
		if (*(char *)(e + 0xf1)) {
			return;
		}
		if (*(int *)(e + 0xd4) < 5) {
			return;
		}
		f = 0.0f;
		gm_ResolveEntityById(0, &q, 0, *(int *)(e + 0xac));
		r = gm_SearchTable67(*(int *)(q + 0x1c));
		if (r != 0) {
			f = (float)gm_GetBuildingTechEffect(r, 2, 1) + g_662cf8;
		}
		if (g_7e453c != 0 && *g_7e453c > 0x64) {
			f = f - g_662938;
		} else {
			if (g_7e4538 != 0 && *g_7e4538 > 200) {
				f = f - g_6640cc;
			}
		}
		n = (unsigned short)gm_RandomMod(0x69);
		if (n > (f * 0.01) * *(unsigned char *)(q + 0x12)) {
			if ((g_7f4ca0[(unsigned short)*(unsigned short *)(e + 8)].kind == 6 || g_7f4ca0[(unsigned short)*(unsigned short *)(e + 8)].kind == 7) && (*(unsigned char *)(q + 0x20) & 1) == 0) {
				io_FormatTextBuffer(buf, 0x1c45);
				he_PostEntityMessage(g_7f4ca0[(unsigned short)*(unsigned short *)(e + 8)].id, -1, buf, 0, 0x608, 0);
			}
			gm_ChangeObjektZustand(*(char **)(q + 2), -0xa);
			*(char *)(e + 0xf1) = 2;
			return;
		}
		*(char *)(e + 0xf1) = 1;
		return;
	case 2:
		if ((*(unsigned char *)(e + 0x78) == 0) & 2) {
			break;
		}
		n = *(int *)(e + 0xec);
		if (n == -1 || cm_GetCommandStatus(n)) {
			*(int *)(e + 0xec) = -1;
			gm_StartFilteredEntitySearch(1, 1, *(int *)(e + 0xb4));
			stamp = gm_GameTime;
			gm_AddTime((char *)&stamp, 0, 0, 1);
			r = (char *)gm_StartFilteredEntitySearch(1, 1, *(int *)(e + 0xb4));
			v = *(int *)(r + 1);
			cm_RequestSysMessage(4, &v);
			if (g_7746c4 == r || g_7746c8 == r) {
				sb_PlayVoice(g_7747cc, g_6a63dc, 1, 0x3f, 0x7f, 0, 0);
			}
			*(int *)(e + 0x84) = cm_SendSetHE(3, e);
			return;
		}
		break;
	case 3:
		if ((*(unsigned char *)(e + 0x78) & 2) == 0) {
			break;
		}
		if (*(char *)(e + 0xf2) != 0) {
			*(int *)(e + 0x84) = cm_SendSetHE(4, e);
			return;
		}
		goto ret_minus1;
	case 4:
		if ((*(unsigned char *)(e + 0x78) & 2) == 0) {
			break;
		}
		r = (char *)gm_StartFilteredEntitySearch(1, 1, *(int *)(e + 0xb4));
		c = g_773d75;
		if (*r == 'G') {
			c = *(unsigned char *)(r + 0x65);
		}
		he_LoadTransportCargoAtStop(pB0, c);
		*(int *)(e + 0x84) = cm_SendSetHE(5, e);
		return;
	case 5:
		if ((*(unsigned char *)(e + 0x78) & 2) == 0) {
			break;
		}
		r = (char *)gm_GetChainNodeAtIndex(*(int *)(pB0 + 0x29), *(int *)(pB0 + 0x2d));
		if (r == 0) {
			goto ret_minus1;
		}
		q = gm_SearchTable67(*(int *)(r + 4));
		if (q == 0) {
			goto ret_minus1;
		}
		if (gm_IsGebaeudeOpen(q, 0, 0) != 0) {
			c = g_773d75;
			if (*q == 'G') {
				c = *(unsigned char *)(q + 0x65);
			}
			he_BuyTransportCargoAtStop(pB0, c);
			*(int *)(e + 0x84) = cm_SendSetHE(-1, e);
			return;
		}
		r = e + 0x52;
		*(pos14_7f4c00 *)r = gm_GameTime;
		gm_AddTime(r, 0, 0xf, 0);
		return;
	case -2:
		he_SetActionSubject(e, *gm_CityEntity);
		if (*(int *)(e + 0xc4) == *(int *)(p44 + 1)) {
			*(int *)(e + 0x84) = cm_SendSetHE(1, e);
			return;
		}
		if (*(int *)(e + 0xc4) == *(int *)(pB4 + 1)) {
			goto ret_minus1;
		}
		if (*(int *)(e + 0xc4) != *(int *)(q + 1)) {
			break;
		}
		*(int *)(e + 0x84) = cm_SendSetHE(1, e);
		return;
	case -1:
		r = (char *)fcn_00502cd0(0, 2, 7, 1, *(int *)(e + 0xac));
		if ((*(unsigned char *)(e + 0x78) & 2) != 0) {
			if (r == 0) {
				goto ret190;
			}
			if ((unsigned short)gm_RandomMod(100) > 0x4b) {
				gm_ChangeObjektZustand(*(char **)(r + 2), -2);
			}
			if (*(int *)(e + 0xe8) != -1) {
				d2_CloseWindow(*(int *)(e + 0xe8));
			}
		}
		if (r != 0) {
			*(int *)(r + 0x24) = 0;
			*(unsigned char *)(r + 0x13) = *(unsigned char *)(r + 0x13) & 0xbf;
		}
		goto ret190;
	default:
		break;
	}
	return;
ret_minus1:
	*(int *)(e + 0x84) = cm_SendSetHE(-1, e);
	return;
ret190:
	he_FreeAction(e);
}
