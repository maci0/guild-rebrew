__declspec(dllimport) unsigned long __stdcall timeGetTime(void);

extern int g_772f78;
extern int g_772f7c;
extern int g_772f80;
extern int g_772f84;
extern int g_772f88;
extern int g_772f8c;
extern int g_68dec0[];

void __cdecl srand(unsigned int seed);
unsigned short __cdecl gm_RandomMod(unsigned short n);
void __cdecl ahm_ShufflePlayerPrototypes(void);
#include "Develop/DieGildeAddOn/game/alchemy_player_prototype.h"

#include "Develop/DieGildeAddOn/game/game_data.h"
extern ALCHEMY_PLAYER_PROTOTYPE* ahm_PlayerPrototypes;

unsigned short __cdecl gm_RandomMod(unsigned short n);

extern int g_772fe0;
extern ALCHEMY_RECIPE_PROTOTYPE* ahm_RecipePrototypes;

unsigned short __cdecl gm_RandomMod(unsigned short n);
int __cdecl ahm_HasRecipeSlotCapacity(int p);
int __cdecl ahm_FindRecipeSlot(int p, int id);

/* ADDRESS: GOLD 0x004ead20 */
/* ADDRESS: GOLDTL 0x004ecaa0 */
/* ADDRESS: GOLDDE 0x004d8ef0 */
void __cdecl ahm_ResetAlchemyState(int reseed)
{
	if (reseed) {
		*(unsigned short*) &g_772f8c = (unsigned short) (timeGetTime() % 0x7fff + 1);
	}
	srand((unsigned short) g_772f8c);
	ahm_ShufflePlayerPrototypes();
	if (reseed) {
		g_772f78 = gm_RandomMod(0x19);
		g_772f7c = g_68dec0[gm_RandomMod(8)];
		g_772f80 = gm_RandomMod(0x19);
		g_772f84 = g_68dec0[gm_RandomMod(8)];
		g_772f88 = 0;
	}
}

/* ADDRESS: GOLD 0x004eadc0 */
/* ADDRESS: GOLDTL 0x004ecb40 */
/* ADDRESS: GOLDDE 0x004d8f90 */
void __cdecl ahm_ShufflePlayerPrototypes(void)
{
	int n;
	int i;
	int a;
	int b;
	ALCHEMY_PLAYER_PROTOTYPE tmp;

	n = ahm_PlayerPrototypeCount * 2;
	for (i = 0; i < n; i++) {
		a = gm_RandomMod((unsigned short) ahm_PlayerPrototypeCount);
		b = gm_RandomMod((unsigned short) ahm_PlayerPrototypeCount);
		if (a != b) {
			tmp = ahm_PlayerPrototypes[a];
			ahm_PlayerPrototypes[a] = ahm_PlayerPrototypes[b];
			ahm_PlayerPrototypes[b] = tmp;
		}
	}
}

/* ADDRESS: GOLD 0x004eaea0 */
/* ADDRESS: GOLDTL 0x004ecc20 */
/* ADDRESS: GOLDDE 0x004d9070 */
ALCHEMY_RECIPE_PROTOTYPE* __cdecl ahm_PickRandomUnknownRecipe(int player)
{
	int step;
	int idx;
	int n;

	if (ahm_HasRecipeSlotCapacity(player)) {
		step = gm_RandomMod((unsigned short) g_772fe0) + 1;
		while (step % g_772fe0 == 0) {
			step++;
		}
		idx = gm_RandomMod((unsigned short) g_772fe0);
		n = g_772fe0;
		while (n != 0) {
			if (!ahm_FindRecipeSlot(player, ahm_RecipePrototypes[idx].key)) {
				return &ahm_RecipePrototypes[idx];
			}
			n--;
			idx = (idx + step) % g_772fe0;
		}
	}
	return 0;
}
