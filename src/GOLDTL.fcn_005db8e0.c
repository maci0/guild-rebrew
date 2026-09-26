// FUNCTION: GOLDTL 0x005db8e0
// SIZE: 637

// SIZE 0xf8
struct msg {
	int f0;
	char b4;
	char pad5[3];
	int f8;
	int fc;
	char pad10[0x26];
	char b36;
	char pad37[0x21];
	int f58;
	char b5c;
	char pad5d[3];
	int f60;
	char pad64[0x94];
};

typedef struct Ent {
	unsigned short id;
	short pad2;
	int handle;
} Ent;

typedef struct Req {
	unsigned short id;
	short pad2;
	int handle;
	char pad8;
	unsigned char female;
} Req;

typedef struct Win {
	char pad0[0xc];
	int w;
	int h;
	char pad14[0x3cc - 0x14];
} Win;
// SIZE 0x3cc

typedef struct Slot {
	char pad0[0x5c];
	int shown;
	char pad60[0xcc - 0x60];
	char text[0x100];
	int color;
	int style;
	char pad1d4[0x2f4 - 0x1d4];
} Slot;
// SIZE 0x2f4

typedef struct Font {
	char pad0[0x1d978];
	short w;
} Font;

extern Win g_1015f40[];
extern Slot* g_1015ea0;
extern Font* g_772500;
extern int g_772514;
extern char* g_14a5adc[15];
extern int g_7e46ac;
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_14ce8d8;
extern int g_774654;

int __cdecl fcn_0050dac0(unsigned short id);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_0046f740(int x, int y, int id, int win);
int __cdecl fcn_005373e0(void*, int);
char __cdecl fcn_00507400(int, int);
void __cdecl fcn_004c5530(struct msg*);
void __cdecl fcn_00471e30(int);

int __cdecl fcn_005db8e0(Ent* e, Req* p)
{
	int colw;
	int n;
	int dlg;
	int rowh;
	struct msg m;
	int x0;
	int id;
	char* d;
	char* s;
	int result;
	char c;
	int i;

	n = fcn_0050dac0(e->id) * 0.015f;
	dlg = fcn_00470820(0, 0, "privillegien\\CHOOSEPROFESSION2");
	fcn_00471b60(dlg);
	fcn_004727a0(dlg, 0);
	colw = (g_1015f40[g_772514].w - 0x40) / 5;
	rowh = (g_1015f40[g_772514].h - 0x84) / 3;
	x0 = (colw - g_772500->w) / 2;
	fcn_00519190(0x1a9a, (p->female != 0) + 0x1aa0, p->id, n);
	for (i = 1; i <= 15; i++) {
		id = fcn_0046f740((i - 1) % 5 * colw + x0 + 0x20, (i - 1) / 5 * rowh + x0 + 0x64, i - 1 + 0x5a2, g_772514);
		g_1015ea0[id].shown = 1;
		g_1015ea0[id].style = 3;
		s = g_14a5adc[i - 1];
		d = g_1015ea0[id].text;
		do {
			c = *s++;
			*d++ = c;
		} while (c != 0);
		g_1015ea0[id].color = 0x56;
	}
	result = 0;
	while (fcn_005373e0(fcn_005db8e0, g_7e46ac) != 0) {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		} else if (g_14ce8d8 != 0) {
			result = 1;
			for (i = 0; i <= 15; i++) {
				if (g_100f1dc == i + 0x5a2) {
					m.b36 = 0x12;
					m.b4 = 0x5e;
					m.f8 = p->handle;
					m.fc = -1;
					m.f58 = e->handle;
					m.b5c = fcn_00507400(i + 1, result);
					m.f60 = n;
					fcn_004c5530(&m);
					g_774654 = result;
					break;
				}
			}
		}
	}
	fcn_00471e30(dlg);
	return result;
}
