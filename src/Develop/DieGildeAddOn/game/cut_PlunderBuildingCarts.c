/* Sums the price of the entities resolved from a building's three linked
 * entries and books the result on the player's record. */

extern char* g_772e98;
extern char* cut_CombatDefenderEntity;
extern unsigned char gm_ActiveTownIndex;
extern double g_662908;
extern float flt_1_0;

char* __cdecl fcn_00502cd0(int, ...);
short* __cdecl gm_ResolveParentEntity(short*);
void* __cdecl gm_NextEntityQueryMatch(void);
short* __cdecl gm_GetEntityTableEntry(char*);
float __cdecl gm_GetSeasonPrice(int, unsigned char);
void __cdecl cm_SendSellObjekt(int, int, int, int, unsigned char, int);
void __cdecl cm_RequestMoveCredits(int, int, char, int);

/* ADDRESS: GOLDTL 0x004d52a0 */
int __cdecl cut_PlunderBuildingCarts(int* cutscene, char* building, int* attacker,
    int unusedDefender, float scale)
{
	int total;
	int i;
	int soldQty;
	float v;
	char* rec;
	char* ent;
	int* p;

	total = 0;
	if (cut_CombatDefenderEntity == 0 || g_772e98 == 0) {
		return 0;
	}
	rec = fcn_00502cd0(*(int*) (building + 0x5d), 2, 6, 0, 0x116);
	p = (int*) ((char*) cutscene + 0x100);
	for (i = 3; i != 0; i--) {
		if (*p != -1) {
			ent = fcn_00502cd0(0, 2, 7, 1, *p);
			ent = fcn_00502cd0(*(int*) (ent + 0x14), 1, 0, 0x1dd);
			ent = fcn_00502cd0(*(int*) (ent + 0x14), 1, 5);
			while (ent != 0) {
				gm_ResolveParentEntity((short*) ent);
				v = (float) *(int*) (ent + 0xe) * scale;
				if (1.0f > v) {
					v = 1.0f;
				}
				soldQty = (int) v;
				if (rec != 0) {
					cm_SendSellObjekt(*(int*) (rec + 2), *(int*) (ent + 6),
					    *(unsigned short*) ent, soldQty, gm_ActiveTownIndex, 0);
				} else {
					cm_SendSellObjekt(-1, *(int*) (ent + 6),
					    *(unsigned short*) ent, soldQty, gm_ActiveTownIndex, 0);
				}
				total = (int) (gm_GetSeasonPrice(*(unsigned short*) ent, gm_ActiveTownIndex)
				    * (float) soldQty + (float) total);
				ent = gm_NextEntityQueryMatch();
			}
			if (rec == 0) {
				total = (int) ((double) total * 0.5);
				cm_RequestMoveCredits(attacker[1], -1, gm_ActiveTownIndex, total);
			}
			ent = gm_GetEntityTableEntry(cut_CombatDefenderEntity);
			if (ent != 0) {
				*(int*) (ent + 0x1c) += total;
			}
		}
		p++;
	}
	return total;
}
