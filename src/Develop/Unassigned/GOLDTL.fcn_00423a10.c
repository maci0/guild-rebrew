

char* __cdecl sbs_FindSet(int);

char* __cdecl fcn_00423a10(int a1)
{
	char* p;
	char* q;

	q = 0;
	p = sbs_FindSet(a1);
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
