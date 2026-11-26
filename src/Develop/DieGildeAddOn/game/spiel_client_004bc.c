#include <string.h>
#include "Develop/DieGildeAddOn/game/ambient_animal_slot.h"

extern int g_67a370;

unsigned short __cdecl gm_RandomMod(unsigned short);
int __cdecl ch_QueuePlayAnimation(char*, char*, int);
int __cdecl ch_GenerateNearbyWalkablePoints(int*, int, float*);
char __cdecl fcn_0045b990(int, float*, int*, int*, int*);
char* __cdecl ch_CreateAction(char*, int, int, int, int);

unsigned short __cdecl gm_RandomMod(unsigned short);
int __cdecl ch_QueuePlayAnimation(char*, char*, int);
int __cdecl ch_GenerateNearbyWalkablePoints(int*, int, float*);
char __cdecl fcn_0045b990(int, float*, int*, int*, int*);
char* __cdecl ch_CreateAction(char*, int, int, int, int);

/* ADDRESS: GOLDTL 0x004bc540 */
void __cdecl fcn_004bc540(AMBIENT_ANIMAL_SLOT* state)
{
	int x;
	int g;
	int y;
	int z;
	float pts[8][4];
	float* pt;
	int n;
	char* o;

	if (*(int*) (state->objekt + 0x128) != 0)
		return;
	if (gm_RandomMod(0x64) > 0x1e) {
		if (state->kind == 0) {
			if (gm_RandomMod(0x64) > 0x32)
				ch_QueuePlayAnimation(state->objekt, "bewegung/stehen", gm_RandomMod(3) + 1);
			else
				ch_QueuePlayAnimation(state->objekt, "bewegung/bellen", gm_RandomMod(3) + 1);
		} else {
			ch_QueuePlayAnimation(state->objekt, "bewegung/stehen", gm_RandomMod(3) + 1);
		}
		return;
	}
	g = *(int*) (((char*)g_67a370) + 0xb0);
	n = gm_RandomMod(3) + 1;
	n = ch_GenerateNearbyWalkablePoints((int*) state->pos, n, pts[0]);
	if (n <= 0)
		return;
	for (pt = pts[0]; n != 0; n--, pt += 4) {
		if (fcn_0045b990(g, pt, &x, &y, &z) != 0) {
			o = ch_CreateAction(state->objekt, 0x2d, x, y, 0);
			strcpy(o + 0x70, "anm_UpdateCat");
		}
	}
}

/* ADDRESS: GOLDTL 0x004bc6b0 */
void __cdecl fcn_004bc6b0(AMBIENT_ANIMAL_SLOT* state)
{
	int x;
	int g;
	int y;
	int z;
	float pts[8][4];
	float* pt;
	int n;
	char* o;

	if (*(int*) (state->objekt + 0x128) != 0)
		return;
	if (gm_RandomMod(0x64) > 0x14) {
		if (gm_RandomMod(0x64) > 0x32)
			ch_QueuePlayAnimation(state->objekt, "bewegung/stehen", gm_RandomMod(3) + 1);
		else
			ch_QueuePlayAnimation(state->objekt, "bewegung/fressen", gm_RandomMod(3) + 1);
		return;
	}
	g = *(int*) (((char*)g_67a370) + 0xb0);
	n = gm_RandomMod(3) + 1;
	n = ch_GenerateNearbyWalkablePoints((int*) state->pos, n, pts[0]);
	if (n <= 0)
		return;
	for (pt = pts[0]; n != 0; n--, pt += 4) {
		if (fcn_0045b990(g, pt, &x, &y, &z) != 0) {
			o = ch_CreateAction(state->objekt, 0x2d, x, y, 0);
			strcpy(o + 0x70, "anm_UpdateSheep");
		}
	}
}
