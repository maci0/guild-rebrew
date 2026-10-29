

extern int g_772514;
extern int g_14ac498;
extern int g_14ac49c;
extern int g_14ac4a0;
extern int g_14ce8e0;
extern char g_14cf950;
extern int g_774654;
extern int g_14ce8d8;
extern int g_67d370;

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_00473a90(int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl fcn_005e3b10(int, int, int);
int __cdecl d2_CreateRadioGroup(int, ...);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00469630(int);
void __cdecl fcn_00471af0(int, int);
void __cdecl fcn_005e3520(void);
void __cdecl fcn_005e2b60(void);
void __cdecl fcn_005e3150(void);
void __cdecl fcn_00469510(int);
void __cdecl fcn_00471e30(int);

void __cdecl fcn_005e4820(void)
{
	int h;
	int b1;
	int b2;
	int b3;
	int p;

	h = fcn_00470820(0, 0, "menu\\options");
	fcn_00471b60(h);
	fcn_00473a90(0, 0);
	d2_SetForm(0, 1);
	b1 = fcn_005e3b10(1, g_14ac498, g_772514);
	b2 = fcn_005e3b10(2, g_14ac49c, g_772514);
	b3 = fcn_005e3b10(3, g_14ac4a0, g_772514);
	p = d2_CreateRadioGroup(3, b1, b2, b3);
	while (fcn_005373e0(fcn_005e4820, 0x24087) != 0) {
		if (g_14ce8e0 != 0 || (*(unsigned char*)&g_14cf950) == 1) {
			g_774654 = 1;
		}
		fcn_00469630(p);
		if (g_14ce8d8 != 0 && g_67d370 != -1) {
			if (g_67d370 == b1) {
				fcn_00471af0(h, 0);
				fcn_005e3520();
				fcn_00471af0(h, 1);
			} else if (g_67d370 == b2) {
				fcn_00471af0(h, 0);
				fcn_005e2b60();
				fcn_00471af0(h, 1);
			} else if (g_67d370 == b3) {
				fcn_00471af0(h, 0);
				fcn_005e3150();
				fcn_00471af0(h, 1);
			}
		}
	}
	fcn_00469510(p);
	fcn_00471e30(h);
}
