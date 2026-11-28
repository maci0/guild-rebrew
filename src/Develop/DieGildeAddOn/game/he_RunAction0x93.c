#include "Develop/DieGildeAddOn/game/game_timestamp.h"
/* SIZE 0xe */








/* SIZE 0xf8 */
typedef struct {
	char pad0[4];
	unsigned char kind;
	char pad5[3];
	int owner;
	int target;
	char pad10[0x18];
	GAME_TIMESTAMP at;
	unsigned char code;
	char pad37[0x21];
	unsigned char who;
	char pad59[3];
	int other;
	char pad60[0x98];
} Msg5;

extern char gm_EntitySlotTable[];
extern float g_662a70;
extern float g_662a6c;
extern double g_662908;

char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
char* __cdecl gm_FindNextFilteredEntity(void);
int __cdecl gm_GetBuildingTechEffect(char* e, int a, int b);
char* __cdecl gm_FindBuildingOwner(char* e);
float __cdecl gm_RandomFloat01(void);
unsigned short __cdecl gm_RandomMod(unsigned short n);
int __cdecl gm_GetEntityRelation(int a, int b);
void __cdecl he_SetEntityScriptFlag(char* s, int v);
void __cdecl cm_SendCopyEntityData(Msg5* m);
void __cdecl gm_AddTime(GAME_TIMESTAMP* t, int a, int b, int c);
void __cdecl he_FreeAction(char* e);

/* ADDRESS: GOLDTL 0x0057b390 */
void __cdecl he_RunAction0x93(char* e)
{
	int count;
	float lim;
	Msg5 m;
	char* list[0x20];
	char* u;
	char* cur;
	char* s;
	int p;
	int k;
	int n;
	int d;
	float r;

	switch (*(int*) (e + 0x70)) {
	case 0:
		u = gm_StartFilteredEntitySearch(1, 5, 0x1d);
		while (u != 0) {
			if (*(unsigned short*) (u + 0x27) != 0xffff) {
				lim = (float) gm_GetBuildingTechEffect(u, 0x15, 1) * 0.0025f;
				count = 0;
				for (p = 0x7f4ca0; p < 0x85a0a0; p += 0x21c) {
					if (*(unsigned short*) p != 0xffff && *(int*) (p + 0x16c) == (int) u) {
						list[count++] = (char*) p;
					}
				}
				for (k = 0; k < count; k++) {
					r = gm_RandomFloat01();
					if (r > lim + 0.75f) {
						s = list[k];
						if (!(*(unsigned char*) (s + 0x1b4) & 1) &&
						    (*(unsigned char*) (s + 0x180) == 4 ||
						     *(unsigned char*) (s + 0x180) == 0x8c ||
						     *(unsigned char*) (s + 0x180) == 0x8d)) {
							he_SetEntityScriptFlag(s, 1);
						}
					} else if (r > 0.5) {
						s = list[k];
						if (*(int*) (s + 0x17c) == 0) {
							d = gm_GetEntityRelation(*(unsigned short*) (u + 0x27), *(unsigned short*) s);
							if (-gm_RandomMod(0x4a) < d) {
								memset(&m, 0, sizeof(m));
								m.owner = *(unsigned short*) (e + 8);
								m.target = *(int*) (u + 1);
								m.kind = 0x94;
								m.at = *(GAME_TIMESTAMP*) &gm_GameTime;
								m.code = 1;
								*(int*) &m.who = *(int*) (s + 4);
								cm_SendCopyEntityData(&m);
							}
						}
					}
				}
				u = gm_FindNextFilteredEntity();
			}
		}
		break;
	case 1:
		u = gm_StartFilteredEntitySearch(1, 5, 0x1d);
		while (u != 0) {
			count = 0;
			cur = gm_FindBuildingOwner(u);
			for (p = 0x7f4ca0; p < 0x85a0a0; p += 0x21c) {
				if (*(unsigned short*) p != 0xffff && *(int*) (p + 0x16c) == (int) u) {
					list[count++] = (char*) p;
				}
			}
			gm_GetBuildingTechEffect(u, 0x15, 1);
			for (k = 0; k < count; k++) {
				s = list[k];
				if ((*(unsigned char*) (s + 0x1b4) & 1) &&
				    (*(unsigned char*) (s + 0x180) == 4 ||
				     *(unsigned char*) (s + 0x180) == 0x8c ||
				     *(unsigned char*) (s + 0x180) == 0x8d ||
				     *(unsigned char*) (s + 0x180) == 0) &&
				    (cur == 0 || cur != s)) {
					if (gm_RandomFloat01() > 0.75f) {
						he_SetEntityScriptFlag(s, 0);
					} else if (cur != 0 && (*(unsigned char*) (cur + 0x1b4) & 1) &&
						   *(int*) (s + 0x184) != 0) {
						he_SetEntityScriptFlag(s, 0);
					}
				}
			}
			u = gm_FindNextFilteredEntity();
		}
		break;
	case 2:
		*(GAME_TIMESTAMP*) (e + 0x52) = *(GAME_TIMESTAMP*) &gm_GameTime;
		gm_AddTime((GAME_TIMESTAMP*) (e + 0x52), 0, 0x1e, 0);
		*(int*) (e + 0x70) += 1;
		return;
	case 3:
		*(GAME_TIMESTAMP*) (e + 0x52) = *(GAME_TIMESTAMP*) &gm_GameTime;
		gm_AddTime((GAME_TIMESTAMP*) (e + 0x52), 0, 0x1e, 0);
		*(int*) (e + 0x70) = 0;
		return;
	case -1:
	case -2:
		he_FreeAction(e);
		return;
	default:
		return;
	}
	*(GAME_TIMESTAMP*) (e + 0x52) = *(GAME_TIMESTAMP*) &gm_GameTime;
	gm_AddTime((GAME_TIMESTAMP*) (e + 0x52), 0, gm_RandomMod(0x14) + 0x14, 0);
	*(int*) (e + 0x70) += 1;
}
