// FUNCTION: GOLDTL 0x005ced80

typedef struct
{
	char pad0[0x38];
	int x38;
	char pad3c[0x20];
	int x5c;
	char pad60[0x170];
	int x1d0;
	char pad1d4[0x11c];
	char* x2f0;
} Ctl;
// SIZE 0x2f4

typedef struct
{
	int id;
	unsigned char b4;
	unsigned char b5;
	char pad6[2];
} Entry;
// SIZE 0x8

typedef struct
{
	char type;
	char pad1[64];
} Rec65;
// SIZE 0x41

extern int g_772514;
extern char* g_1015ea0;
extern char* g_99ec10;

void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_0046f740(int, int, int, int);
void __cdecl fcn_00472640(int, int);
int __cdecl fcn_004677e0(int, int, int, int, int, int, int, int);
void __cdecl fcn_00472380(int, int, int, int);

void __cdecl fcn_005ced80(int dlg, Entry* list, int* bars, int* icons)
{
	int i;
	int h;

	fcn_004727a0(dlg, 1);
	fcn_00519190((int) "$C");
	fcn_00519190(0x1949);
	fcn_004727a0(dlg, 2);
	fcn_00519190((int) "$C");
	for (i = 0; i < 7; i++) {
		if (list[i].id != 0) {
			h = fcn_0046f740(0xf, i * 0x30, list[i].id + 0xdf, g_772514);
			((Ctl*)g_1015ea0)[h].x1d0 = 3;
			((Ctl*)g_1015ea0)[h].x2f0 = &((Rec65*)g_99ec10)[list[i].id].type;
			fcn_00472640(h, 1);
			((Ctl*)g_1015ea0)[h].x5c = 1;
			((Ctl*)g_1015ea0)[h].x38 = list[i].b5 == 0;
			icons[i] = h;
			bars[i] = fcn_004677e0(0x64, i * 0x30 + 0xc, 0xc8, 0, 0x64, 0x7b, 0x802, g_772514);
			fcn_00472380(bars[i], 0, 0x64, list[i].b4);
			fcn_00472640(bars[i], list[i].b5 == 0);
		} else {
			bars[i] = -1;
			icons[i] = -1;
		}
	}
}
