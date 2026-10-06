// FUNCTION: GOLD 0x0059fd40
// FUNCTION: GOLDTL 0x005a9070

extern unsigned char g_773d75;
extern int g_14ce8e0;
extern int g_774654;
extern char g_6aae08[];

char* __cdecl fcn_00502cd0(int, int, int, int, int);
int __cdecl fcn_0050b810(int, char);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00532ef0(void);
void __cdecl fcn_00471e30(int);

void __cdecl fcn_005a9070(char* e)
{
	char* r;
	int v;
	int h;

	r = fcn_00502cd0(*(int*) (e + 0x5d), 2, 6, 0, 0x115);
	v = fcn_0050b810(*(int*) (r + 0x14), (*(char*)&g_773d75));
	h = fcn_00470820(0, 0, g_6aae08);
	fcn_00471b60(h);
	fcn_004727a0(h, 1);
	fcn_00519190(0x1a0f, v);
	while (fcn_005373e0(fcn_005a9070, 0x677c7) != 0) {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
	}
	fcn_00532ef0();
	fcn_00471e30(h);
}
