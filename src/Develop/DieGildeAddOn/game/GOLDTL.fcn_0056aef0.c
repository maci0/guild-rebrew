#include "client_types.h"
#include "Develop/DieGildeAddOn/game/entity_record.h"
#include "Develop/DieGildeAddOn/game/game_data.h"

#pragma pack(1)
/* message record handed to fcn_004c6be0 */
typedef struct {
	pos14_7f4c00 stamp;	/* +0x00 */
	int f0e;		/* +0x0e */
	int f12;		/* +0x12 */
	int f16;		/* +0x16 */
	char f1a;		/* +0x1a */
	char f1b;		/* +0x1b */
} Msg56;
// SIZE 0x1c
#pragma pack()

extern pos14_7f4c00 gm_GameTime;
extern unsigned char g_773d75;

extern unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
extern char* __cdecl gm_LookupEntityRecordById(int id);
extern void __cdecl cm_SendCancelCharacterActions(int a1);
extern void __cdecl ch_StartMovement(int, int, int, char*, int, char*);
extern void __cdecl he_AssignActionSlot(char*, char*, unsigned int, char*);
extern void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);
extern int __cdecl gm_IsEntityAtBuilding(char*, char*);
extern int __cdecl gm_GetScaledEntitySkill(char*, int);
extern int __cdecl fcn_0050c4e0(unsigned char*);
extern void __cdecl he_FreeAction(char*);
extern unsigned short* __cdecl fcn_00502cd0(int, int, ...);
extern int __cdecl gm_WalkEntityChain(unsigned short raw_idx);
extern int __cdecl gm_GetMsgField(char*, char*);
extern float __cdecl fcn_0050bb50(int, unsigned char);
extern void* __cdecl gm_NextEntityQueryMatch(void);
extern int __cdecl gm_RandomMod(int);
extern int __cdecl gm_GetBuildingTechEffect(unsigned char*, int, int);
extern void __cdecl cm_RequestAllocWarEvent(char*, char*);
extern char* __cdecl fcn_0050dc90(char*);
extern unsigned short* __cdecl gm_SetupEntityQuery(unsigned char*);
extern int __cdecl gm_FindBuildingPrimarySlot(unsigned char*);
extern void __cdecl io_FormatTextBuffer(char*, int, ...);
extern void __cdecl he_MessageBoxQuickjump(int, int, char*, int, int, int, int, char*, char*);

/* ADDRESS: GOLDTL 0x0056aef0 */
void __cdecl he_RunGebSpionage(char* action)
{
	char* e;
	char* q;
	char* h;
	char* h2;
	char* r;
	char* ent;
	char* u;
	int n;
	int v;
	int t;
	int k;
	int i;
	double d;
	float x;
	float amount;
	Msg56 m;
	char buf[0x400];

	q = 0;
	u = 0;
	switch (*(int*)(action + 0x70)) {
	case 0:
		h = (char*)gm_StartFilteredEntitySearch(1, 1, *(int*)(action + 0xac));
		if (h == 0) {
			*(int*)(action + 0x70) = -1;
			return;
		}
		for (n = 0; n < 8; n++) {
			e = (char*)gm_LookupEntityRecordById(((int*)(action + 0x8c))[n]);
			if (e != 0) {
				cm_SendCancelCharacterActions(*(int*)(e + 4));
				ch_StartMovement(*(int*)(e + 4), *(int*)(h + 1), -1, 0, 1, "GebSpionage");
				he_AssignActionSlot(h, 0, *(unsigned short*)e, action);
			}
		}
		*(pos14_7f4c00*)(action + 0x52) = gm_GameTime;
		gm_AddTime((pos14_7f4c00*)(action + 0x52), 0, 0xa, 0);
		*(int*)(action + 0x70) = 1;
		return;

	case 1:
		v = 1;
		h = (char*)gm_StartFilteredEntitySearch(1, 1, *(int*)(action + 0xac));
		if (h == 0) {
			*(int*)(action + 0x70) = -1;
			return;
		}
		for (n = 0; n < 8; n++) {
			e = (char*)gm_LookupEntityRecordById(((int*)(action + 0x8c))[n]);
			if (e != 0 && *(int*)(e + 0x184) != 0) {
				if (gm_IsEntityAtBuilding(e, h) == 0) {
					e = *(char**)(e + 0x184);
					if (*(int*)(e + 0x128) != 0) {
						v = 0;
					}
				}
			}
		}
		if (v != 0) {
			t = 0;
			k = 0;
			for (n = 0; n < 8; n++) {
				e = (char*)gm_LookupEntityRecordById(((int*)(action + 0x8c))[n]);
				if (e != 0) {
					t += gm_GetScaledEntitySkill(e, 2);
					k++;
				}
			}
			if (k == 0) {
				he_FreeAction(action);
				return;
			}
			t = t / k;
			d = (1.0 > (double)t) ? 1.0 : (double)t;
			h = (char*)gm_StartFilteredEntitySearch(1, 1, *(int*)(action + 0xac));
			if (h == 0) {
				*(int*)(action + 0x70) = -1;
				return;
			}
			v = fcn_0050c4e0((unsigned char*)h);
			x = (float)(v * 120.0);
			x = x * (252.0f / (int)d) / k;
			if (2880.0f < x) {
				x = 2880.0f;
			}
			*(pos14_7f4c00*)(action + 0x44) = gm_GameTime;
			*(pos14_7f4c00*)(action + 0x52) = gm_GameTime;
			gm_AddTime((pos14_7f4c00*)(action + 0x52), 0, (int)x, 0);
			*(int*)(action + 0x70) = 2;
			return;
		}
		*(pos14_7f4c00*)(action + 0x52) = gm_GameTime;
		gm_AddTime((pos14_7f4c00*)(action + 0x52), 0, 5, 0);
		return;

	case 2:
		h = (char*)gm_StartFilteredEntitySearch(1, 1, *(int*)(action + 0xb0));
		if (h == 0) {
			*(int*)(action + 0x70) = -1;
			return;
		}
		ent = (char*)gm_LookupEntityRecordById(((ENTITY_RECORD*)g_7f4ca0)[*(unsigned short*)(h + 0x27)].entity_id);
		q = (char*)gm_SetupEntityQuery((unsigned char*)h);
		t = 0;
		k = 0;
		for (n = 0; n < 8; n++) {
			e = (char*)gm_LookupEntityRecordById(((int*)(action + 0x8c))[n]);
			if (e != 0) {
				t += gm_GetScaledEntitySkill(e, 2);
				u = e;
				cm_SendCancelCharacterActions(((int*)(action + 0x8c))[n]);
				ch_StartMovement(((int*)(action + 0x8c))[n], *(int*)(h + 1), *(int*)(q + 2), 0, 0, "GebSpionage");
				he_AssignActionSlot(h, 0, *(unsigned short*)e, 0);
				k++;
			}
		}
		if (k == 0) {
			he_FreeAction(action);
			return;
		}
		t = t / k;
		t = (int)((42.0f > t) ? 42.0f : t);
		h2 = (char*)gm_StartFilteredEntitySearch(1, 1, *(int*)(action + 0xac));
		if (h2 == 0) {
			*(int*)(action + 0x70) = -1;
			return;
		}
		r = (char*)&((ENTITY_RECORD*)g_7f4ca0)[*(unsigned short*)(h2 + 0x27)];
		q = (char*)fcn_00502cd0(*(int*)(h2 + 0x5d), 2, 6, 0, 0x2a);
		i = gm_WalkEntityChain(*(unsigned short*)r);
		if (i >= 1600000) {
			i = 1600000;
		}
		m.f12 = (int)(i * 0.1);
		v = 0;
		if (q != 0) {
			e = (char*)fcn_00502cd0(*(int*)(q + 0x14), 1, 5);
			while (e != 0) {
				amount = (float)gm_GetMsgField(q, e);
				amount = fcn_0050bb50(*(unsigned short*)e, g_773d75) * amount;
				v = (int)(amount + v);
				e = (char*)gm_NextEntityQueryMatch();
			}
		}
		amount = (float)k * t * 0.25f;
		k = (int)(amount / fcn_0050c4e0((unsigned char*)h2));
		k = k + (gm_RandomMod(4) & 0xffff) - 2;
		if (k > 100) {
			k = 100;
		} else if (k < 2) {
			k = 2;
		}
		m.stamp = gm_GameTime;
		m.f0e = *(int*)(h2 + 1);
		m.f16 = v;
		m.f1a = (char)gm_GetBuildingTechEffect((unsigned char*)h2, 7, 1);
		m.f1b = (char)k;
		cm_RequestAllocWarEvent(h, (char*)&m);
		if (*(char*)(ent + 2) == 6 || *(char*)(ent + 2) == 7) {
			e = (char*)fcn_0050dc90(h);
			if (u != 0) {
				if (e == 0 || (e[0x1b4] & 1) == 0) {
					io_FormatTextBuffer(buf, 0x19f8, *(unsigned short*)u, *(unsigned short*)r, h2);
					i = gm_FindBuildingPrimarySlot((unsigned char*)h);
					he_MessageBoxQuickjump(*(int*)(ent + 4), *(int*)(ent + 4), buf, 1, 0x5f0,
						*(int*)(action + 0xb0), *(int*)((char*)i + 2), 0, "_NACHRICHTEN_HS_78");
				}
			}
		}
		he_FreeAction(action);
		return;

	case -2:
	case -1:
		h = (char*)gm_StartFilteredEntitySearch(1, 1, *(int*)(action + 0xb0));
		if (h != 0) {
			q = (char*)gm_SetupEntityQuery((unsigned char*)h);
		}
		for (n = 0; n < 8; n++) {
			e = (char*)gm_LookupEntityRecordById(((int*)(action + 0x8c))[n]);
			if (e != 0) {
				cm_SendCancelCharacterActions(((int*)(action + 0x8c))[n]);
				if (h != 0) {
					ch_StartMovement(((int*)(action + 0x8c))[n], *(int*)(h + 1), *(int*)(q + 2), 0, 0, "GebSpionage");
				}
				he_AssignActionSlot(0, 0, *(unsigned short*)e, 0);
			}
		}
		he_FreeAction(action);
		return;

	default:
		break;
	}
	he_FreeAction(action);
}
