typedef struct Ent {
	unsigned short id;
	char pad2[2];
	int seed;
	char pad8[0x1c8 - 8];
	int flags;
	char pad1cc[0x21c - 0x1cc];
} Ent;
// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"
extern char g_7f4ca0[];

unsigned short __cdecl gm_RandomMod(int n);
int __cdecl ai_SelectRankedCandidates(char* e, int n, int* lim, float a4, float r, unsigned short* ids);
#include "Develop/DieGildeAddOn/game/spiel.h"
float __cdecl gm_RandomFloat01(void);

/* ADDRESS: GOLDTL 0x004a9600 */
int __cdecl ai_PreparePrivWerbung(int unused1, char* actor, int unused3, int unused4, char* out)
{
	int mask;
	unsigned short targetId;
	float duelScore;

	if (*(int*) (actor + 0x194) >= 3 && !(*(int*) (actor + 0x1c8) & 0x400)) {
		mask = 0xf00500;
		if (ai_SelectRankedCandidates(actor, 1, &mask, 0.0f, (float) gm_RandomMod(0x20) + 18.0f, &targetId) &&
		    !(((Ent *)&((ENTITY_RECORD_VIEW *)g_7f4ca0)[targetId])->flags & 0x400)) {
			duelScore = gm_CalcSkillDuelScore(actor, (char*) &((Ent*)g_7f4ca0)[targetId], 3);
			if (gm_RandomFloat01() + duelScore >= 1.0f) {
				out[0] = 7;
				*(int*) (out + 4) = ((Ent *)&((ENTITY_RECORD_VIEW *)g_7f4ca0)[targetId])->seed;
				return 1;
			}
		}
	}
	return 0;
}
