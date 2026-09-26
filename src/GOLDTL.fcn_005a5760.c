// FUNCTION: GOLDTL 0x005a5760
// SIZE: 539

typedef struct
{
	char pad0[0x18];
	int x18;
	char pad1c[0x38];
	int x54;
	char pad58[4];
	int x5c;
	char pad60[0xc];
	int x6c;
	char pad70[0x2f4 - 0x70];
} Ctl;
// SIZE 0x2f4

typedef struct
{
	int icon;
	int name;
	int info;
	int id;
	unsigned char owner;
	char pad11[0xb];
} Row;
// SIZE 0x1c

typedef struct
{
	int x0;
	char pad4[8];
	int width;
} Screen;

extern int g_772514;
extern char* g_77255c;
extern char* g_1015ea0;
extern int g_14a79c0[];
extern char g_868060[];

void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00466ee0(int, int, int, int, int);
int __cdecl fcn_0046f740(int, int, int, int);
int __cdecl fcn_0046fac0(int, int, char*, int);
void __cdecl fcn_0051af00(void*, char*, ...);
void __cdecl fcn_0046f940(int, char*);
void __cdecl fcn_00472900(int, int);

void __cdecl fcn_005a5760(Row* rows, int a2, int a3, int a4)
{
	char buf[0x80];
	int i;

	for (i = 0; i < 16; i++) {
		if (rows[i].id == 0) {
			return;
		}
		fcn_004727a0(a2, a3);
		if (a4 != 0) {
			rows[i].icon = fcn_00466ee0((((Screen*)g_77255c)->width - 0x30) >> 1, i * 0x4c, rows[i].id + 0xdf, 0x82, g_772514);
		} else {
			rows[i].icon = fcn_0046f740((((Screen*)g_77255c)->width - 0x30) >> 1, i * 0x4c, rows[i].id + 0xdf, g_772514);
			((Ctl*)g_1015ea0)[rows[i].icon].x5c = 1;
		}
		((Ctl*)g_1015ea0)[rows[i].icon].x54 = 1;
		rows[i].name = fcn_0046fac0((((Screen*)g_77255c)->width - 0xbe) >> 1, i * 0x4c + 0x30, "", g_772514);
		fcn_0051af00(buf, "%S", g_14a79c0[rows[i].id * 2]);
		fcn_0046f940(rows[i].name, buf);
		fcn_00472900(rows[i].icon, 0x54);
		fcn_00472900(rows[i].name, 0x54);
		((Ctl*)g_1015ea0)[rows[i].name].x6c = 1;
		((Ctl*)g_1015ea0)[rows[i].name].x18 = 0xbe;
		rows[i].info = fcn_0046fac0((((Screen*)g_77255c)->width - 0xbe) >> 1, i * 0x4c + 0x3f, "", g_772514);
		fcn_0051af00(buf, "%s", g_868060 + rows[i].owner * 0x2f4);
		fcn_0046f940(rows[i].info, buf);
		fcn_00472900(rows[i].info, 0x54);
		((Ctl*)g_1015ea0)[rows[i].info].x6c = 1;
		((Ctl*)g_1015ea0)[rows[i].info].x18 = 0xbe;
	}
}
