extern int g_14ce8a0;
extern int g_14ce89c;
extern int g_14ce8d0;
extern int g_14ce8d8;
extern int g_14ce920;
extern int g_14ce922;
extern int g_14ce8c0;
extern int g_14ce8c2;
extern int g_14cf900;
extern int g_14cf902;

int __stdcall ClientToScreen(int hwnd, int* pt);
int __stdcall SetCursorPos(int x, int y);
void __cdecl fcn_00411780(int err, char* text, int a3);

/* ADDRESS: GOLDTL 0x004123a0 */
void __cdecl fcn_004123a0(void)
{
	int state[4];
	int dev;
	int vtable;
	int err;
	int dx;
	int dy;
	int hwnd;
	int* pt;

	dev = g_14ce8a0;
	vtable = *(int*) dev;
	err = ((int (__stdcall*) (int, int, int*)) *(int*) (vtable + 0x24))
	    (dev, 0x10, state);
	if (err != 0) {
		switch (err) {
		case 0x8007001e:
			fcn_00411780(err, "Access to Input Device Lost", 0);
			break;
		case 0x80070057:
			fcn_00411780(err, "Invalid Param", 0);
			break;
		case 0x8007000c:
			fcn_00411780(err, "Device not aquired", 0);
			break;
		case 0x80070015:
			fcn_00411780(err, "Device not initialized", 0);
			break;
		case 0x8000000a:
			fcn_00411780(err, "Data not available", 0);
			break;
		default:
			break;
		}
	}
	if (((unsigned char*) state)[12] & 0x80)
		g_14ce8d0 = 1;
	if ((((unsigned char*) state)[12] & 0x80) == 0) {
		g_14ce8d8 = 0;
		g_14ce8d0 = 0;
	}
	dx = g_14ce920 + state[0];
	dy = (int) (*(short*) (state + 1) + *(short*) &g_14ce922);
	*(short*) &g_14ce8c0 = (short) dx;
	*(short*) &g_14cf900 = (short) dx;
	*(short*) &g_14ce8c2 = (short) dy;
	*(short*) &g_14cf902 = (short) dy;
	*(short*) &g_14ce920 = (short) dx;
	*(short*) &g_14ce922 = (short) dy;
	pt = state;
	pt[0] = dx;
	pt[1] = dy;
	hwnd = g_14ce89c;
	ClientToScreen(hwnd, pt);
	SetCursorPos(pt[0], pt[1]);
}
