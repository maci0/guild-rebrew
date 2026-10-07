// FUNCTION: GOLD 0x0046c250
// fcn_0046c250 — set word at base + a*0x2ec + 0x14; call fcn_0046c1c0(a). (b=param4)

int __cdecl fcn_0046c1c0(int);

void __cdecl fcn_0046c250(int a, int u1, int u2, short b)
{
	(void) u1; (void) u2;
	*(short*) (*(char**) 0xf8f080 + a * 0x2ec + 0x14) = b;
	fcn_0046c1c0(a);
}
