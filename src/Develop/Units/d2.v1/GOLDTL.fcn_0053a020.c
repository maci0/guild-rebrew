


extern char g_6a3a80[];
extern int g_14ce8e0;
extern char g_14cf950;
extern int g_774654;
extern int g_100f1dc;
extern int g_67d370;

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
int __cdecl fcn_00472250(int, int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl fcn_005373e0(int (__cdecl*)(void), int);
int __cdecl d2_CreateRadioGroup(int, int, int);
void __cdecl fcn_00469630(int);
void __cdecl fcn_00469510(int);
void __cdecl fcn_00471af0(int, int);
void __cdecl fcn_00471e30(int);
int __cdecl fcn_00539600(void);
int __cdecl fcn_00539930(int);

int __cdecl fcn_0053a020(void)
{
	int list;
	int b;
	int result;
	int h;
	int a;

	result = 0;
	h = fcn_00470820(0, 0, g_6a3a80);
	fcn_00471b60(h);
	d2_SetForm(h, 0);
	io_AppendText(0x1ca5);
	a = fcn_00472250(h, 0, io_AppendText(0x1ca9));
	b = fcn_00472250(h, 0, io_AppendText(0x1caa));
	list = d2_CreateRadioGroup(2, a, b);
	while (fcn_005373e0(fcn_0053a020, 0x24087) != 0) {
		fcn_00469630(list);
		if (g_14ce8e0 != 0 || g_14cf950 == 1) {
			g_774654 = 1;
			result = 0;
		}
		if (g_100f1dc != -1) {
			if (g_67d370 == a) {
				fcn_00471af0(h, 0);
				if (fcn_00539600() != 0) {
					g_774654 = 1;
					result = 1;
				}
				fcn_00471af0(h, 1);
			} else if (g_67d370 == b) {
				fcn_00471af0(h, 0);
				if (fcn_00539930(1) != 0) {
					g_774654 = 1;
					result = 1;
				}
				fcn_00471af0(h, 1);
			}
		}
	}
	fcn_00469510(list);
	fcn_00471e30(h);
	return result;
}
