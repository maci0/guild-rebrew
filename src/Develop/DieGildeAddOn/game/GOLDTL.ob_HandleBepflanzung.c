#include <string.h>

extern char* g_6b8300;
extern int g_1040494;
extern int g_6a25b8;
extern int g_772514;
extern char* g_1015ea0;
extern short g_14ce8c0;
extern short g_14ce8c2;
extern char* g_6b8014;
extern int g_14ce8cc;
extern int g_14ce8e0;
#include "client_dialog_state.h"
extern int g_67d370;
#include "game_player.h"
extern char g_773d75;
extern char g_14cf950;
extern double g_662908;

unsigned short* __cdecl fcn_00502cd0(int a, int b, int c, int d);
unsigned short* __cdecl gm_NextEntityQueryMatch(void);
int __cdecl fcn_00470820(int a, int b, char* name);
void __cdecl fcn_00471af0(int a, int b);
void __cdecl d2_SetForm(int a, int b);
int __cdecl fcn_0046f740(int a, int b, int c, int d);
void __cdecl fcn_00469470(int a, int b);
int __cdecl d2_CreateRadioGroup(int a, ...);
int __cdecl fcn_00441ab0(char* a, int b, int c, float d, float* out);
float* __stdcall fcn_005ebbb9(float* a, const float* b);
void __cdecl fcn_00438b40(int h, float* p);
int __cdecl plt_CheckZoneAvailability(int a, int b, int c, unsigned int d);
void __cdecl fcn_00414c90(int a, int b, int c, int d);
int __cdecl fcn_004c5aa0(int a, int b, int c, int d, int e, int f);
int __cdecl fcn_004c4450(int a);
int __cdecl fcn_005373e0(void* fn, int msg);
int __cdecl fcn_004c4480(int a);
float __cdecl eval_ObjektPreis2Credits(int, int);

void __cdecl fcn_004c5150(int a, int b, unsigned char c, int d);
int __cdecl init_SetPflanzenMap(int a, int b);
void __cdecl fcn_00412cf0(int a, float* p, int b, int c, int d);
void __cdecl d2_SelectRadioGroup(int a, int b);
int __cdecl plt_FindPlantInfo(int a);
void __cdecl d3_DestroyObject(int a);
int __cdecl fcn_0064d41a(char* buf, char* fmt, ...);
int __cdecl fcn_004488e0(char* a, int b, int c);
void __cdecl fcn_0043a5a0(int a, int p);
void __cdecl ReportClientMessage(char* a);
void __cdecl fcn_00469510(int a);
void __cdecl fcn_00471e30(int a);

/* ADDRESS: GOLDTL 0x005c5310 */
void __cdecl ob_HandleBepflanzung(int a0)
{
	int v1;

	int v6;
	int v16;
	int v17;
	unsigned int v18;
	unsigned int v19;
	unsigned int v20;
	unsigned int v21;
	unsigned int v22;
	int v23;
	int v24;
	int v25;
	unsigned short* v26;
	int v3;



	int v33;
	unsigned int v34;
	int v35;
	unsigned int v36;
	int v37;
	int v38;
	unsigned int v39;
	unsigned short* v4;
	unsigned int v40;

	unsigned int v7[9];
	int v8[8];
	float pick[3];
	float matrix[16];
	float world[3];
	float place[3];
	unsigned int color;












	char v14[256];
	char v15[256];


	v40 = *(unsigned int*) ((char*) a0 + 0x71);
	v33 = -1;
	v24 = -1;
	v17 = 0;
	v6 = 0;
	v16 = 0;
	pick[0] = 0.0f;
	pick[1] = 0.0f;
	pick[2] = 0.0f;
	v1 = 1;
	v34 = 0;
	v37 = 0;
	v36 = 0;
	v16 = 0;
	v23 = 0;
	v26 = 0;
	v25 = 0;
	if (!g_6b8300) {
		return;
	}
	v18 = 0;
	do {
		v3 = v17 + 0x7e24 + (int) g_6b8300;
		if (strstr((char*) v3, (char*) 0x67dd10)) {
			v36 = v18;
		}
		v17 += 0x40;
		v18 += 1;
	} while (v17 < 0x200);
	v17 = fcn_00502cd0(*(unsigned int*) ((char*) a0 + 0x5d), 1, 0, 0xff);
	if (!v17) {
		return;
	}
	v4 = fcn_00502cd0(*(unsigned int*) ((char*) v17 + 0x14), 1, 4, 0x17);
	if (v4) {
		do {
			v16 += 1;
			v7[v16] = *v4;
			v4 = gm_NextEntityQueryMatch();
		} while (v4);
		v25 = v16;
	}
	v17 = fcn_00470820(g_1040494 - 0x5f, 0x10a, (char*) 0x6ac720);
	if (v17 == -1) {
		return;
	}
	v38 = v17;
	if (g_6a25b8 != -1) {
		fcn_00471af0(g_6a25b8, 0);
	}
	d2_SetForm(v17, 1);
	v17 = 0;
	if (1 <= v16) {
		do {
			v16 = fcn_0046f740(0x1a, v17 * 0x32, v7[v17 + 1] + 0xdf,
				g_772514);
			v8[v17] = v16;
			if (v24 == -1) {
				v24 = d2_CreateRadioGroup(1, v16);
				*(unsigned int*) (v16 * 0x2f4 + 0x38 + g_1015ea0) = 1;
				*(unsigned int*) (v16 * 0x2f4 + 0x3c + g_1015ea0) = 1;
			} else {
				fcn_00469470(v24, v16);
			}
			v17 += 1;
		} while (v17 < v25);
		v16 = v25;
	}
	v35 = v24 * 0x23;
	for (;;) {
		v18 = fcn_00441ab0(g_6b8300, (int) g_14ce8c0,
			(int) g_14ce8c2, 30.0f, pick);
		if (v18 != 0xffffffff && v6) {
			v19 = v18 & 0xffff;
			v16 = (int) v18 >> 0x10;
			v34 = v19;
			v37 = v16;
			fcn_005ebbb9(matrix, (float*) (g_6b8014 + 0x18c));
			world[0] = matrix[8] * pick[2] + matrix[4] * pick[1] + matrix[0] * pick[0];
			world[1] = matrix[9] * pick[2] + matrix[5] * pick[1] + matrix[1] * pick[0];
			world[2] = matrix[10] * pick[2] + matrix[6] * pick[1] + matrix[2] * pick[0];
			world[0] += *(float*) (g_6b8014 + 0x4c);
			world[1] += *(float*) (g_6b8014 + 0x50);
			world[2] += *(float*) (g_6b8014 + 0x54);
			fcn_00438b40(v6, world);
			if (*(unsigned char*) (*(int*) g_6b8300 * v16
					+ *(int*) (g_6b8300 + 0x14) + v19) != v36
				|| (v16 = plt_CheckZoneAvailability(v40, v19, v16,
						(unsigned char) ((char*) v26)[0x42])) == 0) {
				v1 = 0;
				v16 = v25;
				v22 = 0x40;
				v21 = 0x40;
				v20 = 0xc0;
			}
			else {
				v22 = 0;
				v21 = 0;
				v1 = 1;
				v20 = 0;
				v16 = v25;
			}
		}
		else {
			if (!v1) {
				v22 = 0x40;
				v21 = 0x40;
				v20 = 0xc0;
			}
			else {
				v22 = 0;
				v21 = 0;
				v20 = 0;
			}
		}
		fcn_00414c90(v6, v20, v21, v22);
		v4 = v26;
		if (g_14ce8cc && v18 != 0xffffffff && v1) {
			v20 = fcn_004c5aa0(*(unsigned int*) ((char*) a0 + 1),
				v34, v37, *v26, 0, 0xffffffff);
			v17 = fcn_004c4450(v20);
			while (!v17) {
				fcn_005373e0(0, 0x677c7);
				v17 = fcn_004c4450(v20);
			}
			v17 = fcn_004c4480(v20);
			if (v17) {
				v39 = (int) eval_ObjektPreis2Credits(*v4, 100);
				v3 = (int) ((int) v39 * g_662908);
				if (v3 <= 0x400) {
					v3 = 0x400;
				}
				fcn_004c5150(0xffffffff,
					*(unsigned int*) (g_774970 * 0x21c
						+ 0x7f4ca4), g_773d75, v3);
				init_SetPflanzenMap(v17, 0);
				v17 = *(int*) ((char*) v17 + 0x14);
				if (v17) {
					place[0] = world[0];
					place[1] = world[1] - 60.0;
					place[2] = world[2];
					fcn_00438b40(v17, place);
					fcn_00412cf0(v17, world, v17 + 0x84, 0x32, 0x20);
				}
			}
		}
		if (g_14ce8e0) {
			g_774654 = 1;
		}
		if (g_14ce8cc) {
			v17 = 0;
			if (1 <= v16) {
				do {
					if (g_67d370 == v8[v17]) {
						v23 = *(int*) (v35 * 4 + 0x102cbc8);
						break;
					}
					v17 += 1;
				} while (v17 < v16);
			}
		}
		if (g_14cf950 != 'N') {
			if (g_14cf950 == 'J') {
				v23 -= 1;
				if (v23 <= -1) {
					v23 = v16 - 1;
				}
				d2_SelectRadioGroup(v24, v23);
			}
		}
		else {
			v23 += 1;
			if (v16 - 1 < v23) {
				v23 = 0;
			}
			d2_SelectRadioGroup(v24, v23);
		}
		v23 = *(int*) (v35 * 4 + 0x102cbc8);
		if (v23 != v33) {
			v4 = (unsigned short*) plt_FindPlantInfo(v7[v23 + 1]);
			v26 = v4;
			if (v6) {
				d3_DestroyObject(v6);
			}
			fcn_0064d41a(v14, (char*) 0x6ac704, (char*) 0x7e1ae0,
				&v4[1]);
			v6 = fcn_004488e0(v14, 0, 0);
			if (v6) {
				color = 0x100dc;
				*(unsigned char*) ((char*) v6 + 0x215) =
					*(unsigned char*) ((char*) v6 + 0x215) & 0x7f;
				fcn_0043a5a0(v6, (int) &color);
				*(unsigned char*) ((char*) v6 + 0x215) =
					*(unsigned char*) ((char*) v6 + 0x215) | 0x80;
			}
			else {
				fcn_0064d41a(v15, (char*) 0x6ac6c4, v14);
				ReportClientMessage(v15);
				g_774654 = 1;
			}
			v33 = v23;
		}
		if (!fcn_005373e0((void*) ob_HandleBepflanzung, 0x677cf)) {
			if (v6) {
				d3_DestroyObject(v6);
			}
			fcn_00469510(v24);
			if (g_6a25b8 != -1) {
				fcn_00471af0(g_6a25b8, 1);
			}
			fcn_00471e30(v38);
			return;
		}
	}
}
