// FUNCTION: GOLD 0x004ac150
// SIZE: 23
// fcn_004ac150 — do { r=fcn_0042ec00(0x33); } while ((r & 0xffff) == si).

int __cdecl fcn_0042ec00(int);

void __cdecl fcn_004ac150(unsigned short si)
{
	int r;
	do {
		r = fcn_0042ec00(0x33) & 0xffff;
	} while ((unsigned short) r == si);
}
