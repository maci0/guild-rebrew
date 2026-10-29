#include <string.h>

extern int* g_104336c;
extern int* g_1005900;
extern char* g_1005904;
extern int g_1005908;
extern int g_100590c;
extern int g_1006110;
extern int g_1006914;
extern unsigned char g_1005910[];
extern unsigned char g_1006114[];
extern int g_1043698;
extern int g_773ddc;
extern int g_67a370;
extern int g_778d24;
extern char s_681664[];
extern char s_681658[];
extern char s_68149c[];

char* __cdecl fcn_0045b700(int* a1, int n, int a3);
void __cdecl gv_Free3Fields(char* p);
void __cdecl fcn_004bdd40(int a);
int __cdecl fcn_00597ff0(int a1, char* out);
void __cdecl fcn_00455540(char* object, float* position, float* result);
int __cdecl fcn_00455350(char* object, char* pos, float* result);
char __cdecl fcn_004379a0(char* scene, char* node, unsigned int flags, char (__cdecl* cb)(char*, char*), char* ctx);
char* __cdecl rd_GetBKSize(char* name);
void __cdecl fcn_004bdfb0(float* ox, float* oy, float* position, char* object, char** context);
int __cdecl fcn_004bdbe0(int obj, int x, int y, int i, int j);
char* __cdecl fcn_00445600(char* o, int flags, char* ptr, char* name);
char __cdecl fcn_0045b990(char* map, float* pos, int* x, int* y, int* z);
char __cdecl fcn_004bdeb0(char* e, char* obj);
void __cdecl fcn_0066080a(char* text);

/* ADDRESS: GOLDTL 0x004bd4e0 */
int __cdecl fcn_004bd4e0(int a0, int a1)
{
	char name[0x40];
	char ctx[0x54];
	char buf[0x40];
	char res[0x10];
	float pos[3];
	float ox1;
	float oy1;
	float ox2;
	float oy2;
	float dx;
	float dy;
	float adx;
	float ady;
	float rate;
	float step;
	int cellx;
	int celly;
	int count;
	int i;
	int j;
	int k;
	char* box;
	char* map;
	char* dst;
	char* p;
	char c;
	int n;

	g_1005900 = g_104336c;
	if (g_104336c == 0) {
		return 0;
	}
	g_1005904 = fcn_0045b700(g_104336c, *g_104336c, 2);
	if (g_1005904 == 0) {
		return 0;
	}
	g_100590c = -1;
	g_1005908 = -1;
	n = 0;
	k = 0;
	do {
		p = (char*) (g_1005900) + 0x7e24 + n;
		i = 0;
		do {
			c = *p;
			name[i] = c;
			p++;
			i++;
		} while (c);
		fcn_0066080a(name);
		if (strstr(name, s_681664) != 0) {
			g_1005908 = k;
		}
		if (strstr(name, s_681658) != 0) {
			g_100590c = k;
		}
		n += 0x40;
		k++;
	} while (n < 0x200);
	if (g_100590c == -1) {
		g_100590c = 1;
	}
	if (g_1005908 == -1) {
		g_1005908 = 2;
	}
	fcn_004bdd40((int) &g_1005900);
	i = fcn_00597ff0(a1, buf);
	if (i == 0) {
		gv_Free3Fields(g_1005904);
		return 0;
	}
	pos[0] = 0.0f;
	pos[1] = 0.0f;
	pos[2] = 0.0f;
	fcn_00455540((char*) a0, pos, (float*) res);
	*(int*) (ctx + 0x50) = 0;
	fcn_004379a0((char*) g_67a370, 0, 0x180, fcn_004bdeb0, ctx);
	if (*(int*) (ctx + 0x50) == 0) {
		gv_Free3Fields(g_1005904);
		return 0;
	}
	box = rd_GetBKSize(*(char**) (ctx + 0x50));
	if (box == 0) {
		gv_Free3Fields(g_1005904);
		return 0;
	}
	pos[0] = *(float*) (g_1005900 + 0x18) + *(float*) (box + 0x40);
	pos[1] = *(float*) (box + 0x44);
	pos[2] = *(float*) (g_1005900 + 0x1e) + *(float*) (box + 0x48);
	fcn_004bdfb0(&oy1, &ox1, pos, box, (char**) &g_1005900);
	pos[0] = *(float*) (box + 0x50) - *(float*) (g_1005900 + 0x18);
	pos[1] = *(float*) (box + 0x44);
	pos[2] = *(float*) (g_1005900 + 0x1e) + *(float*) (box + 0x48);
	fcn_004bdfb0(&oy2, &ox2, pos, box, (char**) &g_1005900);
	count = 0x200;
	dst = (char*) g_1006114;
	map = (char*) g_1005910;
	while (count) {
		*(int*) dst = *(int*) map;
		dst += 4;
		map += 4;
		count--;
	}
	g_1006110 = g_1006914;
	if (fcn_004bdbe0((int) &g_1005900, (int) ox2, (int) oy2, -1, -1) == 0) {
		gv_Free3Fields(g_1005904);
		return 0;
	}
	if (g_1006110 > g_1006914) {
		if (g_1006110 >= 5) {
			count = 0x200;
			dst = (char*) g_1006114;
			map = (char*) g_1005910;
			while (count) {
				*(int*) dst = *(int*) map;
				dst += 4;
				map += 4;
				count--;
			}
			g_1006110 = g_1006914;
		} else {
			goto copy_offset;
		}
	} else if (g_1006110 < 5) {
		goto copy_offset;
	}
	goto line;
copy_offset:
	count = 0x200;
	dst = (char*) g_1006114 + g_1006110 * 2;
	map = (char*) g_1005910;
	while (count) {
		*(int*) dst = *(int*) map;
		dst += 4;
		map += 4;
		count--;
	}
	g_1006110 += g_1006914;
line:
	dy = oy2 - oy1;
	dx = ox2 - ox1;
	adx = dx;
	if (adx < 0.0f) {
		adx = -adx;
	}
	ady = dy;
	if (ady < 0.0f) {
		ady = -ady;
	}
	if (adx <= ady) {
		rate = dx / ady;
		step = (rate != 0.0f) ? -1.0f : 1.0f;
		cellx = (int) oy1;
		celly = (int) oy2;
		if (cellx != celly) {
			while (1) {
				g_1006114[g_1006110 * 2] = (unsigned char) (int) oy1;
				g_1006114[g_1006110 * 2 + 1] = (unsigned char) (int) ox1;
				g_1006110++;
				map = *(char**) (g_1005904 + 0x24);
				*(int*) (map + ((int) ox1 * *g_1005900 + (int) oy1) * 0x1c) = 6;
				oy1 += step;
				ox1 += rate;
				cellx = (int) oy1;
				celly = (int) oy2;
				if (cellx == celly) {
					break;
				}
			}
		}
	} else {
		rate = dy / adx;
		step = (rate != 0.0f) ? -1.0f : 1.0f;
		cellx = (int) ox1;
		celly = (int) ox2;
		if (cellx != celly) {
			while (1) {
				g_1006114[g_1006110 * 2] = (unsigned char) (int) oy1;
				g_1006114[g_1006110 * 2 + 1] = (unsigned char) (int) ox1;
				g_1006110++;
				map = *(char**) (g_1005904 + 0x24);
				*(int*) (map + ((int) oy1 * *g_1005900 + (int) ox1) * 0x1c) = 6;
				ox1 += step;
				oy1 += rate;
				cellx = (int) ox1;
				celly = (int) ox2;
				if (cellx == celly) {
					break;
				}
			}
		}
	}
	dst = fcn_00445600((char*) a0, 0x100, 0, s_68149c);
	if (dst == 0) {
		dst = (char*) a0;
	}
	fcn_00455350(dst, dst + 0x4c, pos);
	i = 0;
	j = 0;
	if (fcn_0045b990(g_1005904, pos, &i, &j, 0) != 0) {
		if (fcn_004bdbe0((int) &g_1005900, i, j, -1, -1) != 0) {
			gv_Free3Fields(g_1005904);
			if (g_778d24 >= 0x780) {
					for (n = 0; n < g_1006110; n++) {
						map = *(char**) (g_1005900 + 5);
						*(map + (unsigned int) g_1006114[n * 2 + 1] * *g_1005900 + (unsigned int) g_1006114[n * 2]) = (unsigned char) g_1005908;
					}
					for (n = 0; n < g_1006914; n++) {
						map = *(char**) (g_1005900 + 5);
						*(map + (unsigned int) g_1005910[n * 2 + 1] * *g_1005900 + (unsigned int) g_1005910[n * 2]) = (unsigned char) g_1005908;
					}
				} else {
					for (n = 0; n < g_1006110; n++) {
						for (k = -1; k < 1; k++) {
							for (i = -1; i < 1; i++) {
								map = *(char**) (g_1005900 + 5);
								*(map + ((unsigned int) g_1006114[n * 2 + 1] + k) * *g_1005900 + (unsigned int) g_1006114[n * 2] + i) = (unsigned char) g_1005908;
							}
						}
					}
					for (n = 0; n < g_1006914; n++) {
						for (k = -1; k < 1; k++) {
							for (i = -1; i < 1; i++) {
								map = *(char**) (g_1005900 + 5);
								*(map + ((unsigned int) g_1005910[n * 2 + 1] + k) * *g_1005900 + (unsigned int) g_1005910[n * 2] + i) = (unsigned char) g_1005908;
							}
						}
					}
				}
			if ((g_1043698 & 2) == 0) {
				g_773ddc = 1;
			}
			return 1;
		}
	}
	gv_Free3Fields(g_1005904);
	return 0;
}
