


// fcn_004ac150 — do { r=fcn_0042ec00(0x33); } while ((r & 0xffff) == si).

int __cdecl gm_RandomMod(int);

void __cdecl fcn_004ac150(unsigned short si)
{
	int r;
	do {
		r = gm_RandomMod(0x33) & 0xffff;
	} while ((unsigned short) r == si);
}

