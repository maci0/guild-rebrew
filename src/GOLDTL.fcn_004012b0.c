

// Client twin of GOLD's fcn_004012b0 (0x4012b0, 45 B): the client calls
// fcn_004011d0 four times over four consecutive 4-byte fields instead of
// fcn_00401320 over a three-element array.

void __cdecl fcn_004011d0(int, char*);

void __cdecl fcn_004012b0(int a1, char* a2)
{
	fcn_004011d0(a1, a2);
	fcn_004011d0(a1, a2 + 4);
	fcn_004011d0(a1, a2 + 8);
	fcn_004011d0(a1, a2 + 0xc);
}
