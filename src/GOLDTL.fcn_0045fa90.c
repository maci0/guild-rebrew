int __cdecl fcn_0045f240(char* s);

// FUNCTION: GOLD 0x463670
// FUNCTION: GOLDTL 0x45fa90
unsigned long __cdecl fcn_0045fa90(char* s)
{
	unsigned long x = (unsigned long) fcn_0045f240(s);
	int c;

	x += ((unsigned long) fcn_0045f240(s)) << 8;
	x += ((unsigned long) fcn_0045f240(s)) << 16;
	c = fcn_0045f240(s);
	if (c == -1) {
		*(int*) (s + 0x38) = -3;
	}
	x += ((unsigned long) c) << 24;
	return x;
}
