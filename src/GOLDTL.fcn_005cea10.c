

extern int g_14ce8e0;
extern int g_774654;
extern char g_6aca6c[];
extern int g_772514;
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_005340f0(int);
void __cdecl fcn_00473a90(int, int);
int __cdecl fcn_00519190(char*, ...);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);

void __cdecl fcn_005cea10(void)
{
	int h;

	h = fcn_00470820(0, 0, g_6aca6c);
	fcn_004727a0(h, 0);
	fcn_005340f0(g_772514);
	fcn_00471b60(h);
	fcn_00473a90(0, 0);
	fcn_004727a0(h, 1);
	fcn_00519190((char*) 0x1949);
	fcn_00519190((char*) 0x194e);
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
	} while (fcn_005373e0(fcn_005cea10, 0x677c7) != 0);
	fcn_00471e30(h);
}
