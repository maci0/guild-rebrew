extern int g_677508;
extern int g_773ddc;
extern int g_6b8300;
extern int g_6b5c80;
extern int g_6772bc;
extern int g_6772c0;
extern unsigned short g_774970;
extern unsigned char g_7747b0;
extern int g_6b5c84;
extern unsigned char g_772d10;
extern char g_774964;
extern int g_774950;
extern int g_7f4c04;
extern int g_7f4e10;
extern int g_774650;
extern int g_774658;
extern int g_14ce8d4;
extern int g_14ce8e4;
extern int g_7746b0;
extern int g_6b5cc0;
extern int g_100f1dc;
extern int g_67d370;
extern int g_6a25dc;
extern int g_7e2aa0;
extern int g_14ce8dc;
extern int g_14ce8cc;
extern unsigned short g_7725c4;
extern int g_7725c8;
extern int g_6772c4;
extern int g_100f1e8;
extern int g_100f1ec;
extern int g_773d78;
extern int g_7e2700;
extern int g_7e2704;
extern int g_7e2708;

int __cdecl fcn_00500e20(char*);
void __cdecl fcn_00516f60(void);
void __cdecl fcn_0043c2c0(int* a0);
void __cdecl fcn_005c80f0(void);
void* __cdecl fcn_00503fe0(int, int, ...);
void* __cdecl fcn_00503e80(void);
void __cdecl fcn_0052cf20(int a0);
void __cdecl fcn_004c39b0(void);
void __cdecl fcn_0042df30(int a1, int a2);
int __cdecl fcn_005373e0(int a1, int a2);
void __cdecl fcn_0059a8f0(void);
void __cdecl fcn_0052c9b0(void);
void* __cdecl fcn_00426cc0(int a1);
int __cdecl fcn_00428720(int a1);
void __cdecl fcn_0052db70(int a0);
void __cdecl fcn_0059a2a0(void);
void __cdecl fcn_0052cbb0(int a0);
void __cdecl fcn_00599350(void);
int __cdecl fcn_00506380(int a, int b, int c, int d);
int __cdecl fcn_00505370(void* a0);
int __cdecl fcn_0057eba0(int a, int b, int c, int d);
void __cdecl fcn_005a80d0(int a0);
int __cdecl fcn_00505340(void* a0);
void __cdecl fcn_005a76b0(int a, int b);
void __cdecl fcn_005a3b30(int a0);
void __cdecl fcn_004c3a10(void);
void __cdecl fcn_00475220(char* a);
void __cdecl fcn_00533a40(char* a);
void __cdecl fcn_00530510(void);
void __cdecl fcn_004125c0(int x, int y);

/* ADDRESS: GOLDTL 0x0059a340 */
void __cdecl fcn_0059a340(void)
{
	int v7;
	int v3;
	int v4;
	int v5;
	int v6;
	int fx;
	int v10;
	int v11;
	int v8;
	int v9;
	int state;
	short v13;
	char* p;
	char* v12;
	char c;

	v7 = fcn_00500e20((char*) 0x7f4c00);
	g_677508 = -1;
	fcn_00516f60();
	if (g_773ddc) {
		fcn_0043c2c0((int*) g_6b8300);
		g_773ddc = 0;
	}
	v6 = g_6b5c84;
	v5 = g_6b5c80;
	v4 = g_6772c0;
	v3 = g_6772bc;
	g_772d10 = 1;
	g_774964 = 1;
	v13 = g_774970;
	if (g_7747b0 & 4) {
		v12 = (char*) 0x7f4ca2;
		do {
			if (*(short*) (v12 - 2) != -1
				&& *(int*) (v12 + 0x52) == *(int*) (g_774970 * 0x21c + 0x7f4cf4)
				&& *(short*) (v12 - 2) != g_774970
				&& (c = *v12, c == 6 || c == 7 || c == 5)
				&& *(unsigned int*) (g_774970 * 0x21c + 0x7f4ca4) < *(unsigned int*) (v12 + 2)) {
				fcn_005c80f0();
				v13 = g_774970;
				break;
			}
			v12 += 0x21c;
		} while ((int) v12 < (int) 0x85a0a2);
	}
	if ((g_7747b0 & 1) && g_774950 == 1) {
		v8 = (int) fcn_00503fe0(1, 4, v13);
		while (v8) {
			if (v8 != *(int*) (g_774970 * 0x21c + 0x7f4e10)) {
				fcn_0052cf20(v8);
				break;
			}
			v8 = (int) fcn_00503e80();
		}
	}
	fcn_004c39b0();
	v8 = 0;
	fcn_0042df30(0x538060, 0);
	v9 = fcn_005373e0(0x59a340, 0x67fff);
	do {
		if (!v9) {
			g_772d10 = 0;
			g_774964 = 0;
			fcn_004c3a10();
			fcn_00475220((char*) 0x6b5c60);
			fcn_00533a40((char*) 0x6b5c60);
			fcn_00530510();
			g_7725c4 = 0;
			g_7725c8 = 0;
			g_6772c4 = 1;
			fcn_004125c0(g_100f1e8, g_100f1ec);
			g_6772bc = v3;
			g_6772c0 = v4;
			g_6b5c80 = v5;
			g_6b5c84 = v6;
			fcn_005373e0(0, 0x67fff);
			return;
		}
		g_774658 = g_774650;
		if (*(unsigned char*) (g_774970 * 0x21c + 0x7f4e51) > 0)
			fcn_0059a8f0();
		fcn_0052c9b0();
		fx = g_7f4c04 & 0xffff;
		if (v8 == 0) {
			if ((float) fx < *(float*) (v7 * 4 + 0x696540)
				|| *(float*) (v7 * 4 + 0x696550) <= (float) fx) {
				v8 = (int) fcn_00503fe0(1, 6);
				while (v8) {
					if (*(int*) (v8 + 0x95) != -1) {
						v9 = (int) fcn_00426cc0(*(int*) (v8 + 0x95));
						if (v9)
							fcn_00428720(v9);
						*(int*) (v8 + 0x95) = -1;
					}
					v8 = (int) fcn_00503e80();
				}
				v8 = 1;
			}
		} else if (v8 == 1) {
			if (*(float*) (v7 * 4 + 0x696540) <= (float) fx
				&& (float) fx < *(float*) (v7 * 4 + 0x696550)) {
				v8 = (int) fcn_00503fe0(1, 6);
				while (v8) {
					if (*(int*) (v8 + 0x95) == -1)
						fcn_0052db70(v8);
					v8 = (int) fcn_00503e80();
				}
				v8 = 2;
			}
		} else if (v8 == 2) {
			if ((float) fx < *(float*) (v7 * 4 + 0x696540)
				|| *(float*) (v7 * 4 + 0x696550) <= (float) fx) {
				v8 = (int) fcn_00503fe0(1, 6);
				while (v8) {
					if (*(int*) (v8 + 0x95) != -1) {
						v9 = (int) fcn_00426cc0(*(int*) (v8 + 0x95));
						if (v9)
							fcn_00428720(v9);
						*(int*) (v8 + 0x95) = -1;
					}
					v8 = (int) fcn_00503e80();
				}
				v8 = 3;
			}
		}
		fcn_0059a2a0();
		if (g_14ce8d4 && !g_14ce8e4 && g_7746b0 && !g_6b5cc0)
			fcn_0052cbb0(g_7746b0);
		if (g_100f1dc != -1 && g_67d370 == g_6a25dc)
			fcn_00599350();
		if (g_7e2aa0) {
			v10 = fcn_00506380(g_774970, g_7e2aa0, 0, 0);
			v9 = g_7e2aa0;
			if (v9 && g_7746b0 == v9
				&& (g_14ce8dc
					|| (g_14ce8cc && g_7725c4 == 0xb))
				&& (v10 & 1)
				&& !(*(unsigned char*) (v9 + 0x5a) & 1)) {
				v11 = fcn_00505370((void*) v9);
				if (v11 && fcn_0057eba0(0x1b, v9, 0, 0) == 1)
					fcn_005a80d0(v9);
				else if (!fcn_00505340((void*) v9)
					&& fcn_0057eba0(0x19, v9, 0,
						*(unsigned short*) (v9 + 0x29)) == 1)
					fcn_005a76b0(v9,
						*(unsigned short*) (v9 + 0x29));
			}
		}
		if (g_773d78)
			fcn_005a3b30(g_773d78);
		v9 = g_7e2704;
		if (g_7e2700) {
			if (g_7e2708) {
				*(unsigned short*) (v9 + 0x29) =
					*(unsigned short*) g_7e2708;
				if (!
					(*(unsigned char*) (v9 + 0x5a) & 1)) {
					if (*(int*) (v9 + 0x61)
						&& !fcn_00505340((void*) v9))
						fcn_0052cf20(v9);
					if (fcn_00505370((void*) v9)) {
						fcn_005a80d0(v9);
						goto label_59a83a;
					}
					if (!fcn_00505340((void*) v9)) {
						fcn_005a76b0(v9,
							*(unsigned short*) (v9 + 0x29));
						goto label_59a83a;
					}
					if (fcn_00505340((void*) v9)) {
						fcn_0052cbb0(v9);
						goto label_59a834;
					}
					goto label_59a83a;
				}
			} else {
				fcn_0052cbb0(v9);
			}
label_59a834:
			g_7e2700 = 0;
		}
label_59a83a:
		v9 = fcn_005373e0(0x59a340, 0x67fff);
	} while (1);
}
