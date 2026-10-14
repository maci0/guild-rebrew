

typedef struct Device Device;

// SIZE 0x94
typedef struct {
	char pad0[0x90];
	void(__stdcall* clear)(Device* self, int a, int b, int c, int d, float e, int f);
} DeviceVtbl;

// SIZE 0x4
struct Device {
	DeviceVtbl* vtbl;
};

extern int g_6a2bdc;
extern int g_7725c8;
extern void* g_6b5de0;
extern int g_774710;
extern int g_1040490;
extern int g_1040494;
extern char g_67d67c[];
extern int g_6a25ac;
extern int g_774670;

void __cdecl fcn_005270c0(int show);
void __cdecl fcn_00533cf0(int v);
int __cdecl fcn_004675f0(int x, int y, int w, int a, int b, int c, int d);
void __cdecl fcn_00472380(int h, int a, int b, int c);
void __cdecl fcn_0046b2b0(int h);
void __cdecl fcn_004730c0(int a, int b, int w, int h, char* s, int c, int d);
void __cdecl fcn_00527f60(int a, int b);
void __cdecl fcn_0046a110(int v);
void __cdecl fcn_0041bcb0(void);

void __cdecl fcn_00526bf0(int phase, int cur, int max)
{
	if (g_6a2bdc == -1) {
		g_7725c8 = 1;
		fcn_005270c0(0);
		fcn_00533cf0(1);
		((Device*)g_6b5de0)->vtbl->clear(((Device*)g_6b5de0), 0, 0, 1, 0, 1.0f, 0);
		g_774710 = 0;
		g_6a2bdc = fcn_004675f0(g_1040494 / 2 - 0xcd, g_1040490 - 0x40, 0x190, 0, 0x190, 0x83, 0x42);
		fcn_00472380(g_6a2bdc, 0, 0x190, 0);
		if (g_6a2bdc == -1) {
			g_774710++;
			return;
		}
	}
	if (phase == 0) {
		fcn_00472380(g_6a2bdc, 0, 0x190, cur * 200 / max);
	} else if (phase == 1) {
		fcn_00472380(g_6a2bdc, 0, 0x190, cur * 200 / max + 200);
		if (cur >= max - 1) {
			fcn_0046b2b0(g_6a2bdc);
			g_6a2bdc = -1;
			g_7725c8 = 0;
			fcn_004730c0(0, 0, g_1040494, g_1040490, g_67d67c, 0x5a, 2);
			fcn_005270c0(1);
			fcn_00533cf0(0);
			if (g_6a25ac != -1) {
				fcn_00527f60(1, 0);
			}
			g_774670 = 1;
		}
	}
	if (g_774710 % 10 == 0 && g_6a2bdc != -1) {
		fcn_0046a110(1);
		fcn_0041bcb0();
	}
	g_774710++;
}
