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

/* SIZE 0x80; row header words overlay cell 0, as in client_town.h */
typedef struct {
	int x0;
	int x4;
	int x8;
	int xc;
	unsigned short id;
	char p12[0xe];
	int x20;
	int x24;
	int x28;
	int x2c;
	float f30;
	char p34[0xc];
	int x40;
	int x44;
	float f48;
	char p4c[4];
	unsigned char b50;
	char p51[0x2f];
} Cell;

/* SIZE 0x2a90 */
typedef struct {
	Cell c[85];
	char tail[0x10];
} TownRow;

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
extern TownRow g_85ab80[];
extern char* lpObjektePROT;
extern unsigned char g_773d75;
extern int g_14cbca0;
extern double g_662908;

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
		g_85ab80[a0].c[0].x0 = g_8680c0[a0].a[n].val;
	} else if (year == g_8680c0[a0].a[k].key) {
		g_85ab80[a0].c[0].x0 = (stamp.month + (year - g_8680c0[a0].a[k].key) * 12) * (g_8680c0[a0].a[k + 2].val - g_8680c0[a0].a[k + 1].val)
		    / ((g_8680c0[a0].a[k + 1].key - g_8680c0[a0].a[k].key) * 12) + g_8680c0[a0].a[k + 1].val;
	} else if (k > 0) {
		g_85ab80[a0].c[0].x0 = (stamp.month + (year - g_8680c0[a0].a[k - 1].key) * 12) * (g_8680c0[a0].a[k + 1].val - g_8680c0[a0].a[k].val)
		    / ((g_8680c0[a0].a[k].key - g_8680c0[a0].a[k - 1].key) * 12) + g_8680c0[a0].a[k].val;
	} else {
		g_85ab80[a0].c[0].x0 = g_8680c0[a0].a[1].val;
	}
	g_85ab80[a0].c[0].x0 = g_85ab80[a0].c[0].x4 * g_85ab80[a0].c[0].x0 / 1000;

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
		g_85ab80[a0].c[0].x8 = g_8680c0[a0].b[n].val;
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
		g_85ab80[a0].c[0].x8 = v;
	}
	g_85ab80[a0].c[0].x8 = g_85ab80[a0].c[0].xc * g_85ab80[a0].c[0].x8 / 1000;
	for (i = 0; i < 85; i++) {
		kind = lpObjektePROT[g_85ab80[a0].c[i].id * 0x41];
		if (kind != 0x17 && kind != 0x25) {
			g_85ab80[a0].c[i].f30 = (float) (((double) fcn_00502450(a0, i) - g_85ab80[a0].c[i].f30) * g_662908 + g_85ab80[a0].c[i].f30);
		}
		if (a0 == g_773d75) {
			g_85ab80[a0].c[i].x44 = fcn_005024e0(a0, i);
		} else {
			g_85ab80[a0].c[i].x44 = g_85ab80[a0].c[i].x40;
		}
		g_85ab80[a0].c[i].f48 = fcn_005025a0(a0, i);
		if (g_85ab80[a0].c[i].b50) {
			g_85ab80[a0].c[i].f30 = (float) g_85ab80[a0].c[i].x44;
		}
		g_85ab80[a0].c[i].x20 = 0;
		g_85ab80[a0].c[i].x24 = 0;
		g_85ab80[a0].c[i].x2c = 0;
		g_85ab80[a0].c[i].x28 = 0;
	}
	if (g_14cbca0 == -1) {
		fcn_005017a0(a0);
		fcn_00501fe0(a0);
	}
}
