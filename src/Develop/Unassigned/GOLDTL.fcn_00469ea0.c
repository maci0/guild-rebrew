extern int g_772504;

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

extern char* g_772500;
extern signed char g_772510;

int __cdecl d2_GetResourceData(int);
int __cdecl fcn_0047cba0(int, int, int, int, int);


/* ADDRESS: GOLDTL 0x00469ea0 */
int __cdecl fcn_00469ea0(int a1, int a2, int idx, int a4)
{
	int r;
	int base;

	r = 0;
	if (idx <= g_772504) {
		base = -1;
		if ((((Rec*)g_772500)[idx].type == 5 || ((Rec*)g_772500)[idx].type == 8) && ((Rec*)g_772500)[idx].x30 == 0) {
			if (((Rec*)g_772500)[((Rec*)g_772500)[idx].link].x34 == 0) {
				r = d2_GetResourceData(idx);
			}
			base = idx;
			idx = ((Rec*)g_772500)[idx].link;
		} else if (((Rec*)g_772500)[idx].x34 == 0) {
			r = d2_GetResourceData(idx);
		}
		if (((Rec*)g_772500)[idx].flags & 2) {
			idx += g_772510;
		}
		if (r == 0) {
			r = ((Rec*)g_772500)[idx].x34;
		}
		switch ((base == -1) ? ((Rec*)g_772500)[idx].type : ((Rec*)g_772500)[base].type) {
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
