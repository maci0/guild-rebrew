// FUNCTION: GOLD 0x004c0210
// fcn_004c0210 — walk 0xc chain to last node.

int __cdecl fcn_004c0210(void)
{
	char* p;
	p = *(char**) 0x6f0b84;
	if (p == 0) {
		return 0;
	}
	while (*(char**) (p + 0xc) != 0) {
		p = *(char**) (p + 0xc);
	}
	return (int) p;
}
