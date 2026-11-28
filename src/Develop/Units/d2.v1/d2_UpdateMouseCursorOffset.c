extern short d2_CursorStateId;
extern int g_772570;
extern int g_772574;


/* ADDRESS: GOLDTL 0x00526b70 */
void __cdecl d2_UpdateMouseCursorOffset(void)
{
	int a;
	int b;

	a = 0;
	b = 0;
	if (d2_CursorStateId == 1) {
		b = -0x30;
	} else if (d2_CursorStateId == 3) {
		a = -0x28;
	} else if (d2_CursorStateId == 6) {
		a = -0x28;
	} else if (d2_CursorStateId == 8) {
		a = -0x28;
		b = -0x30;
	} else if (d2_CursorStateId == 7) {
		b = -0x30;
	}
	g_772570 = a;
	g_772574 = b;
}
