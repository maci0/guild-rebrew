// FUNCTION: GOLD 0x0040eea0
// fcn_0040eea0 — fcn_00433b10([0xfc2dec]); zero [0x6310e8] [0x6310e4].

void __cdecl fcn_00433b10(int);

void __cdecl fcn_0040eea0(void)
{
	fcn_00433b10(*(int*) 0xfc2dec);
	*(int*) 0x6310e8 = 0;
	*(int*) 0x6310e4 = 0;
}
