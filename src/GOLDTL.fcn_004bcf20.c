#include <stdio.h>
#include <string.h>

extern char s_681608[];
extern char s_68162c[];
extern char s_6815c0[];
extern char s_6815c8[];
extern char s_7e1ae0[];

extern void* __cdecl plt_FindPlantInfo(int);
extern void* __cdecl fcn_004488e0(char*, int, int);
extern void __cdecl fcn_0041d9e0(char*);
extern void __cdecl fcn_00438b40(void*, float*);

/* ADDRESS: GOLDTL 0x004bcf20 */

/* Loads the 3D object named by the plant info record, appends the caller's
 * object name and places it with the two axes of the placement cell. */
void __cdecl fcn_004bcf20(char* a0, int a1)
{
	char b1[256];
	char b2[256];
	float pos[4];
	char* info;
	char* obj;
	char* mat;
	int iv;
	int n;

	info = (char*) plt_FindPlantInfo(*(unsigned short*) (a0 + 0xa));
	if (a1 == 0) {
		n = *(signed char*) (a0 + 0xd) / (unsigned char) info[0x43];
		if (n < 1)
			n = 1;
		sprintf(b1, s_68162c, s_7e1ae0, info + 2, n);
	} else {
		n = *(signed char*) (a0 + 0xd) / (unsigned char) info[0x43];
		if (n < 1)
			n = 1;
		sprintf(b1, s_681608, s_7e1ae0, info + 2, n);
	}
	obj = (char*) fcn_004488e0(b1, 0, 0);
	if (obj == NULL) {
		sprintf(b2, s_6815c8, b1);
		fcn_0041d9e0(b2);
		return;
	}
	*(char**) (a0 + 0x14) = obj;
	sprintf(b2, s_6815c0, *(int*) a0);
	strcat(obj, b2);
	*(int*) (obj + 0x224) = 1;
	mat = (char*) *(int*) 0x6b8300;
	if (mat == NULL)
		return;
	pos[0] = *(float*) (mat + 0x50);
	pos[1] = *(float*) (mat + 0x54);
	pos[2] = *(float*) (mat + 0x58);
	iv = (unsigned char) a0[8];
	pos[0] += (float) iv * *(float*) (mat + 0x60);
	pos[1] += (float) iv * *(float*) (mat + 0x64);
	pos[2] += (float) iv * *(float*) (mat + 0x68);
	iv = (unsigned char) a0[9];
	pos[0] += (float) iv * *(float*) (mat + 0x70);
	pos[1] += (float) iv * *(float*) (mat + 0x74);
	pos[2] += (float) iv * *(float*) (mat + 0x78);
	pos[0] += (float) *(unsigned char*) (*(int*) mat * (unsigned char) a0[9] +
					     *(int*) (mat + 0x10) + (unsigned char) a0[8]) *
		  *(float*) (mat + 0x80);
	pos[1] += (float) *(unsigned char*) (*(int*) mat * (unsigned char) a0[9] +
					     *(int*) (mat + 0x10) + (unsigned char) a0[8]) *
		  *(float*) (mat + 0x84);
	pos[2] += (float) *(unsigned char*) (*(int*) mat * (unsigned char) a0[9] +
					     *(int*) (mat + 0x10) + (unsigned char) a0[8]) *
		  *(float*) (mat + 0x88);
	fcn_00438b40(obj, pos);
}
