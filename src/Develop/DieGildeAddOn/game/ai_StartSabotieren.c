#include <string.h>

typedef struct Stat {
	int v[9];
} Stat;
/* SIZE 0x24 */

typedef struct Msg {
	unsigned char kind;
	char pad1[3];
	int a;
	int b;
	int c;
	int d;
	float f;
} Msg;
/* SIZE 0x18 */

typedef struct F8 {
	int mask;
	int b;
} F8;
/* SIZE 0x8 */

extern unsigned char gm_ActiveTownIndex;
extern char* ai_FeudTargetEntity;
extern char gm_EntitySlotTable[];

int __cdecl gm_GetSeasonTreasury(char* e, unsigned char flag);
int __cdecl ai_SelectBestMethod(int kind, int id, int n, Msg* b1, Msg* b2);
int __cdecl gm_QueryEntities(int a, int b, int c, int d, int e);
void __cdecl gm_GetLawEntry(int size, Stat* st);
unsigned short __cdecl gm_RandomMod(int a);
int __cdecl ai_FindEntityInFavorRange(char* p, int kind, F8 f, int c, float r, int* out);
void __cdecl gm_ResolveEntityById(int* out, int a, int b, int id);
int __cdecl he_HasNoActiveAction0x88(char* obj, char* e);
int __cdecl gm_CalculateGebaeudeValue(int* p, int n);
int __cdecl gm_WalkEntityChain(unsigned short id);
int __cdecl gm_CheckPrivilege(int a, char* e, void* buf);
float __cdecl gm_CalcSkillDuelScore(char* a, char* b, int i);
float __cdecl gm_RandomFloat01(void);
int __cdecl he_HasNoActiveEvent04b(char* obj, char* e);
int __cdecl he_HasNoActiveAction0x2e(char* obj, char* e);
int __cdecl he_HasNoActiveAction0x62(int* p);

/* ADDRESS: GOLDTL 0x00499090 */
int __cdecl ai_StartSabotieren(int who, char* entity, int busy, Msg* out1, Msg* out2)
{
	int targetRec;
	int v4;
	int v8;
	int id;
	Msg b1;
	Msg b2;
	Stat st;
	int buf[0x88];
	char* owner;
	F8 ff;
	int r;

	v8 = gm_GetSeasonTreasury(entity, gm_ActiveTownIndex);
	if (busy != 0) {
		return 0;
	}
	if (*(int*)(entity + 0x170) == 0 && entity[2] != 3) {
		b1.kind = 0;
		b1.a = 0;
		b1.b = 0;
		b2.kind = 0;
		b2.a = 0;
		b2.b = 0;
		r = ai_SelectBestMethod(0x17, *(unsigned short*)entity, 1, &b1, &b2);
		if (r != 0) {
			*out1 = b1;
			*out2 = b2;
		}
		return r;
	}
	if (entity[2] == 3) {
		if ((entity[0x1e8] & 2) == 0) {
			return 0;
		}
	} else if (gm_QueryEntities(*(int*)(*(int*)(entity + 0x170) + 0x5d), 2, 6, 0, 0x14) == 0) {
		b1.kind = 2;
		b1.a = 0x14;
		b1.b = 1;
		b1.f = 0.22f;
		b2.kind = 4;
		b2.a = *(int*)(*(int*)(entity + 0x170) + 1);
		b2.b = 1;
		r = ai_SelectBestMethod(0x17, *(unsigned short*)entity, 1, &b1, &b2);
		if (r != 0) {
			*out1 = b1;
			*out2 = b2;
		}
		return r;
	}
	gm_GetLawEntry(0x18, &st);
	if (st.v[6] != 0 && gm_RandomMod(4) == 0 && ai_FeudTargetEntity == 0) {
		return 0;
	}
	if (out1->kind == 0) {
		ff.mask = 0x344015;
		ff.b = 1;
		id = -1;
		if (ai_FeudTargetEntity != 0) {
			ai_FindEntityInFavorRange(ai_FeudTargetEntity, 4, ff, 0, 100.0f, &id);
		}
		if (id != -1 || ai_FindEntityInFavorRange(entity, 6, ff, 0, (float)gm_RandomMod(0x20) + 19.0f, &id) != 0) {
			gm_ResolveEntityById(&targetRec, 0, 0, id);
			if (targetRec != 0) {
				if (*(unsigned short*)(targetRec + 0x27) != 0xffff) {
					if (he_HasNoActiveAction0x88(gm_EntitySlotTable + *(unsigned short*)(targetRec + 0x27) * 0x21c, entity) != 0) {
						memset(buf, 0, 0x220);
						buf[0] = 1;
						v4 = (int)((float)gm_CalculateGebaeudeValue((int*)targetRec, 100) * 0.05f + (float)gm_WalkEntityChain(*(unsigned short*)entity) * 0.02f);
						owner = gm_EntitySlotTable + *(unsigned short*)(targetRec + 0x27) * 0x21c;
						if ((gm_CheckPrivilege(0x1b, entity, buf) & 2) != 0) {
							v4 = v4 / 2;
						}
						if (!((float)v8 * 0.44f < (float)v4)) {
							if (!(gm_CalcSkillDuelScore(entity, owner, 2) + gm_RandomFloat01() >= 1.0f)) {
								b1.kind = 0xe;
								b1.a = 2;
								b1.b = 1;
								b1.f = 0;
								b2.kind = 0;
								b2.a = 0;
								b2.b = 0;
								r = ai_SelectBestMethod(0x17, *(unsigned short*)entity, 0, &b1, &b2);
								if (r != 0) {
									*out1 = b1;
									*out2 = b2;
								}
								return r;
							}
							if (he_HasNoActiveEvent04b(gm_EntitySlotTable + *(unsigned short*)(targetRec + 0x27) * 0x21c, entity) != 0) {
								if (he_HasNoActiveAction0x2e(gm_EntitySlotTable + *(unsigned short*)(targetRec + 0x27) * 0x21c, entity) != 0) {
									if (he_HasNoActiveAction0x62((int*)targetRec) != 0) {
										if (he_HasNoActiveAction0x88(gm_EntitySlotTable + *(unsigned short*)(targetRec + 0x27) * 0x21c, entity) != 0) {
											out1->kind = 4;
											out1->a = *(int*)(targetRec + 1);
											out1->d = v4;
											out1->b = 1;
											out1->f = (float)(st.v[6] * 2 + 1);
											return 0x17;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return 0;
}
