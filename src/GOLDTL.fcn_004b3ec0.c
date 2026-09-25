extern char g_681130[];
extern char g_68112c[];
extern char g_681110[];
extern int g_14ce8e0;
extern int g_100f1dc;
extern int g_774654;

char* __cdecl fcn_004b3c50(int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_00519190(int);
int __cdecl fcn_0064d41a(char*, char*, ...);
int __cdecl fcn_004c3030(int, int, char*, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);
int __cdecl fcn_00423460(int);
void __cdecl fcn_004237f0(int, int);

// FUNCTION: GOLDTL 0x4b3ec0
// SIZE: 274

int __cdecl fcn_004b3ec0(int a1, int flags)
{
	char buf[0x100];
	char* r;
	int h;
	int w;
	int result;

	result = 0;
	r = fcn_004b3c50(a1);
	h = fcn_00470820(0, 0, g_681130);
	fcn_00471b60(h);
	fcn_004727a0(h, 1);
	fcn_00519190(*(int*) (r + 8) + 1);
	fcn_00519190((int) g_68112c);
	fcn_00519190(0x7d);
	fcn_00519190((int) g_68112c);
	fcn_00519190(0x7e);
	fcn_0064d41a(buf, g_681110, *(int*) (r + 0xc));
	w = fcn_004c3030(-7, 0, buf, -1);
	while (fcn_005373e0(fcn_004b3ec0, flags) != 0) {
		if (g_14ce8e0 != 0 || g_100f1dc == 1)
			g_774654 = 1;
		if (g_100f1dc == 2) {
			result = 1;
			g_774654 = 1;
		}
	}
	if (h != -1)
		fcn_00471e30(h);
	if (fcn_00423460(w) != 0)
		fcn_004237f0(w, 0x19);
	return result;
}
