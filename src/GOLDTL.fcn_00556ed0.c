#include "client_types.h"

#pragma pack(push, 1)
typedef struct {
	int day;
	unsigned short hour;
	int minute;
	unsigned short x;
} Clock;
/* SIZE 0xe */
#pragma pack(pop)

/* SIZE 0x21c */
typedef struct {
	unsigned short id;
	unsigned char type;
	char pad3;
	int handle;
	char pad8[0x164];
	char* home2;
	char* home;
	char pad174[0xa8];
} Player;

extern pos14_7f4c00 g_7f4c00;
extern Player g_7f4ca0[];
extern unsigned char* g_868050;
extern char g_6b5c60[];

unsigned short __cdecl gm_RandomMod(int);
float __cdecl gm_RandomFloat01(void);
void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);
int __cdecl fcn_0050c710(char*, int, int);
int __cdecl fcn_00508280(char*, int*, float*);
float __cdecl fcn_004fef80(char*);
int __cdecl fcn_005c6270(char*, int);
int __cdecl fcn_00556e80(unsigned short*);
void __cdecl fcn_005498b0(char*, char*, char*, char*, int, float);
void __cdecl fcn_0051af00(char*, char*, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, char*);
void __cdecl fcn_00546190(char*);

/* One step of the disease simulation: walks twelve towns in a pseudo-random
 * order and rolls an illness for each one. */
/* ADDRESS: GOLDTL 0x00556ed0 */
void __cdecl fcn_00556ed0(char* s)
{
	float x;
	float y;
	int idx;
	int r;
	float g;
	float m;
	int count;
	float f;
	int steps[16];
	char buf[0x200];
	Player* p;
	char* home;
	char* home2;
	unsigned char* q;

	if (*(int*) (s + 0x70) == -2) {
		fcn_00546190(s);
		return;
	}
	fcn_0051af00(buf, "-------> RunSimKrankheiten: calculating at <Day = %i Time = %i.2:%i.2>",
	    ((Clock*) &g_7f4c00)->day, ((Clock*) &g_7f4c00)->hour, ((Clock*) &g_7f4c00)->minute);
	if (*(int*) (s + 0xb0) == 0) {
		steps[0] = 1;
		steps[1] = 3;
		steps[2] = 5;
		steps[3] = 7;
		steps[4] = 11;
		steps[5] = 13;
		steps[6] = 17;
		steps[7] = 19;
		steps[8] = 0x2ed;
		steps[9] = 0x2ef;
		steps[10] = 0x2f3;
		steps[11] = 0x2f5;
		steps[12] = 0x2f9;
		steps[13] = 0x2fb;
		steps[14] = 0x2fd;
		steps[15] = 0x2ff;
		*(int*) (s + 0xb0) = steps[gm_RandomMod(16)];
		*(int*) (s + 0xac) = gm_RandomMod(0x300);
	}
	if (*(int*) (s + 0x70) != 0) {
		return;
	}
	idx = *(int*) (s + 0xac);
	count = 12;
	do {
		p = &g_7f4ca0[idx];
		if (fcn_00556e80((unsigned short*) p) != 0) {
			f = gm_RandomFloat01() * 100.0f;
			home = p->home;
			x = 0.0f;
			y = 0.0f;
			if (home != 0) {
				if (*(unsigned char*) (g_868050 + *(unsigned char*) home * 0x24d) == 2) {
					x = (float) fcn_0050c710(home, 8, 1) * 0.0125f * 20.0f;
				} else {
					x = (float) fcn_0050c710(home, 8, 1) * 0.02f * 20.0f;
				}
			} else {
				y = 25.0 - gm_RandomFloat01() * 20.0f * 0.5;
			}
			m = fcn_005c6270((char*) p, 0x2b3) != 0 ? y * 0.75f : y;
			if (f < m - x) {
				if (fcn_00508280((char*) p, &r, &g) != 0) {
					home2 = p->home2;
					if (home2 != 0 && *(unsigned short*) (home2 + 0x27) != 0xffff
					    && (q = (unsigned char*) &g_7f4ca0[*(unsigned short*) (home2 + 0x27)]) != 0) {
						fcn_005498b0(s, (char*) p, (char*) q, home2, r, g);
					} else {
						if (g < fcn_004fef80((char*) p)
						    && (p->type == 6 || p->type == 7)) {
							fcn_0051af00(buf, (char*) 0x163c, (char*) (r + 0x1632));
							fcn_00545d40(p->handle, -1, buf, 0, 0x5f7, g_6b5c60);
						}
					}
				}
			}
		}
		idx = (*(int*) (s + 0xb0) + idx) % 0x300;
		*(int*) (s + 0xb4) = *(int*) (s + 0xb4) + 1;
	} while (--count != 0);
	*(int*) (s + 0xac) = idx;
	if (*(int*) (s + 0xb4) >= 0x300) {
		*(unsigned short*) (s + 0x56) = 10;
		*(int*) (s + 0xac) = 0;
		*(int*) (s + 0xb0) = 0;
		*(int*) (s + 0xb4) = 0;
		*(int*) (s + 0x52) = *(int*) (s + 0x52) + 1;
		return;
	}
	fcn_00500bb0((pos14_7f4c00*) (s + 0x52), 0, 0x1e, 0);
	if (*(unsigned short*) (s + 0x56) >= 0x12) {
		*(int*) (s + 0x58) = 0;
		*(unsigned short*) (s + 0x56) = 10;
		*(int*) (s + 0x52) = *(int*) (s + 0x52) + 1;
	}
}
