#include <string.h>
#pragma intrinsic(memcpy)
extern int g_772848;
extern int g_77284c;
extern int g_772890;
extern int g_772894;
extern int g_772898;
extern int g_77289c;
extern int g_7728b4;
extern int g_7728b8;
extern float g_772850;
extern float g_772854;
extern float g_772858;
extern float g_772860;
extern float g_772864;
extern float g_772868;
extern float g_772870;
extern float g_772874;
extern float g_772878;
extern float g_772880;
extern float g_772884;
extern float g_772888;
extern float g_6660f4;
extern unsigned char g_773d75;

int __cdecl gm_LookupSlot170ByKey(int);
int __cdecl gm_GetCannonShotEndpoints(char*, void*, int, void*);
void __cdecl gm_GetArtilleryLimits(char*, int*, int*);
void __cdecl gm_ComputeCannonShotStats(int, void*);
float __cdecl gm_GetCannonPowerScale(char*);
int __cdecl d3_CalcParticleSphereMass(float, float, float*);
void __cdecl d3_CalcSpeedRangeFromMass(float, float, char*, float*);
int __cdecl gm_SolveBallisticTrajectory(void*, void*, void*, void*, void*, void*, void*, void*, void*);
int __cdecl _ftol(void);
float __cdecl gm_CalcArtilleryVolleyCost(int, int, int);
int __cdecl gm_CanFireCannonShot(int, int, int, int, void*, void*);
int __cdecl gm_SumQueryEntryValues(int, unsigned char);
int __cdecl gm_RandomMod(int);

extern float g_662cf8;
#include "Develop/DieGildeAddOn/game/game_data.h"

/* ADDRESS: GOLDTL 0x004a6210 */
int __cdecl gm_ComputeCannonShot(char* actor, char* building, int targetEnt)
{
	int col;
	int row;
	union { float level; int cash; } value;
	float trajectory;
	struct {
		int cost;
		int amount;
	} res;
	float bounds[4];
	float range[2];
	float origin[4];
	float direction[4];
	float normal[4];
	float angle;
	float velocity[4];
	float other;
	float entry[5];
	float target[4];
	int profile[8];
	float spread;
	int state;
	int off;

	int* p;


	g_772848 = -1;
	g_77284c = -1;
	p = (int*) gm_LookupSlot170ByKey(*(int*) (building + 1));
	if (p == 0) return 0;
	if (gm_GetCannonShotEndpoints(building, origin, targetEnt, target) != 0) return 0;
	gm_GetArtilleryLimits(building, &row, &col);
	col = gm_RandomMod(col + 1) & 0xffff;
	gm_ComputeCannonShotStats(col, profile);
	if (*(int*) (actor + 0x194) < profile[1]) return 0;
	value.level = gm_GetCannonPowerScale(building);
	row = gm_RandomMod(row + 1) & 0xffff;
	d3_CalcParticleSphereMass(g_6660f4, *(float*) (col * 0xc + 0x665290), entry);
	off = col * 0xc;
	d3_CalcSpeedRangeFromMass(*(float*) (off + 0x665288),
		value.level * *(float*) (off + 0x66528c), (char*) entry, range);
	bounds[0] = range[0];
	bounds[1] = range[1];
	bounds[2] = -0.2617994f;
	bounds[3] = 0.7853982f;
	if (gm_SolveBallisticTrajectory(origin, target, bounds, &angle, &other, &trajectory,
		velocity, direction, normal) != 0) return 0;
	state = (int) ((trajectory - bounds[0]) * 100.0f / (bounds[1] - bounds[0]));
	spread = gm_CalcArtilleryVolleyCost(col, state, row + 1);
	if (spread > *(float*) (p + 2 + row)) return 0;
	if (gm_CanFireCannonShot((int) actor, col, state, row + 1, &res.amount, &res.cost) == 0) return 0;
	value.cash = gm_SumQueryEntryValues(*(int*) (actor + 0x178), g_773d75);
	if ((int) (value.cash * 0.25f) < res.cost) return 0;
	g_772850 = origin[0];
	g_772854 = origin[1];
	g_772858 = origin[2];
	g_772860 = velocity[0];
	g_772864 = velocity[1];
	g_772868 = velocity[2];
	g_772880 = direction[0];
	g_772884 = direction[1];
	g_772888 = direction[2];
	g_772870 = normal[0];
	g_772874 = normal[1];
	g_772878 = normal[2];
	g_772848 = *(int*) (actor + 4);
	g_77284c = *(int*) (building + 1);
	g_7728b8 = res.amount;
	g_7728b4 = res.cost;
	g_772894 = row + 1;
	g_772890 = *(int*) &trajectory;
	g_772898 = state;
	g_77289c = col;
	memcpy((void*) 0x7728a0, entry, sizeof(entry));

	return 1;
}
