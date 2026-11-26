#include "Develop/DieGildeAddOn/game/ambient_animal_slot.h"










#include "Develop/DieGildeAddOn/game/game_data.h"
extern char gm_GameTime[];
extern unsigned char g_776664;
extern volatile unsigned int g_6b7fac;
extern unsigned int g_7728f0;
extern int g_7728e4;
extern AMBIENT_ANIMAL_SLOT* g_7728e8;
extern int g_7728ec;

int __cdecl gm_GetSeason(char*);
void __cdecl d3_SelectSceneContext(int, int);
unsigned short __cdecl gm_RandomMod(unsigned short);
double __cdecl gm_RandomFloat01(void);
AMBIENT_ANIMAL_SLOT* __cdecl fcn_004bc010(void);
void __cdecl fcn_004bc060(AMBIENT_ANIMAL_SLOT*);
void __cdecl gm_InitAmbientBirds(AMBIENT_ANIMAL_SLOT*);
void __cdecl gm_SpawnAmbientCat(AMBIENT_ANIMAL_SLOT*);
void __cdecl ch_SpawnAmbientDog(AMBIENT_ANIMAL_SLOT*);
void __cdecl gm_SpawnAmbientSheep(AMBIENT_ANIMAL_SLOT*);
void __cdecl ch_SpawnAmbientCow(AMBIENT_ANIMAL_SLOT*);
void __cdecl fcn_004bc410(AMBIENT_ANIMAL_SLOT*, int);
void __cdecl fcn_004bc540(AMBIENT_ANIMAL_SLOT*);
void __cdecl fcn_004bc6b0(AMBIENT_ANIMAL_SLOT*);


/* Per-tick driver for the 32 ambient slots: may spawn one, then updates and
   retires the slot at the rotating cursor g_7728ec. */
/* ADDRESS: GOLDTL 0x004bbd70 */
void __cdecl fcn_004bbd70(void)
{
	int saved;
	int r;
	int lim;
	AMBIENT_ANIMAL_SLOT* s;

	saved = d3_CurrentContextIndex;
	r = gm_GetSeason(gm_GameTime);
	d3_SelectSceneContext(0, 1);
	if (g_776664 == 0) {
		lim = 0;
	} else {
		lim = g_776664 == 1 ? 0x10 : 0x20;
	}
	if (g_6b7fac > g_7728f0 + 0x15e) {
		if ((int) gm_RandomMod(lim * 2) - lim > g_7728e4 && r != 3) {
			s = fcn_004bc010();
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
					fcn_004bc410(s, 6);
					break;
				case 7:
					fcn_004bc410(s, 7);
					break;
				}
			}
		}
		g_7728f0 = g_6b7fac;
	}
	s = &g_7728e8[g_7728ec];
	if (s->objekt != 0) {
		switch (s->kind) {
		case 0:
		case 1:
			fcn_004bc540(s);
			break;
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
			fcn_004bc6b0(s);
			break;
		case 2:
			gm_InitAmbientBirds(s);
			break;
		}
		if (r == 3) {
			g_7728e8[g_7728ec].done = 1;
		}
		if (g_6b7fac > g_7728e8[g_7728ec].created_tick + 0x834 &&
		    gm_RandomFloat01() > (g_7728e8[g_7728ec].created_tick + 0x834) / (g_6b7fac - (g_7728e8[g_7728ec].created_tick + 0x834))) {
			g_7728e8[g_7728ec].done = 1;
		}
		s = &g_7728e8[g_7728ec];
		if (s->done != 0 &&
		    ((*(unsigned char*) (*(char**) (*(char**) (s->objekt + 0x34) + 0x1ec) + 0x163d) & 0x40) || r == 3 ||
		     g_7728e4 > lim)) {
			fcn_004bc060(s);
		}
	}
	d3_SelectSceneContext(saved, 1);
	g_7728ec = (g_7728ec + 1) % 32;
}
unsigned char _dpad_775318[4940];
