

extern int g_6b5c94;
extern short io_ActiveCursorX;
extern int io_PolledCursorState[];

/* ADDRESS: GOLDDE 0x004112d0 */
void __cdecl io_ClearInputButtonFlags(unsigned char mask)
{
	if (g_6b5c94 != 0) {
		if (mask & 0x1) {
			((int*)&io_ActiveCursorX)[11] = 0;
			io_PolledCursorState[11] = 0;
		}
		if (mask & 0x2) {
			((int*)&io_ActiveCursorX)[8] = 0;
			io_PolledCursorState[8] = 0;
		}
		if (mask & 0x4) {
			((int*)&io_ActiveCursorX)[9] = 0;
			io_PolledCursorState[9] = 0;
		}
		if (mask & 0x8) {
			((int*)&io_ActiveCursorX)[6] = 0;
			io_PolledCursorState[6] = 0;
		}
		if (mask & 0x10) {
			((int*)&io_ActiveCursorX)[3] = 0;
			io_PolledCursorState[3] = 0;
		}
		if (mask & 0x20) {
			((int*)&io_ActiveCursorX)[4] = 0;
			io_PolledCursorState[4] = 0;
		}
	} else {
		if (mask & 0x1) {
			((int*)&io_ActiveCursorX)[6] = 0;
			io_PolledCursorState[6] = 0;
		}
		if (mask & 0x2) {
			((int*)&io_ActiveCursorX)[3] = 0;
			io_PolledCursorState[3] = 0;
		}
		if (mask & 0x4) {
			((int*)&io_ActiveCursorX)[4] = 0;
			io_PolledCursorState[4] = 0;
		}
		if (mask & 0x8) {
			((int*)&io_ActiveCursorX)[11] = 0;
			io_PolledCursorState[11] = 0;
		}
		if (mask & 0x10) {
			((int*)&io_ActiveCursorX)[8] = 0;
			io_PolledCursorState[8] = 0;
		}
		if (mask & 0x20) {
			((int*)&io_ActiveCursorX)[9] = 0;
			io_PolledCursorState[9] = 0;
		}
	}
}
unsigned char _dpad_14cf736[458];
