// FUNCTION: GOLD 0x0052e360
// fcn_0052e360 — copy string a mirrored into 0x761f40-a; 2 global stores.

void __cdecl fcn_0052e360(char* a)
{
	char* p;
	char* q;
	p = a;
	q = (char*) (0x761f40 - (int) a);
	do {
		*q++ = *p;
	} while (*p++ != 0);
	*(int*) 0x6237cc = *(int*) 0x6333cc;
}
