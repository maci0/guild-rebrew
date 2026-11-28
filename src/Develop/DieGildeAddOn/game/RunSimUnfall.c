

#define MAXV(a, b) (((a) > (b)) ? (a) : (b))
#define MINV(a, b) (((a) < (b)) ? (a) : (b))

#pragma pack(push, 1)
typedef struct {
	int day;
	unsigned short hour;
	int minute;
	unsigned short x;
} Clock;
// SIZE 0xe

typedef struct {
	char pad0[0x27];
	unsigned short x27;
} Home;
// SIZE 0x29
#pragma pack(pop)

typedef struct {
	char pad0[0x16c];
	Home* home;
	char pad170[0xac];
} Player;
// SIZE 0x21c

#include "Develop/client_types.h"

extern pos14_7f4c00 gm_GameTime;
extern char g_7f4ca0[];

void __cdecl he_FreeAction(char* s);
void __cdecl io_FormatTextBuffer(char* buf, char* fmt, ...);
unsigned short __cdecl gm_RandomMod(int n);
int __cdecl he_IsEntityEligibleForAccident(Player* p);
float __cdecl gm_RandomFloat01(void);
int __cdecl gm_GetBuildingTechEffect(Home* h, int a, int b);
float __cdecl gm_ApplyEntityHealthDelta(unsigned short id, int delta);
void __cdecl he_HandleAccidentOutcome(char* s, Player* p, Player* q, Home* h, float v, int f);
void __cdecl gm_AddTime(Clock* c, int a, int b, int d);

/* One step of the accident simulation: walks twelve players in a
 * pseudo-random order and rolls an accident for each. */
void __cdecl RunSimUnfall(char* s)
{
	float f;
	int count;
	int r;
	int steps[16];
	char buf[0x200];
	int idx;
	float x;
	float y;
	Player* p;

	if (*(int*) (s + 0x70) == -2) {
		he_FreeAction(s);
		return;
	}
	io_FormatTextBuffer(buf, "-------> RunSimUnfall: calculating at <Day = %i Time = %i.2:%i.2>", ((Clock*) &gm_GameTime)->day,
		((Clock*) &gm_GameTime)->hour, ((Clock*) &gm_GameTime)->minute);
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
		p = &((Player*) g_7f4ca0)[idx];
		if (he_IsEntityEligibleForAccident(p) != 0 && ((Player*) g_7f4ca0)[idx].home->x27 != 0xffff) {
			f = gm_RandomFloat01() * 100.0f;
			r = gm_GetBuildingTechEffect(((Player*) g_7f4ca0)[idx].home, 2, 1);
			x = r * 0.0125f;
			if (25.0f - 20.0f * x > f) {
				y = MINV(MAXV(2.0f - x, 0.0f), 2.0f);
				f = gm_ApplyEntityHealthDelta(idx, -50 - gm_RandomMod((int) (y * 255.0f + 1.0f)));
				he_HandleAccidentOutcome(s, p, &((Player*) g_7f4ca0)[((Player*) g_7f4ca0)[idx].home->x27], ((Player*) g_7f4ca0)[idx].home, f, 0);
			}
		}
		idx = (*(int*) (s + 0xb0) + idx) % 0x300;
		(*(int*) (s + 0xb4))++;
	} while (--count != 0);
	*(int*) (s + 0xac) = idx;
	if (*(int*) (s + 0xb4) >= 0x300) {
		*(int*) (s + 0xac) = 0;
		*(int*) (s + 0xb0) = 0;
		*(int*) (s + 0xb4) = 0;
		((Clock*) (s + 0x52))->day++;
		((Clock*) (s + 0x52))->minute = 0;
		((Clock*) (s + 0x52))->hour = 10;
		return;
	}
	gm_AddTime((Clock*) (s + 0x52), 0, 0x1e, 0);
	if (((Clock*) (s + 0x52))->hour >= 0x12) {
		((Clock*) (s + 0x52))->minute = 0;
		((Clock*) (s + 0x52))->hour = 10;
		((Clock*) (s + 0x52))->day++;
	}
}
