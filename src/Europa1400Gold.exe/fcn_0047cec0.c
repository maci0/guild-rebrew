// FUNCTION: GOLD 0x0047cec0
// SIZE: 41
// fcn_0047cec0 — store 3 globals (masked).

void __cdecl fcn_0047cec0(int u1, int u2, int u3, int c, int d, char e)
{
	(void) u1; (void) u2; (void) u3;
	*(int*) 0xf8a63c = d & 0xffff;
	*(int*) 0xf8a634 = c & 0xffff;
	*(char*) 0xf8a648 = e;
}
