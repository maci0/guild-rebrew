// FUNCTION: GOLDTL 0x424700

char* __cdecl fcn_00423ac0(char*);

int __cdecl fcn_00424700(char* name)
{
	int n;
	char* p;
	char* q;

	n = 0;
	if (name != 0) {
		p = fcn_00423ac0(name);
		if (p != 0) {
			for (q = *(char**) (p + 0x38); q != 0; q = *(char**) (q + 0x104)) {
				n++;
			}
		}
	} else {
		for (q = *(char**) (*(char**) 0x6b7d68 + 0x3c); q != 0; q = *(char**) (q + 0x3c)) {
			n += fcn_00424700(q);
		}
	}
	return n;
}
