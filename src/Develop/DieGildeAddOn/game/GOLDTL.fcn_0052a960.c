

#pragma pack(2)
// SIZE 0xe
typedef struct {
	int day;
	unsigned short hour;
	int minute;
	int second;
} Stamp;
#pragma pack()

typedef struct {
	char pad0[0x2c];
	int f2c;
	char pad30[0x3dc - 0x30];
} Slot_52a960;
// SIZE 0x3dc

#include "client_types.h"

extern int g_6a2902;
extern int g_6a290c;
extern int g_6a2916;
extern int g_6a2920;
extern int g_6a292a;
extern int g_6a2934;
extern unsigned char* g_7e4548;
extern int g_6b8010;
extern Slot_1043340 g_1043340[64];
extern int g_7e4468;
extern int g_7e446c;
extern int g_6b7fac;
extern int g_77472c;
extern float g_7e42e0;
extern int g_7e4380;
extern int g_7e2a60;
extern int g_6b5cc0;
extern int g_6a2bd8;
extern char g_7746fc;
extern int g_67a370;
extern int g_774728;
extern float g_6a2bec;

double __cdecl fabs(double);
int __cdecl abs(int);
#pragma intrinsic(fabs, abs)

char __cdecl fcn_0052a910(char* e, int flag);
void __cdecl fcn_004463f0(int a, int b, float v);
void __cdecl fcn_004379a0(int list, int a, int mask, char (__cdecl* fn)(char*, int), int arg);
void __cdecl fcn_00445f50(int idx, float frac, float w, int changed);

/* Day-light phase from the clock. v is reused for the truncated phase so it
 * shares the dead parameter slot, and the 0.2 test is written !(d > 0.2)
 * for the reference's `and eax, 0x4100` form. */
void __cdecl fcn_0052a960(Stamp* now)
{
	int s;
	int v;
	float light;
	float x;
	float frac;
	int idx;
	int changed;

	light = 0.0f;
	s = (now->hour * 60 + now->minute) * 60;
	if (s < g_6a2902) {
		v = 0;
	} else if (s < g_6a290c) {
		v = (s - g_6a2902) * 100 / (g_6a290c - g_6a2902);
	} else if (s < g_6a2916) {
		v = (s - g_6a290c) * 100 / (g_6a2916 - g_6a290c) + 100;
	} else if (s < g_6a2920) {
		v = (s - g_6a2916) * 200 / (g_6a2920 - g_6a2916) + 200;
	} else if (s < g_6a292a) {
		v = (s - g_6a2920) * 100 / (g_6a292a - g_6a2920) + 400;
	} else if (s < g_6a2934) {
		v = (s - g_6a292a) * 100 / (g_6a2934 - g_6a292a) + 500;
	} else {
		v = 600;
	}
	if (g_7e4548 != 0) {
		light = g_7e4548[0x2a] * 0.003921569f;
	}
	if (((Slot_52a960*)g_1043340)[g_6b8010].f2c != 0 && (unsigned int) g_6b7fac < (unsigned int) (g_7e4468 + g_7e446c)) {
		fcn_004463f0(0, 2, 1.0f);
		g_77472c = 1;
		return;
	}
	if (g_77472c != 0) {
		fcn_004463f0(0, 1, light);
		g_77472c = 0;
	}
	if ((fabs(g_7e42e0 - 1.0f) < 0.1 && abs(g_7e4380 - v) < 10 && g_7e2a60 == g_6b8010) || g_6b5cc0 != 0) {
		fcn_004463f0(0, 1, light);
		return;
	}
	if (!(fabs(g_7e42e0 - 1.0f) > 0.2) && abs(g_7e4380 - v) < 100) {
		changed = g_7e2a60 != g_6b8010;
	} else {
		changed = 1;
	}
	g_7e2a60 = g_6b8010;
	g_7e4380 = v;
	g_7e42e0 = 1.0f;
	x = (float)(v * 0.01);
	v = (int) x;
	idx = v % 7;
	if (g_6a2bd8 != idx && ((Slot_52a960*)g_1043340)[g_6b8010].f2c != 0) {
		if (idx >= 0 && g_7746fc == 0) {
			fcn_004379a0(g_67a370, 0, 6, fcn_0052a910, 0);
			g_7746fc++;
		} else if (idx >= 3 && g_7746fc == 1) {
			fcn_004379a0(g_67a370, 0, 6, fcn_0052a910, 1);
			g_7746fc++;
		}
		g_6a2bd8 = idx;
	}
	g_774728 = idx;
	frac = x - v;
	g_6a2bec = frac;
	fcn_00445f50(idx, frac, 1.0f, changed);
	fcn_004463f0(0, 1, light);
}
