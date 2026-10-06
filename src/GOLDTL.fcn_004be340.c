// FUNCTION: GOLD 0x4bdaa0
// FUNCTION: GOLDTL 0x4be340

int __cdecl fcn_004be340(char* p)
{
	int n;

	n = 0;
	while (p != 0) {
		p = *(char**) (p + 0x3c);
		n++;
	}
	return n;
}
