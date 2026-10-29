

extern int g_6b5c94;
extern short g_14ce8c0;
extern int g_14cf900[];

void __cdecl fcn_00412830(unsigned char mask)
{
	if (g_6b5c94 != 0) {
		if (mask & 0x1) {
			((int*)&g_14ce8c0)[11] = 0;
			g_14cf900[11] = 0;
		}
		if (mask & 0x2) {
			((int*)&g_14ce8c0)[8] = 0;
			g_14cf900[8] = 0;
		}
		if (mask & 0x4) {
			((int*)&g_14ce8c0)[9] = 0;
			g_14cf900[9] = 0;
		}
		if (mask & 0x8) {
			((int*)&g_14ce8c0)[6] = 0;
			g_14cf900[6] = 0;
		}
		if (mask & 0x10) {
			((int*)&g_14ce8c0)[3] = 0;
			g_14cf900[3] = 0;
		}
		if (mask & 0x20) {
			((int*)&g_14ce8c0)[4] = 0;
			g_14cf900[4] = 0;
		}
	} else {
		if (mask & 0x1) {
			((int*)&g_14ce8c0)[6] = 0;
			g_14cf900[6] = 0;
		}
		if (mask & 0x2) {
			((int*)&g_14ce8c0)[3] = 0;
			g_14cf900[3] = 0;
		}
		if (mask & 0x4) {
			((int*)&g_14ce8c0)[4] = 0;
			g_14cf900[4] = 0;
		}
		if (mask & 0x8) {
			((int*)&g_14ce8c0)[11] = 0;
			g_14cf900[11] = 0;
		}
		if (mask & 0x10) {
			((int*)&g_14ce8c0)[8] = 0;
			g_14cf900[8] = 0;
		}
		if (mask & 0x20) {
			((int*)&g_14ce8c0)[9] = 0;
			g_14cf900[9] = 0;
		}
	}
}
unsigned char _dpad_14cf736[458];
