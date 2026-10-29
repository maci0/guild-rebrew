#include "Develop/Units/d3/d3_camera.h"

extern int g_7746a0;
extern int g_7746c4;
extern int g_774650;
extern int g_774658;
extern float g_7e3a40;
extern float g_7e3a44;
extern float g_7e3a48;
extern float g_7e3a50;
extern float g_7e3a54;
extern float g_7e3a58;
extern int g_6791c8;
extern int g_6a256c;
extern int g_6b5cbc;
extern double g_dbl_665fb8;

void __cdecl fcn_00442c00(char* object, int flag);
void __cdecl fcn_004518a0(float* vector);
void __cdecl fcn_00412cf0(char* camera, float* position, char* view, int limit, int mode);
int __cdecl fcn_005373e0(int a, int b);
void __cdecl fcn_0058f700(int flag);
void __cdecl fcn_0052d820(void);

struct CAMERA_SAVE {
	float offset[4];
	float target[4];
	float saveA[4];
	float saveB[3];
};

/* ADDRESS: GOLDTL 0x005a8c30 */
void __cdecl fcn_005a8c30(char* object)
{
	struct CAMERA_SAVE v;
	char* camera;
	int previous;

	g_7746c4 = (int) object;
	g_6791c8 = *(int*) (object + 1);
	g_774658 = g_774650 + 1;
	previous = g_7746a0;
	v.saveA[0] = g_7e3a40;
	v.saveA[1] = g_7e3a44;
	v.saveA[2] = g_7e3a48;
	v.saveB[0] = g_7e3a50;
	v.saveB[1] = g_7e3a54;
	v.saveB[2] = g_7e3a58;
	fcn_00442c00((char*) previous, 0);
	v.offset[0] = *(float*) (g_7746a0 + 0x4c) - *(float*) (g_6b8014 + 0x4c);
	v.offset[1] = *(float*) (g_7746a0 + 0x50) - *(float*) (g_6b8014 + 0x50);
	v.offset[2] = *(float*) (g_7746a0 + 0x54) - *(float*) (g_6b8014 + 0x54);
	fcn_004518a0(v.offset);
	v.offset[0] *= g_dbl_665fb8;
	v.offset[1] *= g_dbl_665fb8;
	v.offset[2] *= g_dbl_665fb8;
	v.target[0] = *(float*) (g_7746a0 + 0x4c) - v.offset[0];
	v.target[1] = *(float*) (g_7746a0 + 0x50) - v.offset[1];
	v.target[2] = *(float*) (g_7746a0 + 0x54) - v.offset[2];
	*(int*) (g_7746a0 + 0x94) = *(int*) (g_6b8014 + 0x88);
	fcn_00412cf0(g_6b8014, v.target, (char*) g_7746a0 + 0x90, g_6a256c, 8);
	do {
		if (!fcn_005373e0(0, 0x67fff)) {
			break;
		}
	} while (g_6b5cbc);
	camera = g_6b8014;
	g_7e3a40 = *(float*) (camera + 0x4c);
	g_7e3a44 = *(float*) (camera + 0x50);
	g_7e3a48 = *(float*) (camera + 0x54);
	g_7e3a50 = *(float*) (camera + 0x84);
	g_7e3a54 = *(float*) (camera + 0x88);
	g_7e3a58 = *(float*) (camera + 0x8c);
	fcn_0058f700(0);
	g_7e3a40 = v.saveA[0];
	g_7e3a44 = v.saveA[1];
	g_7e3a48 = v.saveA[2];
	g_6791c8 = 0;
	g_7e3a50 = v.saveB[0];
	g_7e3a54 = v.saveB[1];
	g_7e3a58 = v.saveB[2];
	fcn_0052d820();
	fcn_00442c00((char*) previous, 1);
}
