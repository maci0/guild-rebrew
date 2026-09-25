// FUNCTION: GOLDTL 0x539380
// SIZE: 258

extern int g_6a375c;
extern int g_14ce8e0;
extern int g_774654;
extern int g_100f1dc;
extern char g_6a3a04[];
extern char g_6a2300[];

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
int __cdecl fcn_00472250(int, int, int);
void __cdecl fcn_00472380(int, int, int, int);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_00519190(int, ...);
int __cdecl fcn_005373e0(int (__cdecl*)(void), int);
unsigned char __cdecl fcn_00471f80(int);
void __cdecl fcn_00471af0(int, int);
void __cdecl fcn_00471e30(int);

int __cdecl fcn_00539380(void)
{
	int result;
	int h;
	int d;
	unsigned char mode;

	result = 0;
	h = fcn_00470820(0, 0, g_6a3a04);
	fcn_00471b60(h);
	d = fcn_00472250(h, 0, 0);
	mode = *(unsigned char*) &g_6a375c;
	*(unsigned char*) &g_6a375c = 2;
	if (mode >= 2) {
		*(unsigned char*) &g_6a375c = mode;
	}
	fcn_00472380(d, 2, 8, (unsigned char) g_6a375c);
	fcn_00473a90(0, 0);
	fcn_004727a0(h, 1);
	fcn_00519190(0x1ab5);
	fcn_004727a0(h, 2);
	fcn_00519190((int) g_6a2300, 0x7d, 0x7e);
	while (fcn_005373e0(fcn_00539380, 0x24087) != 0) {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_100f1dc == 1) {
			g_774654 = 1;
		} else if (g_100f1dc == 2) {
			*(unsigned char*) &g_6a375c = fcn_00471f80(d);
			fcn_00471af0(h, 0);
			result = 1;
			g_774654 = 1;
		}
	}
	if (h != -1) {
		fcn_00471e30(h);
	}
	return result;
}
