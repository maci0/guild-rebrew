// FUNCTION: GOLDTL 0x423a10

char* __cdecl fcn_00423ac0(int);

char* __cdecl fcn_00423a10(int a1)
{
	char* p;
	char* q;

	q = 0;
	p = fcn_00423ac0(a1);
	if (p != 0) {
		q = *(char**) (p + 0x38);
		if (q != 0) {
			while (*(char**) (q + 0x104) != 0) {
				q = *(char**) (q + 0x104);
			}
		}
	}
	return q;
}
