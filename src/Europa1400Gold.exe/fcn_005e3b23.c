// FUNCTION: GOLD 0x005e3b23
// SIZE: 45
// fcn_005e3b23 — set 2 bytes from PE header of module.

void* __stdcall f_5eb120(int);

void __cdecl fcn_005e3b23(char* out)
{
	void* base;
	char* pe;
	*(int*) out = 0;
	base = f_5eb120(0);
	if (*(unsigned short*) base != 0x5a4d) {
		return;
	}
	if (*(int*) ((char*) base + 0x3c) == 0) {
		return;
	}
	pe = (char*) base + *(int*) ((char*) base + 0x3c);
	out[0] = *(char*) (pe + 0x1a);
	out[1] = *(char*) (pe + 0x1b);
}
