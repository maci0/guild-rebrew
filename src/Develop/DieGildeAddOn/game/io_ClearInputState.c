

extern short io_ActiveCursorX;
extern int io_PolledCursorState[];
extern int io_ActiveInputState[];

/* ADDRESS: GOLDDE 0x00410330 */
void __cdecl io_ClearInputState(void)
{
	((int*)&io_ActiveCursorX)[6] = 0;
	io_PolledCursorState[6] = 0;
	io_ActiveInputState[6] = 0;
	((int*)&io_ActiveCursorX)[4] = 0;
	io_PolledCursorState[4] = 0;
	io_ActiveInputState[4] = 0;
	((int*)&io_ActiveCursorX)[5] = 0;
	io_PolledCursorState[5] = 0;
	io_ActiveInputState[5] = 0;
	((int*)&io_ActiveCursorX)[11] = 0;
	io_PolledCursorState[11] = 0;
	io_ActiveInputState[11] = 0;
	((int*)&io_ActiveCursorX)[8] = 0;
	io_PolledCursorState[8] = 0;
	io_ActiveInputState[8] = 0;
	((int*)&io_ActiveCursorX)[9] = 0;
	io_PolledCursorState[9] = 0;
	io_ActiveInputState[9] = 0;
	((int*)&io_ActiveCursorX)[10] = 0;
	io_PolledCursorState[10] = 0;
	io_ActiveInputState[10] = 0;
}
unsigned char _dpad_14ce8c2[30];
