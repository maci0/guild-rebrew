#pragma pack(2)
typedef struct {
	int day;
	unsigned short hour;
	int minute;
	int second;
} Stamp;
#pragma pack()

typedef struct {
	float v[24];
} Vec24;

/* SIZE 0x4 */
typedef struct {
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
} Col;

/* SIZE 0x2f4 */
typedef struct {
	char pad0[0x108];
	int f108[4];
	int f118[4];
	char pad128[0x2f4 - 0x128];
} SkyFrame;

/* SIZE 0x3dc */
typedef struct {
	char pad0[0x2c];
	int f2c;
	char pad30[0x3dc - 0x30];
} Slot_52a3a0;

#include "client_types.h"

extern unsigned char g_773d75;
extern char g_868060[];
extern pos14_7f4c00 g_7f4c00;
extern int g_7e43a0;
extern int g_7e43a4;
extern int g_7e4530;
extern int g_7e4534;
extern int g_7e4538;
extern int g_7e453c;
extern int g_7e4540[6];
extern int g_7e4468;
extern int g_7e446c;
extern int g_7e4380;
extern int g_6b89c0;
extern int g_6b8010;
extern char g_7746fc;
extern Slot_1043340 g_1043340[64];
extern Tabs_7e43a8 g_7e43a8;
extern float g_6a2640;
extern float g_6a2644;
extern float g_6a2648;
extern float g_6a268c;
extern float g_6a2690;
extern float g_6a2694;
extern float g_6a28f0;
extern float g_6a28f4;
extern float g_6a28f8;

void __cdecl fcn_00500d60(int*, char*);
int __cdecl fcn_0052a310(int*);
unsigned short __cdecl gm_RandomMod(int);
int __cdecl rand(void);
float __cdecl gm_RandomFloat01(void);
double __cdecl sin(double);
double __cdecl cos(double);
#pragma intrinsic(sin, cos)

int* __cdecl fcn_00459ae0(float, float, float);
int __cdecl fcn_00459870(int, int, int, Col, float, int, float, float);
void __cdecl fcn_00459940(int, int, float);
void __cdecl fcn_004597f0(int, int);
void __cdecl fcn_005e8870(int, int, Vec24*, Vec24*);
void __cdecl fcn_004432d0(int, int);
void __cdecl fcn_0052a7d0(void);
void __cdecl fcn_0052a960(Stamp*);
int* __cdecl fcn_00415310(int);
void __cdecl fcn_004154e0(int);
int* __cdecl fcn_00416060(int);
void __cdecl fcn_004162c0(int);
void __cdecl fcn_00416300(int*, int, ...);
void __cdecl fcn_00415510(int*, int, ...);

/* ADDRESS: GOLDTL 0x0052a3a0 */
void __cdecl fcn_0052a3a0(Stamp* now, int flag)
{
	char buf[12];
	float step;
	float angle;
	int mode;
	int i;
	int maxv;
	int player;
	Col col;

	fcn_00500d60((int*) now, buf);
	mode = fcn_0052a310((int*) now);
	g_7e43a0 = ((int*) ((char*) g_868060 + 0x108))[g_773d75 * 189 + mode];
	g_7e43a4 = ((int*) ((char*) g_868060 + 0x118))[g_773d75 * 189 + mode];
	if (flag != 0) {
		if (mode == 3) {
			g_7e4530 = (gm_RandomMod(100) < g_7e43a0 / 2) + 1;
		} else {
			g_7e4530 = 0;
		}
		for (i = 0; i < 24; i++) {
			g_7e43a8.a[i] = 0;
		}
		for (i = 0; i < 24; i++) {
			if (gm_RandomMod(100) < g_7e43a0) {
				g_7e43a8.a[i] = gm_RandomMod(g_7e43a0 * 10);
			}
			if (g_7e43a8.a[i] > 700) {
				g_7e43a8.a[i] = (g_7e43a8.a[i] & 1) + 999;
			} else if (g_7e43a8.a[i] > 500) {
				g_7e43a8.a[i] = (g_7e43a8.a[i] & 1) + 499;
			} else if (g_7e43a8.a[i] > 250) {
				g_7e43a8.a[i] = (g_7e43a8.a[i] & 1) + 149;
			} else {
				g_7e43a8.a[i] = 0;
			}
			if (g_7e4530 == 0 && g_7e43a8.a[i] >= 999) {
				g_7e43a8.b[i] = gm_RandomMod(3);
			} else {
				g_7e43a8.b[i] = 0;
			}
		}
		angle = gm_RandomFloat01() * 6.2831853;
		step = rand() > 0x3fff ? -0.175f : 0.175f;
		for (i = 0; i < 24; i++) {
			((Vec24*) &g_7e43a8.c)->v[i] = sin(angle);
			((Vec24*) &g_7e43a8.d)->v[i] = cos(angle);
			angle += gm_RandomFloat01() * step;
		}
	}
	fcn_005e8870(mode, g_7f4c00.a, (Vec24*) &g_7e43a8.c, (Vec24*) &g_7e43a8.d);
	g_7e4468 = 0;
	g_7e446c = 0;
	g_7e4534 = -1;
	maxv = 0;
	for (i = 0; i < 24; i++) {
		if (maxv <= g_7e43a8.a[i]) {
			maxv = g_7e43a8.a[i];
		}
	}
	if (g_7e4530 != 0) {
		if (g_7e4530 == 1) {
			if (g_7e4538 != 0) {
				fcn_004154e0(g_7e4538);
				g_7e4538 = 0;
			}
		} else if (g_7e4538 == 0) {
			g_7e4538 = (int) fcn_00415310(maxv);
		}
		if (g_7e453c == 0) {
			g_7e453c = (int) fcn_00416060(maxv);
		}
		fcn_00416300((int*) g_7e453c, 2, 0, 0, 3, 0xff);
		fcn_00416300((int*) g_7e453c, 1, 0, 0);
	} else {
		if (g_7e453c != 0) {
			fcn_004162c0(g_7e453c);
			g_7e453c = 0;
		}
		if (g_7e4538 == 0) {
			g_7e4538 = (int) fcn_00415310(maxv);
		}
		fcn_00415510((int*) g_7e4538, 1, 0, 0);
	}
	if (g_6b89c0 == 0) {
		g_6b89c0 = (int) fcn_00459ae0(-0.95f, -0.2f, 600.0f);
	}
	for (i = 0; i < 6; i++) {
		if (g_7e4540[i] != 0) {
			fcn_004597f0(g_6b89c0, g_7e4540[i]);
			g_7e4540[i] = 0;
		}
	}
	*(int*) &col = 0xff;
	col.b = 0;
	g_7e4540[0] = fcn_00459870(g_6b89c0, 0, (int) "Sky_Schoen_01", col, g_6a2640, 0, g_6a2644, g_6a2648);
	fcn_00459940(g_6b89c0, g_7e4540[0], 0);
	*(int*) &col = 0;
	col.b = 0;
	g_7e4540[1] = fcn_00459870(g_6b89c0, 0, (int) "Sky_Schoen_02", col, g_6a268c, 0, g_6a2690, g_6a2694);
	fcn_00459940(g_6b89c0, g_7e4540[1], 0);
	*(int*) &col = 0;
	col.b = 0;
	g_7e4540[2] = fcn_00459870(g_6b89c0, 0, (int) "sky_dunkel_01", col, g_6a28f0, 0, g_6a28f4, g_6a28f8);
	fcn_00459940(g_6b89c0, g_7e4540[2], 0);
	player = g_6b8010;
	for (i = 0; i < 64; i++) {
		if (((Slot_52a3a0*) g_1043340)[i].f2c != 0) {
			fcn_004432d0(i, 1);
			fcn_0052a7d0();
		}
	}
	fcn_004432d0(player, 1);
	g_7e4380 = -100;
	g_7746fc = 0;
	fcn_0052a960(now);
}
unsigned char _dpad_7e43a8[400];
unsigned char _dpad_7e4540[364];
