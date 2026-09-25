// FUNCTION: GOLDTL 0x4b6210
// SIZE: 168

extern int g_6a3760;
extern int g_681130;
extern int g_100f1dc;
extern int g_774954;
extern int g_774654;

unsigned short* __cdecl fcn_00508e40(int h);
int __cdecl fcn_00470820(int a, int b, int* c);
void __cdecl fcn_00471b60(int h);
void __cdecl fcn_004727a0(int h, int on);
void __cdecl fcn_00519190(int id, int a, int b);
int __cdecl fcn_005373e0(void (__cdecl* cb)(int), int flags);
void __cdecl fcn_00471e30(int h);
void __cdecl fcn_004b5b20(int arg);

void __cdecl fcn_004b6210(int arg)
{
	int mode;
	unsigned short* p;
	int h;

	mode = 0;
	p = fcn_00508e40(g_6a3760);
	h = fcn_00470820(mode, mode, &g_681130);
	fcn_00471b60(h);
	fcn_004727a0(h, 1);
	fcn_00519190(0x1b97, *p, *p);
	g_100f1dc = -1;
	do {
		if (g_6a3760 == -1) {
			mode = (g_774954 != 0) + 1;
			g_774654 = 1;
		}
	} while (fcn_005373e0(fcn_004b6210, arg | 0x80) != 0);
	fcn_00471e30(h);
	if (mode == 2) {
		fcn_004b5b20(arg);
	}
}
