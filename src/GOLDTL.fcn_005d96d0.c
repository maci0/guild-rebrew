// FUNCTION: GOLDTL 0x005d96d0

extern int g_100f1dc;
extern int g_774654;
extern int g_14ce8e0;

void __cdecl fcn_004c6ae0(int, int);
unsigned short __cdecl gm_RandomMod(int);
void __cdecl fcn_005d9000(char*, int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00525f60(char*, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);

int __cdecl fcn_005d96d0(char* e)
{
	int r;
	int dlg;

	if (e[2] != 6 && e[2] != 7) {
		if (*(int*) (e + 0x194) < 4) {
			return 0x20;
		}
		fcn_004c6ae0(*(int*) (e + 4), -4);
		fcn_005d9000(e, gm_RandomMod(6));
		return 0x10;
	}
	if (e[2] == 6) {
		r = 0;
		dlg = fcn_00470820(0, 0, "privillegien\\wunder");
		fcn_00473a90(0, 0);
		fcn_00471b60(dlg);
		fcn_004727a0(dlg, 1);
		fcn_00519190(0x1df6, 4);
		g_100f1dc = -1;
		do {
			if (g_100f1dc != -1) {
				if (g_100f1dc == 2) {
					if (fcn_00525f60(e, 4) != 0) {
						fcn_004c6ae0(*(int*) (e + 4), -4);
						fcn_005d9000(e, gm_RandomMod(6));
						r = 1;
						g_774654 = 1;
					}
				} else if (g_100f1dc == 1) {
					g_774654 = 1;
				}
			}
			if (g_14ce8e0 != 0) {
				g_774654 = 1;
			}
		} while (fcn_005373e0((void*) fcn_005d96d0, 0x657c7) != 0);
		fcn_00471e30(dlg);
		return r;
	}
	return 0;
}
