// FUNCTION: GOLD 0x004bd9e0
// SIZE: 29
// FUNCTION: GOLDTL 0x4be280
// SIZE: 30

void __cdecl fcn_0041ddd0(void*);

void __cdecl fcn_004be280(char* p)
{
	char* q;

	while (p != 0) {
		q = p;
		p = *(char**) (p + 0x3c);
		fcn_0041ddd0(q);
	}
}
