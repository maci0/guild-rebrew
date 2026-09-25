int __cdecl fcn_00479330(char*);
int __cdecl fcn_00479110(char*);

// FUNCTION: GOLD 0x0047c3c0
// SIZE: 52
// FUNCTION: GOLDTL 0x479620
// SIZE: 52

int __cdecl fcn_00479620(char* p, int mode)
{
	if (p[0xc] == 2 && mode == 1)
		return fcn_00479330(p);
	if (p[0xc] == 0 && mode == 1)
		return fcn_00479110(p);
	return 0;
}
