extern char g_68c340[];
extern char* g_77255c;
extern int g_772514;
extern int g_68bfb8;
extern int g_100f1dc;
extern int g_774654;
extern int g_67d370;

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471d80(int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_004677e0(int, int, int, int, int, int, int, int);
int __cdecl fcn_004e6e20(int, int, int);
int __cdecl fcn_004aacb0(unsigned short*, unsigned short*, unsigned short*, int*);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);


/* ADDRESS: GOLDTL 0x004dc230 */
int __cdecl fcn_004dc230(unsigned short* a1, unsigned short* a2, unsigned short* a3, int* a4)
{
	int aux;
	int h;
	int t;
	int b0;
	int b2;
	int w;
	int res;

	*a4 = 0;
	h = fcn_00470820(0, 0, g_68c340);
	fcn_00471d80(h, 1);
	d2_SetForm(h, 0);
	t = io_AppendText(0x12c6, *a2, *a1);
	b0 = fcn_00472250(h, 0, t);
	fcn_00472250(h, 0, t + 1);
	b2 = fcn_00472250(h, 0, t + 2);
	w = fcn_004677e0((*(int*) (g_77255c + 0xc) - 300) / 2 - 8, 8, 300, 0, 100, 0x75, 0x42, g_772514);
	fcn_004e6e20(w, 0x5dc, 1);
	res = fcn_004aacb0(a1, a2, a3, &aux);
	g_100f1dc = -1;
	while (fcn_005373e0(fcn_004dc230, g_68bfb8) != 0) {
		if (fcn_004e6e20(w, 0, 0) == 0) {
			g_774654 = 1;
		} else if (g_100f1dc != -1) {
			res = 0;
			g_774654 = 1;
			if (g_67d370 != b0)
				res = (g_67d370 != b2) + 1;
		}
	}
	fcn_00471e30(h);
	return res;
}
