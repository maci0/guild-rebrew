/* Recomputes the wage/price curves of one town row: each curve is a list of
 * (value, year) points in g_8680c0; the current date (from the given time
 * source) selects and interpolates a segment by month, the result is scaled by
 * the row's factor, and then every goods cell of the row is refreshed. */

typedef struct {
	int val;
	int key;
} CurvePt;

/* SIZE 0x2f4 */
typedef struct {
	CurvePt a[10];
	CurvePt b[10];
	char pad[0x2f4 - 0xa0];
} CurveRow;

#include "Develop/DieGildeAddOn/game/season_slots.h"



























typedef struct {
	char day;
	char month;
	short year;
	char b4;
	char b5;
	short x6;
	short x8;
} Stamp;

extern CurveRow g_8680c0[];
extern SEASON_TABLE g_85ab80[];
extern char* lpObjektePROT;
extern unsigned char g_773d75;
#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl fcn_00500d60(char*, Stamp*);
void __cdecl fcn_005017a0(int);
void __cdecl fcn_00501fe0(int);
int __cdecl fcn_00502450(int, int);
int __cdecl fcn_005024e0(int, int);
float __cdecl fcn_005025a0(int, int);

/* ADDRESS: GOLDTL 0x005020e0 */
void __cdecl fcn_005020e0(int a0, char* a1)
{
	Stamp stamp;
	int year;
	int n;
	int k;
	int i;
	int v;
	char kind;

	fcn_00500d60(a1, &stamp);
	year = stamp.year;

	for (n = 0; n < 9; n++) {
		if (g_8680c0[a0].a[n].key >= g_8680c0[a0].a[n + 1].key)
			break;
	}
	if (n >= 9)
		n = 9;
	for (k = 0; k < n; k++) {
		if (g_8680c0[a0].a[k].key >= year)
			break;
	}
	if (k >= n - 1) {
		g_85ab80[a0].unk_00 = g_8680c0[a0].a[n].val;
	} else if (year == g_8680c0[a0].a[k].key) {
		g_85ab80[a0].unk_00 = (stamp.month + (year - g_8680c0[a0].a[k].key) * 12) * (g_8680c0[a0].a[k + 2].val - g_8680c0[a0].a[k + 1].val)
		    / ((g_8680c0[a0].a[k + 1].key - g_8680c0[a0].a[k].key) * 12) + g_8680c0[a0].a[k + 1].val;
	} else if (k > 0) {
		g_85ab80[a0].unk_00 = (stamp.month + (year - g_8680c0[a0].a[k - 1].key) * 12) * (g_8680c0[a0].a[k + 1].val - g_8680c0[a0].a[k].val)
		    / ((g_8680c0[a0].a[k].key - g_8680c0[a0].a[k - 1].key) * 12) + g_8680c0[a0].a[k].val;
	} else {
		g_85ab80[a0].unk_00 = g_8680c0[a0].a[1].val;
	}
	g_85ab80[a0].unk_00 = g_85ab80[a0].unk_04 * g_85ab80[a0].unk_00 / 1000;

	for (n = 0; n < 9; n++) {
		if (g_8680c0[a0].b[n].key >= g_8680c0[a0].b[n + 1].key)
			break;
	}
	if (n >= 9)
		n = 9;
	for (k = 0; k < n; k++) {
		if (g_8680c0[a0].b[k].key >= year)
			break;
	}
	if (k >= n - 1) {
		g_85ab80[a0].unk_08 = g_8680c0[a0].b[n].val;
	} else {
		if (year == g_8680c0[a0].b[k].key) {
			v = (stamp.month + (year - g_8680c0[a0].b[k].key) * 12) * (g_8680c0[a0].b[k + 2].val - g_8680c0[a0].b[k + 1].val)
			    / ((g_8680c0[a0].b[k + 1].key - g_8680c0[a0].b[k].key) * 12) + g_8680c0[a0].b[k + 1].val;
		} else if (k > 0) {
			v = (stamp.month + (year - g_8680c0[a0].b[k - 1].key) * 12) * (g_8680c0[a0].b[k + 1].val - g_8680c0[a0].b[k].val)
			    / ((g_8680c0[a0].b[k].key - g_8680c0[a0].b[k - 1].key) * 12) + g_8680c0[a0].b[k].val;
		} else {
			v = g_8680c0[a0].b[1].val;
		}
		g_85ab80[a0].unk_08 = v;
	}
	g_85ab80[a0].unk_08 = g_85ab80[a0].unk_0c * g_85ab80[a0].unk_08 / 1000;
	for (i = 0; i < 85; i++) {
		kind = lpObjektePROT[g_85ab80[a0].slots[i].objekt_id * 0x41];
		if (kind != 0x17 && kind != 0x25) {
			g_85ab80[a0].slots[i].unk_20 = (float) (((double) fcn_00502450(a0, i) - g_85ab80[a0].slots[i].unk_20) * 0.5 + g_85ab80[a0].slots[i].unk_20);
		}
		if (a0 == g_773d75) {
			g_85ab80[a0].slots[i].unk_34 = fcn_005024e0(a0, i);
		} else {
			g_85ab80[a0].slots[i].unk_34 = g_85ab80[a0].slots[i].unk_30;
		}
		g_85ab80[a0].slots[i].unk_38 = fcn_005025a0(a0, i);
		if (g_85ab80[a0].slots[i].entries[0].kind) {
			g_85ab80[a0].slots[i].unk_20 = (float) g_85ab80[a0].slots[i].unk_34;
		}
		g_85ab80[a0].slots[i].unk_10 = 0;
		g_85ab80[a0].slots[i].unk_14 = 0;
		g_85ab80[a0].slots[i].unk_1c = 0;
		g_85ab80[a0].slots[i].unk_18 = 0;
	}
	if (g_14cbca0 == -1) {
		fcn_005017a0(a0);
		fcn_00501fe0(a0);
	}
}
