

extern int g_7749f4;

void __cdecl io_SetMessageFilterMask(int mask, int on)
{
	if (on) {
		g_7749f4 |= mask;
	} else {
		g_7749f4 &= ~mask;
	}
}
