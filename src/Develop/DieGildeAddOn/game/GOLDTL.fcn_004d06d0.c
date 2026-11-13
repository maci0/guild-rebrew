#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/d2.v1/d2_gui.h"
extern int g_67d370;
int __cdecl fcn_00443bf0(float, float, int, int); int __cdecl fcn_00442c00(int, int);
int __cdecl fcn_0045bad0(int, int, int, int*, int*);
char __cdecl fcn_0045b920(int, int, int, float*);
int __cdecl fcn_004cef70(int, int);
int* __cdecl fcn_004ce610(int);
int __cdecl fcn_0064f170(char*, char*, int);
int __cdecl strncmp(char*, char*, unsigned int);

/* ADDRESS: GOLDTL 0x004d06d0 */
void __cdecl fcn_004d06d0(void)
{
	float buf[3];
	char* obj;
	int* rec;
	int* meta;
	unsigned int v4;
	int i;
	int count;
	int x;
	int y;
	int kind;
	int same;
	unsigned short code;

	v4 = *(unsigned int*) (*(int*) &g_67a370 + 0xb0);
	count = 0;
	code = 0x23;
	i = 0;
	*(int*) &g_7746a4 = 0;
	g_7725c4 = 0;
	if (1 <= *(short*) &g_14ce8c0 && *(short*) &g_14ce8c0 < g_1040494
		&& 1 <= *(short*) &g_14ce8c2 && *(short*) &g_14ce8c2 < g_1040490
		&& g_67d370 == -1) {
		x = *(short*) &g_14ce8c0;
		y = *(short*) &g_14ce8c2;
		*(int*) &g_7746a4 = fcn_00443bf0((float) x, (float) y, 0x40, 1);
		if (*(int*) &g_7746a4 != 0 || *(int*) 0x772eb8 == 0) {



			if (*(int*) 0x772ea0 != 0) {
				fcn_00442c00(*(int*) 0x772ea0, 0);
			}
		}
		else if ((fcn_0045bad0(v4, x + 0x1a, y + 0x1a, &x, &y) & 0xff) != 0xffffffff) {
			fcn_0045b920(v4, x, y, buf);
			buf[1] = buf[1] + *(float*) 0x6640cc;
			g_7725c4 = 0;
		}
		if (*(int*) &g_7746a4 != 0) {
			for (rec = (int*) &g_7e4260; rec < (int*) 0x7e42dc; rec++) {
				i = *rec;
				if (i != 0 && *(char*) (i + 0x188) != 0) {
					if ((fcn_004cef70(*g_772f24, i) & 0x800) != 0
						&& g_14cf736 == 0) {
						kind = 0;
						meta = fcn_004ce610(i);
						if (meta != 0) {
							if (*meta == 0x160) code = 0x18;
							else if (*meta == 0x174) code = 0x19;
							else if (*meta == 0x16e) code = 0x1e;
							else if (*meta == 0x154) code = 0x1a;
							else if (*meta == 0x158) code = 0x1f;
							else if (*meta == 0x15e) code = 0x21;
							else if (*meta == 0x156) code = 0x23;
							else if (*meta == 0x176) code = 0x25;



						}
						count += 1;
					}
				}
			}
			if (2 <= count) {
				code = 0x23;
			}
			if (*(int*) &g_7746a4 == 0 || g_67d370 != -1) {
				g_7725c4 = 0;
				return;
			}
			obj = (char*) *(int*) &g_7746a4;
			if (strncmp(obj, (char*) 0x68b82c, 10) == 0 && count != 0) {
				g_7725c4 = 0x1c;
				*(int*) 0x772e90 = (int) *(int*) &g_7746a4;
				return;
			}
			if (fcn_0064f170((char*) *(int*) &g_7746a4, (char*) 0x68b820, 10) == 0 && count != 0) {
				g_7725c4 = 0x1b;
				*(int*) 0x772e90 = (int) *(int*) &g_7746a4;
				return;
			}
			if (fcn_0064f170((char*) *(int*) &g_7746a4, (char*) 0x68b818, 4) == 0 && count != 0) {
				g_7725c4 = 0xe;
				*(int*) 0x772e90 = (int) *(int*) &g_7746a4;
				return;
			}
			if (*(int*) (*(int*) &g_7746a4 + 0x220) == 2 && count != 0) {
				v4 = *(unsigned int*) (*(int*) &g_7746a4 + 0x204);
				if ((fcn_004cef70(*g_772f24, v4) & 0x800) == 0
					|| g_14cf736 != 0) {
					g_7725c4 = code;
					*(int*) 0x772e90 = (int) *(int*) &g_7746a4;
					return;
				}
			}
			else {
				g_7725c4 = 0;
			}
			*(int*) 0x772e90 = (int) *(int*) &g_7746a4;
			return;
		}
	}
	*(int*) 0x772e90 = 0;
	*(int*) &g_7746b4 = 0;
}
