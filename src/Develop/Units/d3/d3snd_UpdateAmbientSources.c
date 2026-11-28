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

typedef struct Slot_419990 {
	int id;
	char pad[0x50];
} Slot_419990;

extern int* d3_CurrentFloor;
extern char* d3_ActiveCamera;
extern unsigned char d3snd_AmbientEnabled;
extern float* d3snd_ProbeSinTable;
char* d3sndw_SlotWaterIds = 0;
char* d3sndw_SlotStates = 0;
extern unsigned short g_6b5d18;
extern int d3_ActiveScene;
extern int g_6b5dcc;
extern int g_6b5d54;
extern int g_6b5da8;
extern volatile int gm_GameTicks;
extern int g_6b5dc8;
extern float flt_1_0;
extern float flt_0_0;
extern float g_662a80;
extern float g_662b60;
extern float d3_TwoPi;
extern float d3_UnitAxisVectors[3];
extern float flt_677688;
extern float flt_677684[];
extern int int_67769c[];
extern char str_6776b8[];

float __cdecl d3_SampleAverageTerrainHeight(float* pos);
unsigned char __cdecl d3_GetFloorHeight(int* world, float* pos, unsigned int flag, unsigned int* grid_x, unsigned int* grid_y, float* radius);
int __cdecl d3_GetFloorWaterType(int* world, int x, int y);
float* __stdcall D3DXMatrixTranspose(float* matrix, const float* camera);
void __cdecl d3_NormalizeVector(float* v);
char* __cdecl d3snd_AcquireAmbientVoice(int id, int* which);
char* __cdecl sb_PlayVoice(char* bank, char* name, int loop, int pan, int vol, int a, int b);
void __cdecl sb_StopVoice(int* handle, int fade);
void __cdecl sb_SetVoicePan(int* handle, int value);
int __cdecl sb_SetVoiceVolume(int* handle, int value);
void __cdecl d3snd_SetVoiceFlag0x10(char* handle, int on);
void __cdecl d3snd_PlaySource(char* voice, int a2, int vol, int pan);
void* __cdecl d3snd_GetObjectVoiceStatus(char* voice);

/* ADDRESS: GOLDTL 0x00419990 */
void __cdecl d3snd_UpdateAmbientSources(void)
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

	if (d3_CurrentFloor == 0 || d3snd_ProbeSinTable == 0 || d3_ActiveCamera == 0 || d3snd_AmbientEnabled == 0) {
		goto stop;
	}
	if (g_6b5dcc == 0) {
		g_6b5dcc = d3_ActiveScene;
	} else if (d3_ActiveScene != g_6b5dcc) {
		g_6b5dcc = d3_ActiveScene;
		goto stop;
	}
	center[0] = *(float*) (d3_ActiveCamera + 0x4c);
	center[1] = *(float*) (d3_ActiveCamera + 0x50);
	center[2] = *(float*) (d3_ActiveCamera + 0x54);
	hint = (int) (*(float*) (d3_ActiveCamera + 0x50) - d3_SampleAverageTerrainHeight((float*) (d3_ActiveCamera + 0x4c)));
	if (hint > 2000) {
		hint = 2000;
	}
	if (!d3_GetFloorHeight(d3_CurrentFloor, center, 1, &raw_x, &raw_y, &height)) {
		return;
	}
	count = 0;
	radius = 39.37f;
	entries[0].id = entries[0].volume = entries[0].pan = 0;
	entries[1].id = entries[1].volume = entries[1].pan = 0;
	D3DXMatrixTranspose((float*) matrix, (float*) (d3_ActiveCamera + 0x18c));
	dir[1] = 0.0f;
	dir[0] = d3_UnitAxisVectors[0] * matrix[0][0] + (d3_UnitAxisVectors[1] * matrix[1][0] + d3_UnitAxisVectors[2] * matrix[2][0]);
	dir[2] = d3_UnitAxisVectors[0] * matrix[0][2] + (d3_UnitAxisVectors[1] * matrix[1][2] + d3_UnitAxisVectors[2] * matrix[2][2]);
	d3_NormalizeVector(dir);
	run = d3_GetFloorWaterType(d3_CurrentFloor, raw_x, raw_y);
	if (run < 0) {
		goto fill_one;
	}
	cell = *(int*) ((char*) d3_CurrentFloor + 0x7da0);
	id = *(int*) ((char*) cell + run * 344 + 0x154);
	if (id <= 3 && id != 0) {
		entries[0].id = id;
		entries[0].volume = (int) (((double) (unsigned int) int_67769c[id] -
			(double) (unsigned int) int_67769c[id] * 0.0f / (flt_677684[id] * flt_677684[id])) *
			(2000 - hint) * g_662a80);
		entries[0].pan = 63;
		count = 1;
		for (i = 0; i < g_6b5d18; i++) {
			((int*) d3sndw_SlotStates)[i] = 3;
		}
	} else {
fill_one:
		for (i = 0; i < g_6b5d18; i++) {
			((int*) d3sndw_SlotStates)[i] = 1;
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
			if (((int*) d3sndw_SlotStates)[slot] != 0) {
				if (d3_GetFloorHeight(d3_CurrentFloor, pos, 0, &raw_x, &raw_y, &height)) {
					run = d3_GetFloorWaterType(d3_CurrentFloor, raw_x, raw_y);
					if (run >= 0) {
						cell = *(int*) ((char*) d3_CurrentFloor + 0x7da0);
						((int*) d3sndw_SlotWaterIds)[slot] = *(int*) ((char*) cell + run * 344 + 0x154);
					} else {
						((int*) d3sndw_SlotWaterIds)[slot] = 0;
					}
					if (((int*) d3sndw_SlotWaterIds)[slot] != 0) {
						state = ((int*) d3sndw_SlotStates)[slot];
						if (state == 1) {
							((int*) d3sndw_SlotStates)[slot] = 2;
						} else if (state == 2) {
							((int*) d3sndw_SlotStates)[slot] = 3;
						}
					} else {
						((int*) d3sndw_SlotStates)[slot] = 1;
					}
				} else {
					((int*) d3sndw_SlotStates)[slot] = 0;
				}
			}
			dx = (double) pos[0] - center[0];
			dy = (double) pos[1] - center[1];
			dz = (double) pos[2] - center[2];
			angle = d3_TwoPi / (float) g_6b5d18;
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
			if (((int*) d3sndw_SlotStates)[slot] != 2 || !((float) steps <= flt_677684[((int*) d3sndw_SlotWaterIds)[slot]])) {
				continue;
			}
			volume = 1;
			sum = d3snd_ProbeSinTable[slot];
			for (i = 0; i < g_6b5d18; i++) {
				if (i != slot && ((int*) d3sndw_SlotWaterIds)[i] == ((int*) d3sndw_SlotWaterIds)[slot]) {
					((int*) d3sndw_SlotWaterIds)[i] = 0;
					volume++;
					sum += d3snd_ProbeSinTable[i];
				}
			}
			id = ((int*) d3sndw_SlotWaterIds)[slot];
			if (id < 4) {
				entries[count].id = id;
				entries[count].volume = (int) (((double) (unsigned int) int_67769c[id] -
					(double) ((unsigned int) int_67769c[id] * steps * steps) / (flt_677684[id] * flt_677684[id])) *
					(2000 - hint) * g_662a80);
				entries[count].pan = (int) ((sum / volume + flt_1_0) * g_662b60);
				count++;
			} else {
				elapsed = (unsigned int) gm_GameTicks * 13 - g_6b5dc8;
				if (elapsed > 60000 && elapsed < 120000) {
					pan = (int) ((sum / volume + flt_1_0) * g_662b60);
					volume = (int) (((double) (unsigned int) int_67769c[id] -
						(double) ((unsigned int) int_67769c[id] * steps * steps) / (flt_677684[id] * flt_677684[id])) *
						(2000 - hint) * g_662a80);
					sb_PlayVoice(0, str_6776b8 + id * 25, 1, pan, volume, 0, 0);
					g_6b5dc8 = (unsigned int) gm_GameTicks * 13;
				} else if (elapsed > 120000) {
					g_6b5dc8 = (unsigned int) gm_GameTicks * 13;
				}
			}
		}
		radius = (float) (radius + 39.37);
	}
	if (count == 2 && entries[0].id == entries[1].id && abs(entries[0].pan - entries[1].pan) < 31) {
		count = 1;
	}
	state = -1;
	switch (count) {
	case 0:
		if (g_6b5d54 != 0) {
			sb_StopVoice((int*) g_6b5d54, 0);
		}
		if (g_6b5da8 != 0) {
			sb_StopVoice((int*) g_6b5da8, 0);
		}
		return;
	case 1:
		voice = (Voice_419990*) d3snd_AcquireAmbientVoice(entries[0].id, &state);
		if (voice != 0) {
			if (voice->handle != 0) {
				sb_SetVoiceVolume((int*) voice->handle, entries[0].volume);
				sb_SetVoicePan((int*) voice->handle, entries[0].pan);
			}
			if (d3snd_GetObjectVoiceStatus((char*) voice) == 0) {
				d3snd_PlaySource((char*) voice, 0, 0, 0);
			}
		}
		id = ((Slot_419990*) &g_6b5d54)[state == 0].id;
		if (id != 0) {
			sb_StopVoice((int*) id, 0);
		}
	case 2:
		state = -1;
		for (i = 0; i < count; i++) {
			voice = (Voice_419990*) d3snd_AcquireAmbientVoice(entries[i].id, &state);
			if (voice != 0) {
				if (voice->handle != 0) {
					sb_SetVoiceVolume((int*) voice->handle, entries[i].volume);
					sb_SetVoicePan((int*) voice->handle, entries[i].pan);
				}
				if (d3snd_GetObjectVoiceStatus((char*) voice) == 0) {
					d3snd_PlaySource((char*) voice, 0, 0, 0);
				}
			}
		}
		break;
	}
	return;
stop:
	if (g_6b5d54 != 0) {
		sb_StopVoice((int*) g_6b5d54, 0);
		d3snd_SetVoiceFlag0x10((char*) g_6b5d54, 0);
		g_6b5d54 = 0;
	}
	if (g_6b5da8 != 0) {
		sb_StopVoice((int*) g_6b5da8, 0);
		d3snd_SetVoiceFlag0x10((char*) g_6b5da8, 0);
		g_6b5da8 = 0;
	}
}
