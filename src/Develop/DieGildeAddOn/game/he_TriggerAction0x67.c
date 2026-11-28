


// SIZE 0xf8
#include "Develop/client_types.h"
struct msg {
	char pad0[4];
	unsigned char kind;
	char pad5[3];
	int player;
	int target;
	char pad10[0x18];
	pos14_7f4c00 when;
	unsigned char mode;
	char pad37[0x21];
	int who;
	int amount;
	char pad60[0x98];
};

// SIZE 0x24
struct stats {
	char pad0[0x18];
	int level;
	char pad1c[8];
};

extern pos14_7f4c00 gm_GameTime;
extern char* gm_CityEntity;

extern float g_6629c0;
extern float g_6628cc;
extern float flt_1_0;

unsigned short __cdecl gm_RandomMod(int);
void* __cdecl he_StartHandlungSearch(int, ...);
char* __cdecl gm_StartFilteredEntitySearch(int, ...);
void __cdecl gm_GetLawEntry(int, struct stats*);
int __cdecl gm_CalculateGebaeudeValue(char*, int);
float __cdecl gm_RandomFloat01(void);
void __cdecl cm_SendCopyEntityData(struct msg*);

void __cdecl he_TriggerAction0x67(void)
{
	char* cand[3];
	struct stats info;
	struct msg m;
	char* a;
	char* b;
	char* c;
	char* pick;
	int n;
	int amount;
	int idx;

	if (gm_GameTime.a < 8) {
		return;
	}
	if (gm_RandomMod(4) != 0) {
		return;
	}
	if (he_StartHandlungSearch(1, 0, 0x67) != 0) {
		return;
	}
	a = gm_StartFilteredEntitySearch(1, 0, 0x20);
	b = gm_StartFilteredEntitySearch(1, 0, 0x1e);
	c = gm_StartFilteredEntitySearch(1, 0, 0x1f);
	n = 0;
	if (a != 0 && *(short*) (a + 0x27) == *(short*) gm_CityEntity) {
		cand[n++] = a;
	}
	if (b != 0 && *(short*) (b + 0x27) == *(short*) gm_CityEntity) {
		cand[n++] = b;
	}
	if (c != 0 && *(short*) (c + 0x27) == *(short*) gm_CityEntity) {
		cand[n++] = c;
	}
	if (n == 0) {
		return;
	}
	idx = gm_RandomMod(n);
	gm_GetLawEntry(7, &info);
	pick = cand[idx];
	amount = (int) ((*(int*) (pick + 0x65) + *(int*) (pick + 0x69)) * (((5 - info.level) * 0.1f + g_6629c0) * g_6628cc));
	m.kind = 0x67;
	m.when = gm_GameTime;
	m.player = *(int*) (gm_CityEntity + 4);
	m.target = *(int*) (pick + 1);
	m.who = *(int*) (pick + 1);
	m.amount = *(int*) (pick + 0x69) + amount;
	if (m.amount <= 0) {
		n = gm_CalculateGebaeudeValue(pick, 0x64);
		m.amount = (int) ((gm_RandomFloat01() + 1.0f) * n);
	}
	m.mode = 2;
	cm_SendCopyEntityData(&m);
}
