


extern int g_772514;
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_67d370;
extern int g_774654;
extern int g_7e46ac;
extern unsigned short g_774970;
extern unsigned char g_773d75;
extern int g_665f78[];
extern char g_7f4ca0[];

int __cdecl fcn_00470820(int, int, int);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_005340f0(int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_00526010(void*, int, char);
int __cdecl fcn_004f2f90(void*, int, char*, int, int, int);
int __cdecl fcn_004c4450(int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_0051af00(void*, int, ...);
void __cdecl fcn_00526120(char*, int);

int __cdecl fcn_0058c890(char* a1, int a2, unsigned char a3, int a4)
{
	int r;
	int ok;
	int cancel;
	char buf[0x200];
	int dlg;
	int cost;
	int id;
	int h;
	int s;

	r = 0;
	cost = *(unsigned short*) (a1 + 0x27) != g_774970 ? 16000 : 0;
	dlg = fcn_00470820(0, 0, (int) "Locations\\Friedhof\\Friedhof");
	fcn_00473a90(0, 0);
	fcn_00471b60(dlg);
	fcn_004727a0(dlg, 0);
	fcn_005340f0(g_772514);
	fcn_004727a0(dlg, 1);
	if (*(unsigned short*) (a1 + 0x27) == g_774970) {
		fcn_00519190(0x4115, 0x4112, a1, g_665f78[a4]);
	} else {
		fcn_00519190(0x4114, 0x4112, g_665f78[a4], cost);
	}
	fcn_004727a0(dlg, 2);
	id = fcn_00519190(0x4116);
	ok = fcn_00472250(dlg, 2, id);
	cancel = fcn_00472250(dlg, 2, id + 1);
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		} else if (g_100f1dc != -1) {
			if (g_67d370 == ok) {
				if (cost == 0 || fcn_00526010(g_7f4ca0 + g_774970 * 540, cost, (*(char*)&g_773d75)) != 0) {
					h = fcn_004f2f90(g_7f4ca0 + g_774970 * 540, a4, a1, a2, a3, cost);
					while (h != -1 && (s = fcn_004c4450(h)) == 0) {
						fcn_005373e0((void*) s, 0x20007);
					}
					g_7e46ac = 0x677c7;
					if (fcn_004c4450(h) == 2) {
						fcn_0051af00(buf, 0x411b, 0x4112, g_665f78[a4]);
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
	} while (fcn_005373e0((void*) fcn_0058c890, 0x677c7) != 0);
	fcn_00471e30(dlg);
	return r;
}
