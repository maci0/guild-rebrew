extern char* lpGebaeudePROT;
extern int g_100f1dc;
extern int g_67d370;
extern int g_774654;
extern int g_14ce8e0;

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
int __cdecl io_AppendText(int, ...);
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);

/* ADDRESS: GOLDTL 0x005bdfc0 */
int __cdecl fcn_005bdfc0(unsigned short* a0, unsigned char* a1, int a2, int a3)
{
	int btn;
	char* info;
	int dlg;
	int x_dlg = -1;
	int y_dlg = -1;
	int handled = 0;
	int r;

	info = lpGebaeudePROT + *a1 * 0x24d;
	dlg = fcn_00470820(0, 0, (char*) 0x6ac448);
	fcn_00471b60(dlg);
	io_AppendText(0x10b);
	if (*a0 != 0x116) {
		if (a2 >= (int) (unsigned char) info[0x240]) {
			io_AppendText(0x110);
		} else {
			btn = io_AppendText(0x10c, 0x1f40);
			x_dlg = fcn_00472250(dlg, 0, btn);
		}
		if (a3 >= (int) (unsigned char) info[0x241]) {
			io_AppendText(0x111);
		} else {
			y_dlg = fcn_00472250(dlg, 0, io_AppendText(0x10d, 0x1f40));
		}
	} else if (a2 >= (int) (unsigned char) info[0x242]) {
		io_AppendText(0x111);
	} else {
		x_dlg = fcn_00472250(dlg, 0, io_AppendText(0x10e, 0x1f40));
	}
	io_AppendText(0x10f, 1);
	do {
		if (g_100f1dc != -1) {
			if (g_67d370 == x_dlg) {
				handled = 1;
				g_774654 = 1;
			} else if (g_67d370 == y_dlg) {
				handled = 2;
				g_774654 = 1;
			} else if (g_100f1dc == 1) {
				g_774654 = 1;
			}
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		r = fcn_005373e0(fcn_005bdfc0, 0x677c7);
	} while (r != 0);
	fcn_00471e30(dlg);
	return handled;
}