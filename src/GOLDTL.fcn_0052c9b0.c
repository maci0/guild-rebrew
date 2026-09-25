// FUNCTION: GOLDTL 0x0052c9b0
// SIZE: 512

// SIZE 0x90
typedef struct {
	char pad0[0x4c];
	int x;
	int y;
	int z;
	char pad58[0x84 - 0x58];
	int rx;
	int ry;
	int rz;
} View;

// SIZE 0x21c
typedef struct {
	char pad0[0x21c];
} Rec;

extern View* g_6b8014;
extern int g_6b7fc0;
extern int g_7e4300;
extern int g_6a99e8;
extern int g_14ce8e8;
extern int g_774668;
extern int g_7e46ac;
extern char g_6a2574;
extern char g_14cf70f;
extern int g_774650;
extern int g_774658;
extern int g_7746c4;
extern int g_7746c8;
extern unsigned short g_774970;
extern Rec g_7f4ca0[];
extern int g_774694;
extern int g_7e3a40;
extern int g_7e3a44;
extern int g_7e3a48;
extern int g_7e3a50;
extern int g_7e3a54;
extern int g_7e3a58;
extern int g_6772c4;
extern short g_14ce8c0;
extern int g_1040494;
extern int g_1040490;
extern int g_6b5c80;
extern int g_6b5c84;
extern int g_6772bc;
extern int g_6772c0;

int __cdecl fcn_0052b720(void);
void __cdecl fcn_0052c060(void);
void __cdecl fcn_0052ad70(void);
char* __cdecl fcn_00509570(Rec* r);
void __cdecl fcn_004125c0(int a, int b);

int __cdecl fcn_0052c9b0(void)
{
	char* p;

	if (g_6b8014 != 0 && g_6b7fc0 == 0) {
		if (g_7e4300 == 0 && g_6a99e8 == -1) {
			if (g_14ce8e8 == 0) {
				g_774668 = fcn_0052b720();
			}
			if (!(g_7e46ac & 0x8000)) {
				fcn_0052c060();
			}
			if (g_6a2574 != 0 && g_14cf70f == 0) {
				fcn_0052ad70();
			}
			if (g_774668 != 0 && g_774650 == g_774658 && g_7746c4 == 0 && g_7746c8 == 0) {
				p = fcn_00509570(&g_7f4ca0[g_774970]);
				if (p != 0) {
					*(int*) (p + 0x8c) = g_6b8014->x;
					*(int*) (p + 0x90) = g_6b8014->y;
					*(int*) (p + 0x94) = g_6b8014->z;
					*(int*) (p + 0x9c) = g_6b8014->rx;
					*(int*) (p + 0xa0) = g_6b8014->ry;
					*(int*) (p + 0xa4) = g_6b8014->rz;
					*(int*) (p + 0x88) = g_774694;
				}
			}
			g_7e3a50 = g_6b8014->rx;
			g_7e3a54 = g_6b8014->ry;
			g_7e3a58 = g_6b8014->rz;
			g_7e3a40 = g_6b8014->x;
			g_7e3a44 = g_6b8014->y;
			g_7e3a48 = g_6b8014->z;
		}
		return g_774668;
	}
	g_774668 = 0;
	if (g_6772c4 == 0) {
		g_6b5c80 = 0;
		g_6b5c84 = 0;
		g_6772bc = g_1040494 - 8;
		g_6772c0 = g_1040490;
		g_6772c4 = 1;
		fcn_004125c0(g_14ce8c0, g_14ce8c0);
	}
	return 0;
}
