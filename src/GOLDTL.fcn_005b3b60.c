#include <string.h>

#pragma pack(push, 2)
typedef struct Time5b3b60 {
	int day;
	int hour;
	int min;
	unsigned short sec;
} Time5b3b60;
#pragma pack(pop)

typedef struct Ent5b3b60 {
	unsigned short id;
	unsigned char kind;
	char pad3;
	int key;
	char pad8[0x166 - 8];
	unsigned char active;
	char pad167[0x21c - 0x167];
} Ent5b3b60;

extern int g_7f4c00;
extern int g_7f4c04;
extern int g_7f4c08;
extern unsigned short g_7f4c0c;
extern unsigned short g_774970;
extern char* g_773da8;
extern char g_7f4ca0[];

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_00471e30(int);
int __cdecl fcn_00472250(int, int, int);
void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_004c5530(void*);
void __cdecl fcn_004c5980(void*);
void __cdecl fcn_004e5a00(void*);
void __cdecl fcn_00500bb0(void*, int, int, int);
int __cdecl fcn_00519190(char*);
int __cdecl fcn_005373e0(int, int);
char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
int __cdecl gm_RandomMod(int);

void __cdecl fcn_005b3b60(void)
{
	char msg[0xf8];
	char m[0x114];
	int types[3];
	int item[11];
	int i;
	int k;
	int p;
	char* r;

	memset(msg, 0, sizeof(msg));
	item[7] = fcn_00470820(0, 0, "misc\\theatre");
	fcn_00471b60(item[7]);
	fcn_004727a0(item[7], 0);
	item[2] = fcn_00472250(item[7], 0, fcn_00519190("%ia[Hochzeit]$N"));
	item[4] = fcn_00472250(item[7], 0, fcn_00519190("%ia[Tod]$N"));
	item[8] = fcn_00472250(item[7], 0, fcn_00519190("%ia[Pleite]$N"));
	item[9] = fcn_00472250(item[7], 0, fcn_00519190("%ia[Hinrichtung]$N"));
	item[6] = fcn_00472250(item[7], 0, fcn_00519190("%ia[Pacht]$N"));
	item[10] = fcn_00472250(item[7], 0, fcn_00519190("%ia[Geburt]$N"));
	item[0] = fcn_00472250(item[7], 0, fcn_00519190("%ia[Pest]$N"));
	item[1] = fcn_00472250(item[7], 0, fcn_00519190("%ia[Brand]$N"));
	item[3] = fcn_00472250(item[7], 0, fcn_00519190("%ia[Sturm]$N"));
	item[5] = fcn_00472250(item[7], 0, fcn_00519190("%ia[Duell]$N"));
	if (fcn_005373e0(0x5b3b60, 0x657c7)) {
		do {
		if (*(int*) 0x14ce8e0) {
			*(int*) 0x774654 = 1;
		}
		if (*(int*) 0x100f1dc != -1) {
			memset(m, 0, sizeof(m));
			k = *(int*) 0x67d370;
			if (k == item[9]) {
				*(char*) (m + 8) = 5;
				*(char*) (m + 0x26) = 0x20;
				*(int*) (m + 0x14) = -1;
				*(char*) (m + 0x30) = 2;
				*(int*) (m + 0x34) = *(int*) 0x7f5730;
				*(int*) (m + 0xc) = ((Ent5b3b60*) g_7f4ca0)[g_774970].key;
				*(int*) (m + 0x38) = ((Ent5b3b60*) g_7f4ca0)[g_774970].key;
				*(char*) (m + 0x7c) = (char) gm_RandomMod(5);
				i = 0;
				p = 0x7f4e06;
				while (p < 0x85a206) {
					if (*(char*) p == 0xd) {
						*(int*) (m + 0x3c) = ((Ent5b3b60*) g_7f4ca0)[i].key;
						break;
					}
					p += 0x21c;
					i++;
				}
				i = 0;
				p = 0x7f4e06;
				while (p < 0x85a206) {
					if (*(char*) p == 0xf) {
						*(int*) (m + 0x40) = ((Ent5b3b60*) g_7f4ca0)[i].key;
						break;
					}
					p += 0x21c;
					i++;
				}
				i = 0;
				p = 0x7f4e06;
				while (p < 0x85a206) {
					if (*(char*) p == 0xe) {
						*(int*) (m + 0x44) = ((Ent5b3b60*) g_7f4ca0)[i].key;
						break;
					}
					p += 0x21c;
					i++;
				}
				*(Time5b3b60*) &m[0x18] = *(Time5b3b60*) &g_7f4c00;
				fcn_00500bb0(m + 0x18, 0, 0x1e, 0);
				fcn_004c5980(m);
			} else if (k == item[2]) {
				r = gm_StartFilteredEntitySearch(1, 5, 7);
				*(char*) (m + 8) = 6;
				*(char*) (m + 0x26) = 0x20;
				*(int*) (m + 0x14) = *(int*) (r + 1);
				*(char*) (m + 0x30) = 2;
				*(int*) (m + 0xc) = ((Ent5b3b60*) g_7f4ca0)[g_774970].key;
				*(int*) (m + 0x34) = ((Ent5b3b60*) g_7f4ca0)[g_774970].key;
				*(int*) (m + 0x38) = *(int*) ((char*) g_7f4ca0 + g_774970 * 0x21c + 0x858);
				fcn_004e5a00(m);
			} else if (k == item[8]) {
				*(char*) (m + 8) = 9;
				*(char*) (m + 0x26) = 0x20;
				*(int*) (m + 0x14) = -1;
				*(char*) (m + 0x30) = 1;
				*(int*) (m + 0xc) = ((Ent5b3b60*) g_7f4ca0)[g_774970].key;
				*(int*) (m + 0x34) = ((Ent5b3b60*) g_7f4ca0)[g_774970].key;
				fcn_004e5a00(m);
			} else if (k == item[4]) {
				*(char*) (m + 8) = 8;
				*(char*) (m + 0x30) = 1;
				*(int*) (m + 0xc) = ((Ent5b3b60*) g_7f4ca0)[g_774970].key;
				*(int*) (m + 0x34) = ((Ent5b3b60*) g_7f4ca0)[g_774970].key;
				*(char*) (m + 0x26) = 0x20;
				*(int*) (m + 0x14) = -1;
				fcn_004e5a00(m);
				*(int*) 0x774954 = 0;
			} else if (k == item[10]) {
				memset(m, 0, sizeof(m));
				*(char*) (m + 8) = 7;
				*(char*) (m + 0x30) = 2;
				*(int*) (m + 0xc) = ((Ent5b3b60*) g_7f4ca0)[g_774970].key;
				*(int*) (m + 0x34) = ((Ent5b3b60*) g_7f4ca0)[g_774970].key;
				*(int*) (m + 0x38) = ((Ent5b3b60*) g_7f4ca0)[g_774970].key;
				*(Time5b3b60*) &m[0x18] = *(Time5b3b60*) &g_7f4c00;
				*(char*) (m + 0x26) = 0x20;
				*(int*) (m + 0x14) = -1;
				fcn_004e5a00(m);
				*(int*) 0x774954 = 0;
			} else if (k == item[6]) {
				types[0] = 0xb;
				types[1] = 0xd;
				types[2] = 0xc;
				i = 0;
				p = 0x7f4ca2;
				while (p < 0x85a0a2 && i < 8) {
					if (*(char*) p == 6 || *(char*) p == 7 || *(char*) p == 5 || *(char*) p == 4) {
						*(int*) (m + 0x34 + i * 4) = *(int*) (p + 2);
						i++;
					}
					p += 0x21c;
				}
				r = gm_StartFilteredEntitySearch(1, 5, types[gm_RandomMod(3) & 0xffff]);
				if (r != 0) {
					*(char*) (m + 8) = 0xa;
					*(char*) (m + 0x26) = 0x22;
					*(int*) (m + 0x14) = -1;
					*(char*) (m + 0x30) = (char) i;
					*(int*) (m + 0x80) = 0x3e80;
					*(int*) (m + 0xc) = ((Ent5b3b60*) g_7f4ca0)[g_774970].key;
					*(int*) (m + 0x7c) = *(int*) (r + 1);
					*(Time5b3b60*) &m[0x18] = *(Time5b3b60*) &g_7f4c00;
					fcn_00500bb0(m + 0x18, 0, 0x1e, 0);
					fcn_004c5980(m);
				}
				*(int*) 0x774954 = 0;
			} else if (k == item[0]) {
				*(char*) (msg + 4) = 0x59;
				*(int*) (msg + 8) = *(int*) (g_773da8 + 4);
				*(int*) (msg + 0xc) = -1;
				*(int*) (msg + 0x28) = g_7f4c00;
				*(int*) (msg + 0x2c) = g_7f4c04;
				*(int*) (msg + 0x30) = g_7f4c08;
				*(unsigned short*) (msg + 0x34) = g_7f4c0c;
				*(char*) (msg + 0x36) = 2;
				i = gm_RandomMod(3) & 0xffff;
				*(int*) (msg + 0x30) = g_7f4c08;
				*(int*) (msg + 0x58) = i * 3;
				*(int*) (msg + 0x2c) = g_7f4c04;
				*(int*) (msg + 0x2e) = 0;
				*(int*) (msg + 0x28) = g_7f4c00;
				*(unsigned short*) (msg + 0x34) = g_7f4c0c;
				if ((unsigned short) g_7f4c04 >= 0x17) {
					fcn_00500bb0(msg + 0x28, gm_RandomMod(4) + 7, gm_RandomMod(2) * 30, 0);
				} else {
					fcn_00500bb0(msg + 0x28, gm_RandomMod(4), gm_RandomMod(2) * 30, 0);
				}
				fcn_004c5530(msg);
			} else if (k == item[1]) {
				*(char*) (msg + 4) = 0x4e;
				*(int*) (msg + 8) = *(int*) (g_773da8 + 4);
				*(int*) (msg + 0xc) = -1;
				*(int*) (msg + 0x28) = g_7f4c00;
				*(int*) (msg + 0x2c) = g_7f4c04;
				*(int*) (msg + 0x30) = g_7f4c08;
				*(unsigned short*) (msg + 0x34) = g_7f4c0c;
				*(char*) (msg + 0x36) = 1;
				*(int*) (msg + 0x58) = -1;
				*(int*) (msg + 0x9c) = 0x7d0;
				*(int*) (msg + 0x2e) = 0;
				if ((unsigned short) g_7f4c04 >= 0x17) {
					fcn_00500bb0(msg + 0x28, gm_RandomMod(4) + 7, gm_RandomMod(2) * 30, 0);
				} else {
					fcn_00500bb0(msg + 0x28, gm_RandomMod(4), gm_RandomMod(2) * 30, 0);
				}
				fcn_004c5530(msg);
			} else if (k == item[3]) {
				*(char*) (msg + 4) = 0x50;
				*(int*) (msg + 8) = *(int*) (g_773da8 + 4);
				*(int*) (msg + 0xc) = -1;
				*(int*) (msg + 0x2c) = g_7f4c04;
				*(int*) (msg + 0x30) = g_7f4c08;
				*(char*) (msg + 0x36) = 2;
				*(int*) (msg + 0x58) = -1;
				*(int*) (msg + 0x9c) = 0x3e8;
				*(int*) (msg + 0x28) = g_7f4c00;
				*(unsigned short*) (msg + 0x34) = g_7f4c0c;
				if ((unsigned short) g_7f4c04 >= 0x17) {
					fcn_00500bb0(msg + 0x28, gm_RandomMod(4) + 7, gm_RandomMod(2) * 30, 0);
				} else {
					fcn_00500bb0(msg + 0x28, gm_RandomMod(4), gm_RandomMod(2) * 30, 0);
				}
				fcn_004c5530(msg);
			} else if (k == item[5]) {
				i = g_774970;
				memset(m, 0, sizeof(m));
				*(char*) (m + 8) = 4;
				*(char*) (m + 0x26) = 0x22;
				*(int*) (m + 0x14) = -1;
				*(char*) (m + 0x30) = 2;
				*(int*) (m + 0xc) = ((Ent5b3b60*) g_7f4ca0)[g_774970].key;
				*(int*) (m + 0x38) = ((Ent5b3b60*) g_7f4ca0)[g_774970].key;
				k = 1;
				p = 0x7f4ca0;
				while (p < 0x85a0a0) {
					if (k >= 2) {
						break;
					}
					if (*(unsigned short*) p != 0xffff && *(char*) (p + 0x166) != 0
					    && *(unsigned short*) p != (unsigned short) i) {
						*(int*) (m + 0x34 + k * 4) = *(int*) (p + 4);
						k++;
					}
					p += 0x21c;
				}
				*(Time5b3b60*) &m[0x18] = *(Time5b3b60*) &g_7f4c00;
				*(char*) (m + 0x7c) = 0;
				fcn_00500bb0(m + 0x18, 0, 0x1e, 0);
				fcn_004c5980(m);
				*(int*) 0x774654 = 2;
			}
		}
		} while (fcn_005373e0(0x5b3b60, 0x657c7));
	}
	fcn_00471e30(item[7]);
}
