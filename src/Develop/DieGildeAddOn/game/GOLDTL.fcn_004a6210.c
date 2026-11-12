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

int __cdecl fcn_004efd30(int);
int __cdecl fcn_004a6160(char*, void*, int, void*);
void __cdecl fcn_004f10d0(char*, int*, int*);
void __cdecl fcn_004f0f60(int, void*);
float __cdecl fcn_004f1290(char*);
int __cdecl fcn_005e8de0(float, float, float*);
void __cdecl fcn_005e8e50(float, float, char*, float*);
int __cdecl fcn_005ea4d0(void*, void*, void*, void*, void*, void*, void*, void*, void*);
int __cdecl _ftol(void);
float __cdecl fcn_004f0eb0(int, int, int);
int __cdecl fcn_004f0ff0(int, int, int, int, void*, void*);
int __cdecl fcn_0050b810(int, int);
int __cdecl gm_RandomMod(int);

extern float g_662cf8;
extern float g_6628bc;

/* ADDRESS: GOLDTL 0x004a6210 */
int __cdecl fcn_004a6210(char* a0, char* a1, int a2)
{
	int col;
	int row;
	union { float level; int cash; } value;
	float trajectory;
	int cost;
	int amount;
	float bounds[4];
	float range[2];
	float origin[3];
	float direction[3];
	float normal[3];
	float angle;
	float velocity[3];
	float other;
	float entry[5];
	float target[3];
	int profile[8];
	float spread;
	int state;

	int* p;


	g_772848 = -1;
	g_77284c = -1;
	p = (int*) fcn_004efd30(*(int*) (a1 + 1));
	if (p == 0) return 0;
	if (fcn_004a6160(a1, origin, a2, target) != 0) return 0;
	fcn_004f10d0(a1, &row, &col);
	col = gm_RandomMod(col + 1) & 0xffff;
	fcn_004f0f60(col, profile);
	if (*(int*) (a0 + 0x194) < profile[1]) return 0;
	value.level = fcn_004f1290(a1);
	row = gm_RandomMod(row + 1) & 0xffff;
	fcn_005e8de0(g_6660f4, *(float*) (col * 0xc + 0x665290), entry);
	fcn_005e8e50(*(float*) (col * 0xc + 0x665288),
		value.level * *(float*) (col * 0xc + 0x66528c), (char*) entry, range);
	bounds[0] = range[0];
	bounds[1] = range[1];
	bounds[2] = -0.2617994f;
	bounds[3] = 0.7853982f;
	if (fcn_005ea4d0(origin, target, bounds, &angle, &other, &trajectory,
		velocity, direction, normal) != 0) return 0;
	state = (int) ((trajectory - bounds[0]) * g_662cf8 / (bounds[1] - bounds[0]));
	spread = fcn_004f0eb0(col, state, row + 1);
	if (spread > *(float*) (p + 2 + row)) return 0;
	if (fcn_004f0ff0((int) a0, col, state, row + 1, &amount, &cost) == 0) return 0;
	value.cash = fcn_0050b810(*(int*) (a0 + 0x178), g_773d75);
	if ((int) (value.cash * g_6628bc) < cost) return 0;
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
	g_772848 = *(int*) (a0 + 4);
	g_7728b4 = cost;
	g_77284c = *(int*) (a1 + 1);
	g_7728b8 = amount;
	g_772898 = state;
	g_772894 = row + 1;
	g_772890 = *(int*) &trajectory;
	g_77289c = col;
	memcpy((void*) 0x7728a0, entry, sizeof(entry));

	return 1;
}
