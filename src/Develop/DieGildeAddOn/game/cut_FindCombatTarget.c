extern char* ch_ContextCharacters[32];

char* __cdecl gm_GetEquippedCombatGear(char*);
int __cdecl gm_EntitiesDifferByOwnerPtr(char*, unsigned char*);
float __cdecl gm_CalcEntityFlatDistance(char*, int);
float __cdecl gm_GetEntityHealthRatio(unsigned char*);


/* ADDRESS: GOLDTL 0x004d2f70 */
unsigned char* __cdecl cut_FindCombatTarget(char* actor)
{
	float best;
	float d;
	unsigned char* e;
	unsigned char* result;
	int i;

	best = 1000000.0f;
	result = 0;
	if (*(int*) (gm_GetEquippedCombatGear(actor) + 0x58) != 2) {
		for (i = 0; i < 32; i++) {
			e = ((unsigned char**)ch_ContextCharacters)[i];
			if (e != 0 && gm_EntitiesDifferByOwnerPtr(actor, e) != 0 && e[8] != 0) {
				d = gm_CalcEntityFlatDistance(actor, *(int*) (*(char**) (e + 0x184) + 0x34));
				if (d * gm_GetEntityHealthRatio(e) < best) {
					best = d;
					result = ((unsigned char**)ch_ContextCharacters)[i];
				}
			}
		}
	} else {
		for (i = 0; i < 32; i++) {
			e = ((unsigned char**)ch_ContextCharacters)[i];
			if (e != 0 && gm_EntitiesDifferByOwnerPtr(actor, e) != 0 && e[8] != 0) {
				d = gm_CalcEntityFlatDistance(actor, *(int*) (*(char**) (e + 0x184) + 0x34));
				if (d * gm_GetEntityHealthRatio(e) < best) {
					best = d;
					result = ((unsigned char**)ch_ContextCharacters)[i];
				}
			}
		}
	}
	return result;
}
