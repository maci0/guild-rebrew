extern int g_67d370;
extern int g_772514;
extern char* g_1015ea0;

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(char* fmt, ...);
int __cdecl fcn_00472250(int, int, int);
int __cdecl d2_CreateRadioGroup(int);
int __cdecl fcn_0052dee0(int, int, int);
char* __cdecl fcn_00502cd0(int, int, int, ...);
void __cdecl fcn_00469470(int, int);
void __cdecl fcn_004695a0(int, int);
void __cdecl fcn_00476b60(void);
int __cdecl fcn_0046f2c0(int, int);
int __cdecl fcn_00472830(int, int);
int __cdecl fcn_0046f740(int, int, int, int);
void __cdecl fcn_00469510(int);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_004116d0(void);
int __cdecl fcn_005373e0(void* fn, int arg);

/* ADDRESS: GOLDTL 0x004bec20 */
unsigned int __cdecl fcn_004bec20(int a0, int a1, unsigned int a2)
{
	int handles[7];
	int ids[7];
	int list[0x30];
	int items[0x30];
	int g;
	int v4;
	int v6;
	unsigned int v7;
	unsigned int v17;
	int v18;
	int v2;
	int i;
	int k;
	int n;
	char* p;
	char* p2;

	ids[0] = 0x95;
	ids[1] = 0x92;
	ids[2] = 0x93;
	ids[3] = 0x94;
	ids[4] = 0x97;
	ids[5] = 0x96;
	ids[6] = 0x2db;
	v2 = 1;
	v18 = -1;
	v17 = a2;
	g = fcn_00470820(0, 0, "misc\\routing_choose_good_enhanced");
	fcn_00471b60(g);
	d2_SetForm(g, 1);
	io_AppendText("$Z%2N3$A%1G", *(unsigned short*) (a0 + 0x27), a0);
	d2_SetForm(g, 4);
	v4 = fcn_00472250(g, 4, io_AppendText(0x7d));
	d2_SetForm(g, 3);
	k = d2_CreateRadioGroup(0);
	for (i = 0; i < 7; i++) {
		v6 = fcn_0052dee0(0, 4 + i * 0x1e, *(int*) (0x14a56e8 + i * 4));
		handles[i] = v6;
		v7 = fcn_00502cd0(*(int*) (a0 + 0x5d), 2, 6, 0, *(int*) (ids + i));
		*(int*) (g_1015ea0 + 0x2f0 + v6 * 0x2f4) = v7;
		fcn_00469470(k, v6);
	}
	fcn_004695a0(k, 0);
	fcn_00476b60();
	for (;;) {
		n = g * 0x8c;
		if (*(int*) 0x14ce8e0 != 0 || v17 != 0 || (*(int*) 0x100f1dc != -1 && g_67d370 == v4)) {
			*(int*) 0x774654 = 1;
		}
		if (*(int*) (0x102cbc8 + n) != v18 || v2) {
			d2_SetForm(g, 2);
			fcn_0046f2c0(fcn_00472830(g, 2), 0);
			for (i = 0; i < 0x30; i++) {
				list[i] = -1;
			}
			i = 0;
			v6 = *(int*) (g_1015ea0 + 0x2f0 + handles[*(int*) (0x102cbc8 + n)] * 0x2f4);
			if (v6 != 0) {
				v7 = *(unsigned int*) (v6 + 0x14);
			} else {
				v7 = *(unsigned int*) (a0 + 0x5d);
			}
			p = fcn_00502cd0(v7, 1, 0, 0xff);
			if (p != 0) {
				p2 = fcn_00502cd0(*(unsigned int*) (p + 0x14), 1, 5, 0);
				while (p2 != 0) {
					items[i] = *(unsigned short*) p2;
					v6 = fcn_0046f740((i & 3) * 0x40, (i >> 2) * 0x40, *(unsigned short*) p2 + 0xdf, g_772514);
					list[i] = v6;
					*(int*) (g_1015ea0 + v6 * 0x2f4 + 0x5c) = 1;
					*(int*) (g_1015ea0 + v6 * 0x2f4 + 0x1d0) = 3;
					*(int*) (g_1015ea0 + v6 * 0x2f4 + 0x1e4) = 0x525;
					p2 = fcn_00502cd0(p2, 1, 5, 0);
					i++;
				}
			}
			items[i] = 0;
			v6 = fcn_0046f740((i & 3) * 0x40 + 7, (i >> 2) * 0x40 + 7, 0x527, g_772514);
			list[i] = v6;
			v2 = 0;
			*(int*) (g_1015ea0 + v6 * 0x2f4 + 0x5c) = 1;
			*(int*) (g_1015ea0 + v6 * 0x2f4 + 0x1d0) = 3;
			v18 = *(int*) (0x102cbc8 + n);
		}
		if (*(int*) 0x100f1dc != -1) {
			for (i = 0; i < 0x30; i++) {
				if (g_67d370 == list[i]) {
					v17 = items[i];
					break;
				}
			}
		}
		if (!fcn_005373e0((void*) 0x4bec20, 0x657c7)) {
			fcn_00469510(k);
			fcn_00471e30(g);
			fcn_004116d0();
			return v17;
		}
	}
}
