
extern int g_772514;
extern unsigned short g_774970;

unsigned short __cdecl gm_RandomMod(int);
int __cdecl fcn_004c4450(int);
void __cdecl fcn_00546190(char*);
int __cdecl fcn_004c5620(int, char*);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, void*);
void __cdecl fcn_00500bb0(char*, int, int, int);
int __cdecl fcn_004ac150(short);
unsigned short __cdecl fcn_004ac290(int);
char* __cdecl fcn_004ac1e0(short);
char* __cdecl fcn_00426cc0(int);
char* __cdecl fcn_00426fd0(char*);
void __cdecl fcn_00428340(char*, int, int);
void __cdecl fcn_00428720(char*);
void __cdecl fcn_004432d0(int, int);
int __cdecl sprintf(char*, const char*, ...);
void __cdecl fcn_004c5420(int, int, int, int, int);
void __cdecl fcn_005467e0(int);

#include "client_types.h"

extern pos14_7f4c00 g_7f4c00;

/* ADDRESS: GOLDTL 0x00555d30 */
void __cdecl fcn_00555d30(char* obj)
{
	char buf[0x200];
	char* p;
	char* e;
	char* q;
	char* x;
	int t;
	int id;
	int* base;
	int j;

	if (*(int*) (obj + 0x70) == -1 || *(int*) (obj + 0x70) == -2) {
		fcn_00546190(obj);
		return;
	}
	if (*(int*) (obj + 0x84) != -1 && fcn_004c4450(*(int*) (obj + 0x84)) == 0) {
		return;
	}
	*(int*) (obj + 0x84) = -1;
	switch (*(int*) (obj + 0x70)) {
	case 0:
		if (*(unsigned char*) (obj + 0x78) & 4) {
			return;
		}
		id = fcn_004ac150(*(short*) (obj + 0xac));
		*(short*) (obj + 0xac) = id;
		*(short*) (obj + 0xae) = fcn_004ac290(id);
		base = (int*) (obj + 0x52);
		*(pos14_7f4c00*) base = g_7f4c00;
		base[0] += gm_RandomMod(4) + 3;
		*(unsigned short*) (obj + 0x56) = 10;
		*(int*) (obj + 0x58) = 0;
		fcn_004c5620(1, obj);
		*(int*) (obj + 0x84) = -1;
		return;
	case 1:
		if (*(unsigned char*) (obj + 0x78) & 4) {
			return;
		}
		fcn_0051af00(buf, 0x1e29);
		for (j = 0x7f4ca2; j < 0x85a0a2; j += 0x21c) {
			if (*(unsigned short*) (j - 2) == 0xffff) {
				continue;
			}
			if (*(char*) j != 6 && *(char*) j != 7) {
				continue;
			}
			fcn_00545d40(*(int*) (j + 2), *(int*) (obj + 4), buf, 0,
				     0x601, (void*) 0x6b5c60);
		}
		fcn_00500bb0(obj + 0x52, 0, 5, 0);
		*(int*) (obj + 0x84) = fcn_004c5620(2, obj);
		return;
	case 2:
		base = (int*) (obj + 0x52);
		*(pos14_7f4c00*) base = g_7f4c00;
		fcn_00500bb0((char*) base, 0, 5, 0);
		e = fcn_00426cc0(*(int*) (obj + 0xb4));
		if (*(unsigned short*) (obj + 0x56) < 0x14) {
			if (e == 0 || *(int*) e != 0x68427244) {
				*(int*) (obj + 0xb4) = -1;
				x = fcn_004ac1e0(*(unsigned short*) (obj + 0xac));
				sprintf(buf, (char*) 0x67d444, *(int*) (x + 8));
				t = *(int*) 0x6b8010;
				fcn_004432d0(0, 1);
				q = fcn_00426fd0((char*) 0x6a5edc);
				if (q != 0) {
					*(int*) q = 0x68427244;
					*(int*) (obj + 0xb4) = *(int*) (q + 0x100);
					fcn_00428340(q, 1, *(int*) (x + 8));
					*(int*) (q + 0x104) = 0;
				}
				fcn_004432d0(t, 1);
			}
		} else {
			if (e != 0 && *(int*) e == 0x68427244) {
				fcn_00428720(e);
			}
			fcn_00500bb0((char*) base, 0, 5, 0);
			*(int*) (obj + 0x70) = 3;
			return;
		}
		*(int*) (obj + 0x70) = 2;
		if (*(int*) (obj + 0x88) != 0 &&
		    (*(int*) (g_774970 * 0x21c + 0x7f4e68) & 0x20000) != 0) {
			fcn_005467e0(*(int*) (obj + 0x88));
			*(int*) (obj + 0x88) = 0;
		}
		return;
	case 3:
		if (*(unsigned char*) (obj + 0x78) & 2) {
			for (j = 0x7f4e68; j < 0x85a268; j += 0x21c) {
				if (*(unsigned short*) (j - 0x1c8) == 0xffff) {
					continue;
				}
				if ((*(int*) j & 0x20000) == 0) {
					continue;
				}
				fcn_004c5420(*(int*) (j - 0x1c4), 0x1c8, 4, 0, 0x20000);
			}
		}
		*(pos14_7f4c00*) (obj + 0x52) = g_7f4c00;
		id = *(int*) (obj + 0x52) + 1;
		*(unsigned short*) (obj + 0x56) = 6;
		*(int*) (obj + 0x52) = id;
		*(int*) (obj + 0x58) = 0;
		if (*(int*) (obj + 0x88) != 0) {
			fcn_005467e0(*(int*) (obj + 0x88));
			*(int*) (obj + 0x88) = 0;
		}
		if (*(unsigned char*) (obj + 0x78) & 2) {
			*(int*) (obj + 0x84) = fcn_004c5620(0, obj);
		}
		*(int*) (obj + 0x84) = -1;
		return;
	}
}
