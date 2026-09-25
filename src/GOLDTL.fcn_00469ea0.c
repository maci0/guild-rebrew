// SIZE 0x54
typedef struct {
	char p0[0x30];
	int x30;
	int x34;
	int p38;
	int type;
	int p40;
	int flags;
	int p48;
	int link;
	char p50[4];
} Rec;

extern Rec* g_772500;
extern int g_772504;
extern signed char g_772510;

int __cdecl fcn_00466190(int);
int __cdecl fcn_0047cba0(int, int, int, int, int);

// FUNCTION: GOLDTL 0x00469ea0
// SIZE: 304

int __cdecl fcn_00469ea0(int a1, int a2, int idx, int a4)
{
	int r;
	int base;

	r = 0;
	if (idx <= g_772504) {
		base = -1;
		if ((g_772500[idx].type == 5 || g_772500[idx].type == 8) && g_772500[idx].x30 == 0) {
			if (g_772500[g_772500[idx].link].x34 == 0) {
				r = fcn_00466190(idx);
			}
			base = idx;
			idx = g_772500[idx].link;
		} else if (g_772500[idx].x34 == 0) {
			r = fcn_00466190(idx);
		}
		if (g_772500[idx].flags & 2) {
			idx += g_772510;
		}
		if (r == 0) {
			r = g_772500[idx].x34;
		}
		switch ((base == -1) ? g_772500[idx].type : g_772500[base].type) {
		case 5:
		case 8:
			if (base != -1) {
				r = fcn_0047cba0(a1, a2, a4, r, base - idx);
				break;
			}
		case 1:
		case 4:
			r = fcn_0047cba0(a1, a2, a4, r, 0);
			break;
		case 2:
		case 3:
		case 6:
		case 7:
			return r;
		}
	}
	return r;
}
