#include "client_types.h"

extern unsigned char g_7747b0;
extern unsigned char* lpGebaeudePROT;
extern float g_696540[4];
extern float g_696550[4];

#pragma pack(push, 2)
typedef struct
{
	int day;
	unsigned short hour;
	int min;
	int sec;
} Time;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct
{
	int f0;
	unsigned short f4;
	int f6;
} TimeKey;
#pragma pack(pop)

#define MAXF(a, b) ((a) > (b) ? (a) : (b))
#define MINF(a, b) ((a) < (b) ? (a) : (b))
#define CLAMPF(v, lo, hi) MINF(MAXF((lo), (v)), (hi))

int __cdecl fcn_00500e20(int* p);
int __cdecl fcn_00500d20(TimeKey* a, TimeKey* b);
int __cdecl fcn_00500cb0(Time* a, Time* b);
void __cdecl sim_SetSyncParams(int target, unsigned char type_id, unsigned int field_6, unsigned int field_10);

/* Interpolates the sync time between two dated times: the start record's
 * minute-of-day is scaled, the remainder is distributed over the days
 * between the records, and the end record's minute-of-day is scaled too. */
/* ADDRESS: GOLDTL 0x0050c830 */
int __cdecl fcn_0050c830(Time* a0, Time* a1, char* a2)
{
	float f1;
	float f2;
	double d;
	Time t;
	int idx;
	int i;
	int n;
	int k;
	int acc;
	int res1;

	idx = fcn_00500e20((int*) a0);
	f1 = g_696540[idx];
	f2 = g_696550[idx];
	if ((g_7747b0 & 0x80) != 0) {
		return fcn_00500d20((TimeKey*) a0, (TimeKey*) a1);
	}
	if (a2 != 0) {
		if (lpGebaeudePROT[*(unsigned char*) a2 * 0x24d] == 0x1d) {
			return fcn_00500d20((TimeKey*) a0, (TimeKey*) a1);
		}
	}
	if (fcn_00500cb0(a0, a1) > 0) {
		return 0;
	}
	t = *a0;
	i = t.day;
	n = a1->day;
	if (i < n) {
		acc = (int) (f2 * 60.0f - (float) (int) CLAMPF((float) (t.min + t.hour * 60), f1 * 60.0f, f2 * 60.0f));
		i = i + 1;
		t.day = i;
		sim_SetSyncParams((int) &t, (unsigned char) (int) f1, 0, 0);
	} else {
		acc = 0;
	}
	if (i < n) {
		d = f2 * 60.0f - f1 * 60.0f;
		for (k = n - i; k != 0; k--) {
			acc = (int) ((double) acc + d);
		}
	}
	res1 = (int) CLAMPF((float) (a1->min + a1->hour * 60), f1 * 60.0f, f2 * 60.0f);
	return acc - (int) CLAMPF((float) (t.min + t.hour * 60), f1 * 60.0f, f2 * 60.0f) + res1;
}
