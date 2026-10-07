// FUNCTION: GOLDTL 0x005e4cd0

extern int g_772514;
extern char* g_1015ea0;
extern int g_14ac660[];
extern int g_14ce8e0;
extern char g_14cf950;
extern int g_774654;

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_0046f740(int, int, int, int);
void __cdecl fcn_00472900(int, int);
void __cdecl fcn_0046f9b0(int, int);
int __cdecl fcn_0057de80(int);
void __cdecl fcn_00472380(int, int);
int __cdecl fcn_005373e0(void*, int);
int __cdecl fcn_00471f80(int);
void __cdecl fcn_0057df50(int, int);
void __cdecl fcn_00471e30(int);

void __cdecl fcn_005e4cd0(void)
{
	int h;
	int btn[16];
	int i;
	int b;

	h = fcn_00470820(0, 0, "menu\\messagefilter");
	fcn_00471b60(h);
	fcn_004727a0(h, 2);
	for (i = 0; i < 9; i++) {
		b = fcn_0046f740(8, i * 0x1c + 0xa, 0x605 + i, g_772514);
		btn[i] = b;
		*(int*) (g_1015ea0 + b * 0x2f4 + 0x58) = 1;
		*(int*) (g_1015ea0 + b * 0x2f4 + 0x5c) = 1;
		fcn_00472900(b, 0x55);
		fcn_0046f9b0(b, g_14ac660[i]);
		*(int*) (g_1015ea0 + b * 0x2f4 + 0x1d4) = 0x78;
		*(int*) (g_1015ea0 + b * 0x2f4 + 0x1dc) = 0x1e;
		*(int*) (g_1015ea0 + b * 0x2f4 + 0x1e0) = 3;
		fcn_00472380(b, fcn_0057de80(0x605 + i) == 0);
	}
	while (fcn_005373e0(fcn_005e4cd0, 0x677c7) != 0) {
		if (g_14ce8e0 != 0 || (*(unsigned char*)&g_14cf950) == 1) {
			g_774654 = 1;
			for (i = 0; i < 9; i++) {
				fcn_0057df50(0x605 + i, fcn_00471f80(btn[i]) == 0);
			}
		}
	}
	fcn_00471e30(h);
}
