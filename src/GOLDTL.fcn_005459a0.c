extern int g_77e8a0;
extern int g_772514;
extern int g_1040490;
extern int g_1040494;
extern int g_6a4768;
extern int g_6a476c;

// SIZE 0xc
struct s_77e8c0 {
	char* p;
	int h;
	int x8;
};

extern struct s_77e8c0 g_77e8c0[16];

// SIZE 0x3cc
struct s_1015f4c {
	char pad[0x270];
	int f270;
	char pad2[0x158];
};

extern struct s_1015f4c g_1015f4c[];

// FUNCTION: GOLDTL 0x5459a0
// SIZE: 211

void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_00469c40(int, int, int);
void __cdecl fcn_00471af0(int, int);

void __cdecl fcn_005459a0(int a)
{
	int i;

	if (g_6a476c != -1) {
		for (i = 0; i < 16; i++) {
			if (g_77e8c0[i].h != -1 && g_77e8c0[i].x8 != -1) {
				fcn_00471af0(g_77e8c0[i].x8, 0);
			}
		}
		fcn_004727a0(g_77e8a0, 0);
		fcn_00469c40(g_1040494 - 0x7d, g_1040490 - 0x21, g_1015f4c[g_772514].f270);
		fcn_00471af0(g_77e8a0, 0);
	}
	if (a != 0xffff) {
		fcn_00471af0(g_77e8a0, 1);
		for (i = 0; i < 16; i++) {
			if (g_77e8c0[i].h == -1) {
				break;
			}
		}
		g_6a4768 = i;
		g_6a476c = g_77e8a0;
	} else {
		g_6a4768 = -1;
		g_6a476c = -1;
	}
}
