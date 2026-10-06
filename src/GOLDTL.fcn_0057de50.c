// FUNCTION: GOLDTL 0x0057de50

extern int g_7749f4;

void __cdecl fcn_0057de50(int mask, int on)
{
	if (on) {
		g_7749f4 |= mask;
	} else {
		g_7749f4 &= ~mask;
	}
}
