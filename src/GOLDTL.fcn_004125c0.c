// FUNCTION: GOLDTL 0x4125c0
// SIZE: 66

extern short g_14cf900[2];
extern short g_14ce920[2];
extern short g_14ce8c0[2];
extern int g_6772c4;

void __cdecl fcn_004125c0(int x, int y)
{
	g_14cf900[0] = (short) x;
	g_14cf900[1] = (short) y;
	g_14ce920[0] = (short) x;
	g_14ce920[1] = (short) y;
	g_14ce8c0[0] = (short) x;
	g_14ce8c0[1] = (short) y;
	if (g_6772c4 == 0) {
		((void (__stdcall*)(int, int)) *(void**) 0x662300)(x, y);
	}
}
