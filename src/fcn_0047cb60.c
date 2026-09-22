// FUNCTION: GOLD 0x0047cb60
// SIZE: 32
// fcn_0047cb60 — if(!a) return 0; return a + *(int*)(a + 0x45 + (b&0xffff)*4).

int __cdecl fcn_0047cb60(char* a, int b)
{
	if (a == 0) {
		return 0;
	}
	return (int) (a + *(int*) (a + 0x45 + (b & 0xffff) * 4));
}
