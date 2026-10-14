


extern int g_772514;
extern int g_14ce8e0;
extern int g_774654;
extern char g_6aa8d0[];

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_005340f0(int);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_0046e830(int, int, int, int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);

void __cdecl fcn_005a0960(void)
{
	int h;
	int a;

	h = fcn_00470820(0, 0, g_6aa8d0);
	fcn_00471b60(h);
	fcn_004727a0(h, 0);
	fcn_005340f0(g_772514);
	fcn_00473a90(0, 0);
	fcn_004727a0(h, 2);
	a = g_772514;
	fcn_004727a0(h, 3);
	fcn_0046e830(-1, -1, g_772514, a, 0x767);
	fcn_004727a0(h, 1);
	fcn_00519190(0x1889);
	fcn_004727a0(h, 2);
	fcn_00519190(0x188a);
	while (fcn_005373e0(fcn_005a0960, 0x677c7) != 0) {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
	}
	fcn_00471e30(h);
}
