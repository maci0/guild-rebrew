


extern int g_772514;
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_774654;
extern int g_67d370;
extern char g_6a96f4[];
extern char g_6a4078[];

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_005340f0(int);
int __cdecl fcn_00519190();
void __cdecl fcn_0058c4f0(char* a, int dlg, int mode, int* ids, int* sel);
int __cdecl fcn_0058c780(char* a1, int a2, int a3, int* a4, int* a5);
int __cdecl fcn_0058c890(char* a1, int a2, int a3, int a4);
int __cdecl fcn_00472250(int, int, int);
void __cdecl fcn_00472640(int i, int flag);
void __cdecl fcn_00471af0(int k, int flag);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);

int __cdecl fcn_0058cae0(char* p, int a1, int a2)
{
	volatile int sel;
	int res;
	int ids[4];
	int d;
	volatile int back;
	int i;

	sel = 0;
	res = 0;
	d = fcn_00470820(0, 0, g_6a96f4);
	fcn_00473a90(0, 0);
	fcn_00471b60(d);
	fcn_004727a0(d, 0);
	fcn_005340f0(g_772514);
	fcn_004727a0(d, 1);
	fcn_00519190(0x4113, 0x4112);
	fcn_0058c4f0(p, d, 2, ids, (int*) &sel);
	fcn_004727a0(d, 3);
	back = fcn_00472250(d, 3, fcn_00519190(g_6a4078, 0x4119));
	fcn_00472640(back, fcn_0058c780(p, a1, a2, ids, (int*) &sel));
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		else if (g_100f1dc != -1) {
			if (g_67d370 == back) {
				fcn_00471af0(d, 0);
				if (fcn_0058c890(p, a1, a2, sel) == 1) {
					res = 1;
					g_774654 = 1;
				}
				fcn_00471af0(d, 1);
			}
			else {
				for (i = 0; i < 4; i++) {
					if (g_67d370 == ids[i] && i != sel) {
						goto found;
					}
				}
				continue;
found:
				sel = i;
				fcn_0058c4f0(p, d, 2, ids, (int*) &sel);
				fcn_00472640(back, fcn_0058c780(p, a1, a2, ids, (int*) &sel));
			}
		}
	} while (fcn_005373e0(fcn_0058cae0, 0x677c7) != 0);
	fcn_00471e30(d);
	return res;
}
