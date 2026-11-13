#include <math.h>
#include <stdlib.h>

/* Water-flow sound marker ring. Samples world points around the camera,
 * projects them into the grid, and turns the covered water cells into the
 * flowing-water and splash voices of the per-slot target list. */

typedef struct Vec3_419990 {
	float x;
	float y;
	float z;
} Vec3_419990;

typedef struct Voice_419990 {
	char pad[0x34];
	char* handle;
} Voice_419990;

typedef struct Entry_419990 {
	int id;
	int volume;
	int pan;
} Entry_419990;

extern int* g_6b8300;
extern char* g_6b8014;
extern unsigned char g_772d10;
extern float* g_6b5d0c;
char* g_6b5d10 = 0;
char* g_6b5d14 = 0;
extern unsigned short g_6b5d18;
extern int g_67a370;
extern int g_6b5dcc;
extern int g_6b5d54;
extern int g_6b5da8;
extern int g_6b7fac;
extern int g_6b5dc8;
extern float g_6628a0;
extern float g_6628a8;
extern float g_662a80;
extern float g_662b60;
extern float g_6628c8;
extern float g_662d40[3];
extern float flt_677688;
extern float flt_677684[];
extern int int_67769c[];
extern char str_6776b8[];

float __cdecl fcn_00413d10(float* pos);
unsigned char __cdecl fcn_00441720(int* world, float* pos, unsigned int flag, unsigned int* grid_x, unsigned int* grid_y, float* radius);
int __cdecl fcn_00441f10(int* world, int x, int y);
float* __stdcall fcn_005ebbb9(float* matrix, const float* camera);
void __cdecl fcn_004518a0(float* v);
char* __cdecl fcn_00419640(int id, int* which);
char* __cdecl fcn_004234e0(char* bank, char* name, int loop, int pan, int vol, int a, int b);
void __cdecl fcn_004237f0(int* handle, int fade);
void __cdecl fcn_00423850(int* handle, int value);
int __cdecl fcn_00423890(int* handle, int value);
void __cdecl fcn_00426170(char* handle, int on);
void __cdecl fcn_004192b0(char* voice, int a2, int vol, int pan);
void* __cdecl fcn_004193d0(char* voice);

/* ADDRESS: GOLDTL 0x00419990 */
void __cdecl fcn_00419990(void)
{
	int i;
	int slot;
	int hint;
	int steps;
	int count;
	int id;
	int run;
	int cell;
	int volume;
	int pan;
	int state;
	unsigned int raw_x;
	unsigned int raw_y;
	unsigned int elapsed;
	float height;
	float radius;
	float angle;
	float center[3];
	float pos[3];
	float dir[3];
	float rotated[3];
	float matrix[4][4];
	double dx;
	double dy;
	double dz;
	double sine;
	double cosine;
	double sum;
	Entry_419990 entries[2];
	Voice_419990* voice;

	if (g_6b8300 == 0 || g_6b5d0c == 0 || g_6b8014 == 0 || g_772d10 == 0) {
		goto stop;
	}
	if (g_6b5dcc == 0) {
		g_6b5dcc = g_67a370;
	} else if (g_6b5dcc != g_67a370) {
		g_6b5dcc = g_67a370;
		goto stop;
	}
	center[0] = *(float*) (g_6b8014 + 0x4c);
	center[1] = *(float*) (g_6b8014 + 0x50);
	center[2] = *(float*) (g_6b8014 + 0x54);
	hint = (int) (*(float*) (g_6b8014 + 0x50) - fcn_00413d10((float*) (g_6b8014 + 0x4c)));
	if (hint > 2000) {
		hint = 2000;
	}
	if (!fcn_00441720(g_6b8300, center, 1, &raw_x, &raw_y, &height)) {
		return;
	}
	count = 0;
	radius = 39.37f;
	entries[0].id = entries[0].volume = entries[0].pan = 0;
	entries[1].id = entries[1].volume = entries[1].pan = 0;
	fcn_005ebbb9((float*) matrix, (float*) (g_6b8014 + 0x18c));
	dir[1] = 0.0f;
	dir[0] = g_662d40[0] * matrix[0][0] + (g_662d40[1] * matrix[1][0] + g_662d40[2] * matrix[2][0]);
	dir[2] = g_662d40[0] * matrix[0][2] + (g_662d40[1] * matrix[1][2] + g_662d40[2] * matrix[2][2]);
	fcn_004518a0(dir);
	run = fcn_00441f10(g_6b8300, raw_x, raw_y);
	if (run >= 0) {
		cell = *(int*) ((char*) g_6b8300 + 0x7da0);
		id = *(int*) ((char*) cell + run * 344 + 0x154);
	} else {
		id = 0;
	}
	if (run >= 0 && id <= 3 && id != 0) {
		entries[0].id = id;
		entries[0].volume = (int) (((double) (unsigned int) int_67769c[id] -
			(double) (unsigned int) int_67769c[id] * g_6628a8 / (flt_677684[id] * flt_677684[id])) *
			(2000 - hint) * g_662a80);
		entries[0].pan = 63;
		count = 1;
		for (i = 0; i < g_6b5d18; i++) {
			((int*) g_6b5d14)[i] = 3;
		}
	} else {
		for (i = 0; i < g_6b5d18; i++) {
			((int*) g_6b5d14)[i] = 1;
		}
	}
	for (steps = 1; (float) steps < flt_677688; steps++) {
		if (count >= 2) {
			break;
		}
		pos[0] = dir[0] * radius + center[0];
		pos[1] = dir[1] * radius + center[1];
		pos[2] = dir[2] * radius + center[2];
		for (slot = 0; slot < g_6b5d18; slot++) {
			if (((int*) g_6b5d14)[slot] != 0) {
				if (fcn_00441720(g_6b8300, pos, 0, &raw_x, &raw_y, &height)) {
					run = fcn_00441f10(g_6b8300, raw_x, raw_y);
					if (run >= 0) {
						cell = *(int*) ((char*) g_6b8300 + 0x7da0);
						((int*) g_6b5d10)[slot] = *(int*) ((char*) cell + run * 344 + 0x154);
					} else {
						((int*) g_6b5d10)[slot] = 0;
					}
					if (((int*) g_6b5d10)[slot] != 0) {
						state = ((int*) g_6b5d14)[slot];
						if (state == 1) {
							((int*) g_6b5d14)[slot] = 2;
						} else if (state == 2) {
							((int*) g_6b5d14)[slot] = 3;
						}
					} else {
						((int*) g_6b5d14)[slot] = 1;
					}
				} else {
					((int*) g_6b5d14)[slot] = 0;
				}
			}
			dx = (double) pos[0] - center[0];
			dy = (double) pos[1] - center[1];
			dz = (double) pos[2] - center[2];
			angle = g_6628c8 / (float) g_6b5d18;
			sine = sin(angle);
			cosine = cos(angle);
			rotated[0] = (float) (dx * cosine + dz * sine);
			rotated[2] = (float) (dz * cosine - dx * sine);
			pos[0] = rotated[0] + center[0];
			pos[1] = (float) (dy + center[1]);
			pos[2] = rotated[2] + center[2];
		}
		for (slot = 0; slot < g_6b5d18; slot++) {
			if (count >= 2) {
				break;
			}
			if (((int*) g_6b5d14)[slot] != 2 || !((float) steps <= flt_677684[((int*) g_6b5d10)[slot]])) {
				continue;
			}
			volume = 1;
			sum = g_6b5d0c[slot];
			for (i = 0; i < g_6b5d18; i++) {
				if (i != slot && ((int*) g_6b5d10)[i] == ((int*) g_6b5d10)[slot]) {
					((int*) g_6b5d10)[i] = 0;
					volume++;
					sum += g_6b5d0c[i];
				}
			}
			id = ((int*) g_6b5d10)[slot];
			if (id < 4) {
				entries[count].id = id;
				entries[count].volume = (int) (((double) (unsigned int) int_67769c[id] -
					(double) ((unsigned int) int_67769c[id] * steps * steps) / (flt_677684[id] * flt_677684[id])) *
					(2000 - hint) * g_662a80);
				entries[count].pan = (int) ((sum / volume + g_6628a0) * g_662b60);
				count++;
			} else {
				elapsed = (unsigned int) g_6b7fac * 13 - g_6b5dc8;
				if (elapsed > 60000 && elapsed < 120000) {
					pan = (int) ((sum / volume + g_6628a0) * g_662b60);
					volume = (int) (((double) (unsigned int) int_67769c[id] -
						(double) ((unsigned int) int_67769c[id] * steps * steps) / (flt_677684[id] * flt_677684[id])) *
						(2000 - hint) * g_662a80);
					fcn_004234e0(0, str_6776b8 + id * 25, 1, pan, volume, 0, 0);
					g_6b5dc8 = (unsigned int) g_6b7fac * 13;
				} else if (elapsed > 120000) {
					g_6b5dc8 = (unsigned int) g_6b7fac * 13;
				}
			}
		}
		radius = (float) (radius + *(double*) 0x662b58);
	}
	if (count == 2 && entries[0].id == entries[1].id && abs(entries[0].pan - entries[1].pan) < 31) {
		count = 1;
	}
	state = -1;
	if (count == 0) {
		if (g_6b5d54 != 0) {
			fcn_004237f0((int*) g_6b5d54, 0);
		}
		if (g_6b5da8 != 0) {
			fcn_004237f0((int*) g_6b5da8, 0);
		}
		return;
	}
	if (count == 1) {
		voice = (Voice_419990*) fcn_00419640(entries[0].id, &state);
		if (voice != 0) {
			if (voice->handle != 0) {
				fcn_00423890((int*) voice->handle, entries[0].volume);
				fcn_00423850((int*) voice->handle, entries[0].pan);
			}
			if (fcn_004193d0((char*) voice) == 0) {
				fcn_004192b0((char*) voice, 0, 0, 0);
			}
		}
		id = state == 0 ? g_6b5da8 : g_6b5d54;
		if (id != 0) {
			fcn_004237f0((int*) id, 0);
		}
	}
	state = -1;
	for (i = 0; i < count; i++) {
		voice = (Voice_419990*) fcn_00419640(entries[i].id, &state);
		if (voice != 0) {
			if (voice->handle != 0) {
				fcn_00423890((int*) voice->handle, entries[i].volume);
				fcn_00423850((int*) voice->handle, entries[i].pan);
			}
			if (fcn_004193d0((char*) voice) == 0) {
				fcn_004192b0((char*) voice, 0, 0, 0);
			}
		}
	}
	return;
stop:
	if (g_6b5d54 != 0) {
		fcn_004237f0((int*) g_6b5d54, 0);
		fcn_00426170((char*) g_6b5d54, 0);
		g_6b5d54 = 0;
	}
	if (g_6b5da8 != 0) {
		fcn_004237f0((int*) g_6b5da8, 0);
		fcn_00426170((char*) g_6b5da8, 0);
		g_6b5da8 = 0;
	}
}
