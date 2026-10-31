

extern char g_6a4120[];
extern signed char g_6a3440;
extern int g_14ce8e0;
extern char g_14cf950;
extern int g_774654;
extern int g_100f1dc;

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
int __cdecl fcn_00472250(int, int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl fcn_005373e0(int (__cdecl*)(void), int);
int __cdecl d2_CreateRadioGroup(int, ...);
void __cdecl fcn_00469630(int);
void __cdecl fcn_00469510(int);
void __cdecl fcn_00471e30(int);

int __cdecl fcn_0053e8a0(void)
{
	int result;
	int h;
	int s;
	int a;
	int list;

	result = 0;
	h = fcn_00470820(0, 0, g_6a4120);
	fcn_00471b60(h);
	io_AppendText(0x1adf);
	if ((*(char*)&g_6a3440) != -1) {
		io_AppendText(0x1ae0);
	}
	s = io_AppendText(0x1ae1);
	a = fcn_00472250(h, 0, s);
	list = d2_CreateRadioGroup(2, a, fcn_00472250(h, 0, s + 1));
	while (fcn_005373e0(fcn_0053e8a0, 0xc6) != 0) {
		fcn_00469630(list);
		if (g_14ce8e0 != 0 || g_14cf950 == 1) {
			result = -1;
			g_774654 = 1;
		}
		if (g_100f1dc == 2 || g_14cf950 == 0x1c) {
			result = 1;
			g_774654 = 1;
		} else if (g_100f1dc == 1) {
			g_774654 = 1;
		}
	}
	fcn_00469510(list);
	fcn_00471e30(h);
	return result;
}
