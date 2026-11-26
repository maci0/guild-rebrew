typedef struct Cmd {
	int op;
	int id;
	char pad8[0x14];
	int level;
} Cmd;
// SIZE 0x20

typedef struct Spec {
	char pad0[0x14];
	int need;
} Spec;
// SIZE 0x18

extern char g_774964;
extern int g_7728d8;
extern signed char g_6a3440;

Spec* __cdecl gm_LookupMissionSpec(int op);
char* __cdecl gm_LookupEntityRecordById(int id);
int __cdecl ai_ExceedsEntityGoldThreshold(char* t, Spec* s);
int __cdecl gm_CheckStatRankThreshold(char* t, Spec* s);
int __cdecl ai_FilterRankCandidateLimit(char* t, Cmd* c, Spec* s);
int __cdecl gm_HasMinDynastyWealth(char* t, Spec* s);
int __cdecl gm_HasMinEntityGold(char* t, Spec* s);
int __cdecl gm_HasSkillThreshold(char* t, Spec* s);
int __cdecl gm_HasMissionOfficeWithinLimit(char* t, Cmd* c, Spec* s);
int __cdecl gm_HasMatureCategory2Building(char* t, Spec* s);
int __cdecl gm_HasThreeFullyEquippedBuildings(char* t, Spec* s);
int __cdecl fcn_004b49a0(char* t, Spec* s);
int __cdecl fcn_004b49e0(char* t, Spec* s);
int __cdecl fcn_004b4a20(char* t, Spec* s);
int __cdecl gm_HasMinOwnedEntityPercent(char* t, Spec* s);
int __cdecl gm_HasEntityTypes13AndOptionalOwnership(char* t, Spec* s);
int __cdecl gm_HasThreeEntityHoldings(char* t, Spec* s);
int __cdecl gm_HasThreeType7Entities(char* t, Cmd* c, Spec* s);
int __cdecl gm_HasBuildingGroupMonopoly(char* t, Spec* s);
int __cdecl gm_HasAllCategoryBuildings(char* t, Cmd* c, Spec* s);
int __cdecl gm_CheckCityStatThresholds(char* t, Spec* s);
int __cdecl gm_CheckEconomyCandidateLimit(char* t, Cmd* c, Spec* s);
int __cdecl gm_HasMinBuildingOwnershipShare(char* t, Spec* s);
int __cdecl gm_HasZeroLaw0x11To1cSum(char* t, Spec* s);
int __cdecl gm_HasNoType5Owner(char* t, Spec* s);

/* ADDRESS: GOLD 0x004b4f00 */
/* ADDRESS: GOLDTL 0x004b5070 */
int __cdecl gm_CheckMissionCondition(Cmd* c)
{
	Spec* s;
	char* t;

	s = gm_LookupMissionSpec(c->op);
	if (g_774964 == 0 || s == 0) {
		return 0;
	}
	if (g_7728d8 == 1 && g_6a3440 >= 0 && g_6a3440 <= 5) {
		g_7728d8 = 0;
		return 1;
	}
	t = gm_LookupEntityRecordById(c->id);
	if (t == 0) {
		return 0;
	}
	switch (c->op) {
	case 1:
	case 6:
	case 14:
	case 22:
	case 32:
		return ai_ExceedsEntityGoldThreshold(t, s);
	case 2:
	case 7:
		return gm_CheckStatRankThreshold(t, s);
	case 3:
	case 10:
	case 24:
		return ai_FilterRankCandidateLimit(t, c, s);
	case 5:
	case 13:
	case 21:
	case 30:
		return gm_HasMinDynastyWealth(t, s);
	case 31:
		return gm_HasMinEntityGold(t, s);
	case 4:
	case 9:
	case 29:
		return gm_HasSkillThreshold(t, s);
	case 15:
	case 16:
	case 17:
	case 18:
	case 34:
	case 35:
		return gm_HasMissionOfficeWithinLimit(t, c, s);
	case 11:
	case 19:
	case 23:
	case 28:
	case 40:
		return c->level >= s->need;
	case 8:
		return gm_HasMatureCategory2Building(t, s);
	case 12:
		return gm_HasThreeFullyEquippedBuildings(t, s);
	case 20:
	case 25:
	case 36:
		return fcn_004b49a0(t, s);
	case 26:
	case 37:
		return fcn_004b49e0(t, s);
	case 27:
		return fcn_004b4a20(t, s);
	case 41:
		return gm_HasMinOwnedEntityPercent(t, s);
	case 39:
		return gm_HasEntityTypes13AndOptionalOwnership(t, s);
	case 38:
		return gm_HasThreeEntityHoldings(t, s);
	case 33:
		return gm_HasThreeType7Entities(t, c, s);
	case 43:
		return gm_HasBuildingGroupMonopoly(t, s);
	case 44:
		return gm_HasAllCategoryBuildings(t, c, s);
	case 45:
		return gm_CheckCityStatThresholds(t, s);
	case 46:
		return gm_CheckEconomyCandidateLimit(t, c, s);
	case 47:
		return gm_HasMinBuildingOwnershipShare(t, s);
	case 48:
		return gm_HasZeroLaw0x11To1cSum(t, s);
	case 49:
		return gm_HasNoType5Owner(t, s);
	}
	return 0;
}
