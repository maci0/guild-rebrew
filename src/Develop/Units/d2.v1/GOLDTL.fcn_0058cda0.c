


// SIZE 0x21c
struct house {
	unsigned short id;
	unsigned char type;
	char pad3;
	int handle;
	char pad8[0x214];
};

extern char g_7f4ca0[];
extern unsigned short g_774970;
extern unsigned char g_773d75;
extern int g_772514;
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_67d370;
extern int g_774654;
extern int g_665f78[];
extern int g_7e46ac;

int __cdecl fcn_004f4440(struct house*, int, int, int, int*);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_005340f0(int);
int __cdecl fcn_00519190();
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_00526010(struct house*, int, unsigned char);
int __cdecl fcn_004f2540(struct house*, char*, int, int, int);
int __cdecl fcn_004c4450(int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_00526120(char*, int);
void __cdecl fcn_00471e30(int);

int __cdecl fcn_0058cda0(char* who, int k)
{
	int h;
	int r;
	int ok;
	int cancel;
	int got;
	char buf[0x200];
	int x;
	int s;
	int id;

	r = 0;
	if (*(unsigned short*) (who + 0x27) == g_774970) {
		x = 0;
	} else {
		x = fcn_004f4440(&((struct house*)g_7f4ca0)[g_774970], 0xff, k, 1, &got);
	}
	h = fcn_00470820(0, 0, "Locations\\Friedhof\\Friedhof");
	fcn_00473a90(0, 0);
	fcn_00471b60(h);
	d2_SetForm(h, 0);
	fcn_005340f0(g_772514);
	d2_SetForm(h, 1);
	if (*(unsigned short*) (who + 0x27) == g_774970) {
		fcn_00519190(0x410c, 0x4109, who, g_665f78[k]);
	} else {
		fcn_00519190(0x410b, 0x4108, g_665f78[k], x);
	}
	d2_SetForm(h, 2);
	s = fcn_00519190(0x410d);
	ok = fcn_00472250(h, 2, s);
	cancel = fcn_00472250(h, 2, s + 1);
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		} else if (g_100f1dc != -1) {
			if (g_67d370 == ok) {
				if (x == 0 || fcn_00526010(&((struct house*)g_7f4ca0)[g_774970], x, g_773d75) != 0) {
					id = fcn_004f2540(&((struct house*)g_7f4ca0)[g_774970], who, k, 10, x);
					while (id != -1 && fcn_004c4450(id) == 0) {
						fcn_005373e0(0, 0x20007);
					}
					g_7e46ac = 0x677c7;
					if (fcn_004c4450(id) == 2) {
						fcn_0051af00(buf, 0x411b, (*(unsigned short*) (who + 0x27) == g_774970) + 0x4108,
						    g_665f78[k]);
						fcn_00526120(buf, 0x100);
					} else {
						g_774654 = 1;
						r = 1;
					}
				}
			} else if (g_67d370 == cancel) {
				g_774654 = 1;
			}
		}
	} while (fcn_005373e0(fcn_0058cda0, 0x677c7) != 0);
	fcn_00471e30(h);
	return r;
}
