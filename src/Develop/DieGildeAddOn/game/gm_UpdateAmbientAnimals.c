#include "Develop/DieGildeAddOn/game/ambient_animal_slot.h"










#include "Develop/DieGildeAddOn/game/game_data.h"
extern char gm_GameTime[];
extern unsigned char d3_GfxDetails;
extern volatile unsigned int gm_GameTicks;
extern unsigned int g_7728f0;
extern int g_7728e4;
extern AMBIENT_ANIMAL_SLOT* g_7728e8;
extern int g_7728ec;

int __cdecl gm_GetSeason(char*);
void __cdecl d3_SelectSceneContext(int, int);
unsigned short __cdecl gm_RandomMod(unsigned short);
double __cdecl gm_RandomFloat01(void);
AMBIENT_ANIMAL_SLOT* __cdecl gm_AllocAmbientAnimalSlot(void);
void __cdecl gm_DestroyAmbientAnimal(AMBIENT_ANIMAL_SLOT*);
void __cdecl gm_InitAmbientBirds(AMBIENT_ANIMAL_SLOT*);
void __cdecl gm_SpawnAmbientCat(AMBIENT_ANIMAL_SLOT*);
void __cdecl ch_SpawnAmbientDog(AMBIENT_ANIMAL_SLOT*);
void __cdecl gm_SpawnAmbientSheep(AMBIENT_ANIMAL_SLOT*);
void __cdecl ch_SpawnAmbientCow(AMBIENT_ANIMAL_SLOT*);
void __cdecl ch_SpawnAmbientLivestock(AMBIENT_ANIMAL_SLOT*, int);
void __cdecl anm_UpdateCat(AMBIENT_ANIMAL_SLOT*);
void __cdecl anm_UpdateSheep(AMBIENT_ANIMAL_SLOT*);


/* Per-tick driver for the 32 ambient slots: may spawn one, then updates and
   retires the slot at the rotating cursor g_7728ec. */
/* ADDRESS: GOLDTL 0x004bbd70 */
void __cdecl gm_UpdateAmbientAnimals(void)
{
	int saved;
	int r;
	int lim;
	AMBIENT_ANIMAL_SLOT* s;

	saved = d3_CurrentContextIndex;
	r = gm_GetSeason(gm_GameTime);
	d3_SelectSceneContext(0, 1);
	if (d3_GfxDetails == 0) {
		lim = 0;
	} else {
		lim = d3_GfxDetails == 1 ? 0x10 : 0x20;
	}
	if (gm_GameTicks > g_7728f0 + 0x15e) {
		if ((int) gm_RandomMod(lim * 2) - lim > g_7728e4 && r != 3) {
			s = gm_AllocAmbientAnimalSlot();
			if (s != 0) {
				switch (gm_RandomMod(100) > 30 ? gm_RandomMod(5) + 3 : gm_RandomMod(2)) {
				case 1:
					gm_SpawnAmbientCat(s);
					break;
				case 0:
					ch_SpawnAmbientDog(s);
					break;
				case 4:
					gm_SpawnAmbientSheep(s);
					break;
				case 3:
					ch_SpawnAmbientCow(s);
					break;
				case 6:
					ch_SpawnAmbientLivestock(s, 6);
					break;
				case 7:
					ch_SpawnAmbientLivestock(s, 7);
					break;
				}
			}
		}
		g_7728f0 = gm_GameTicks;
	}
	s = &g_7728e8[g_7728ec];
	if (s->objekt != 0) {
		switch (s->kind) {
		case 0:
		case 1:
			anm_UpdateCat(s);
			break;
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
			anm_UpdateSheep(s);
			break;
		case 2:
			gm_InitAmbientBirds(s);
			break;
		}
		if (r == 3) {
			g_7728e8[g_7728ec].done = 1;
		}
		if (gm_GameTicks > g_7728e8[g_7728ec].created_tick + 0x834 &&
		    gm_RandomFloat01() > (g_7728e8[g_7728ec].created_tick + 0x834) / (gm_GameTicks - (g_7728e8[g_7728ec].created_tick + 0x834))) {
			g_7728e8[g_7728ec].done = 1;
		}
		s = &g_7728e8[g_7728ec];
		if (s->done != 0 &&
		    ((*(unsigned char*) (*(char**) (*(char**) (s->objekt + 0x34) + 0x1ec) + 0x163d) & 0x40) || r == 3 ||
		     g_7728e4 > lim)) {
			gm_DestroyAmbientAnimal(s);
		}
	}
	d3_SelectSceneContext(saved, 1);
	g_7728ec = (g_7728ec + 1) % 32;
}
unsigned char _dpad_775318[4940];
