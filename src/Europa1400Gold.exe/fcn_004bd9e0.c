// FUNCTION: GOLD 0x004bd9e0
// SIZE: 29
// fcn_004bd9e0 — walk 0x3c chain, fcn_00422620 each.

int __cdecl fcn_00422620(int);

void __cdecl fcn_004bd9e0(char* p)
{
	while (p != 0) {
		char* next;
		next = *(char**) (p + 0x3c);
		fcn_00422620((int) p);
		p = next;
	}
}
