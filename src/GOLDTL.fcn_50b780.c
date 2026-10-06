// FUNCTION: GOLDTL 0x50b780

// fcn_00508620 — (param1) * table[param2].

int __cdecl fcn_00508620(int a, int b)
{
	return a * *(int*) ((char*) 0x6995bc + b * 4);
}
