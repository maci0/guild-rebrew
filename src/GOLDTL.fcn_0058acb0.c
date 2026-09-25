// FUNCTION: GOLD 0x582670
// SIZE: 429
// FUNCTION: GOLDTL 0x58acb0
// SIZE: 429

// SIZE 0x21c
struct house {
	unsigned short id;
	unsigned char type;
	char pad3;
	int handle;
	char pad8[0x214];
};

extern struct house g_7f4ca0[];
extern unsigned short g_774970;
extern int g_772514;
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_67d370;
extern int g_774654;

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_005340f0(int);
int __cdecl fcn_00519190();
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_00525f60(struct house*, int);
void __cdecl fcn_005100f0(int, int);
void __cdecl fcn_004c4510(char*, int);
void __cdecl fcn_004c4570(int, int, int, int*);
int __cdecl fcn_004c5360(void);
int __cdecl fcn_004c4450(int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_00532ef0(void);

void __cdecl fcn_0058acb0(int unused, char* p)
{
	int ok;
	int cancel;
	int b;
	int h;
	int s;
	int v;
	int id;

	b = *(int*) (p + 0x20);
	h = fcn_00470820(0, 0, "Locations\\Domizil\\kabinett");
	fcn_00473a90(0, 0);
	fcn_00471b60(h);
	fcn_004727a0(h, 0);
	fcn_005340f0(g_772514);
	fcn_004727a0(h, 1);
	fcn_00519190("$C");
	fcn_00519190(0x407d, 0x4171, b);
	fcn_004727a0(h, 2);
	s = fcn_00519190(0x407e);
	ok = fcn_00472250(h, 2, s);
	cancel = fcn_00472250(h, 2, s + 1);
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		} else if (g_100f1dc != -1) {
			if (g_67d370 == ok) {
				if (fcn_00525f60(&g_7f4ca0[g_774970], b) == 1) {
					v = 0;
					fcn_005100f0(g_7f4ca0[g_774970].handle, -b);
					fcn_004c4510(p, *(int*) (p + 2));
					fcn_004c4570(4, 1, 0x1c, &v);
					fcn_004c4570(4, 1, 0x20, &v);
					id = fcn_004c5360();
					while (id != -1 && fcn_004c4450(id) == 0) {
						fcn_005373e0(0, 0x20007);
					}
					g_774654 = 1;
				}
			} else if (g_67d370 == cancel) {
				g_774654 = 1;
			}
		}
	} while (fcn_005373e0(fcn_0058acb0, 0x677c7) != 0);
	fcn_00471e30(h);
	fcn_00532ef0();
}
