extern short g_7725c4;
extern int g_772570;
extern int g_772574;

// FUNCTION: GOLDTL 0x526b70
// SIZE: 117

void __cdecl fcn_00526b70(void)
{
	int a;
	int b;

	a = 0;
	b = 0;
	if (g_7725c4 == 1) {
		b = -0x30;
	} else if (g_7725c4 == 3) {
		a = -0x28;
	} else if (g_7725c4 == 6) {
		a = -0x28;
	} else if (g_7725c4 == 8) {
		a = -0x28;
		b = -0x30;
	} else if (g_7725c4 == 7) {
		b = -0x30;
	}
	g_772570 = a;
	g_772574 = b;
}
