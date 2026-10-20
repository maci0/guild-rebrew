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
float __cdecl fcn_004518a0(float* vector);
void __cdecl fcn_00412cf0(char* camera, float* position, char* view, int limit, int mode);
int __cdecl fcn_005373e0(int a, int b);
void __cdecl fcn_0058f700(int flag);
void __cdecl fcn_0052d820(void);

/* ADDRESS: GOLDTL 0x005a8c30 */
void __cdecl fcn_005a8c30(char* object)
{
	float offset[4];
	float target[4];
	float saved40;
	float saved44;
	float saved48;
	float saved50;
	float saved54;
	float saved58;
	char* camera;
	int previous;

	previous = g_7746a0;
	g_7746c4 = (int) object;
	g_6791c8 = *(int*) (object + 1);
	g_774658 = g_774650 + 1;
	saved40 = g_7e3a40;
	saved44 = g_7e3a44;
	saved48 = g_7e3a48;
	saved50 = g_7e3a50;
	saved54 = g_7e3a54;
	saved58 = g_7e3a58;
	fcn_00442c00((char*) g_7746a0, 0);
	offset[0] = *(float*) (g_7746a0 + 0x4c) - *(float*) (g_6b8014 + 0x4c);
	offset[1] = *(float*) (g_7746a0 + 0x50) - *(float*) (g_6b8014 + 0x50);
	offset[2] = *(float*) (g_7746a0 + 0x54) - *(float*) (g_6b8014 + 0x54);
	fcn_004518a0(offset);
	offset[0] = (float) (offset[0] * g_dbl_665fb8);
	offset[1] = (float) (offset[1] * g_dbl_665fb8);
	offset[2] = (float) (offset[2] * g_dbl_665fb8);
	target[0] = *(float*) (g_7746a0 + 0x4c) - offset[0];
	target[1] = *(float*) (g_7746a0 + 0x50) - offset[1];
	target[2] = *(float*) (g_7746a0 + 0x54) - offset[2];
	*(int*) (g_7746a0 + 0x94) = *(int*) (g_6b8014 + 0x88);
	fcn_00412cf0(g_6b8014, target, (char*) g_7746a0 + 0x90, g_6a256c, 8);
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
	g_7e3a40 = saved40;
	g_7e3a44 = saved44;
	g_7e3a48 = saved48;
	g_6791c8 = 0;
	g_7e3a50 = saved50;
	g_7e3a54 = saved54;
	g_7e3a58 = saved58;
	fcn_0052d820();
	fcn_00442c00((char*) previous, 1);
}
