// FUNCTION: GOLDTL 0x424760

int __cdecl fcn_0064d530(int, int, int);

int* __cdecl fcn_00424760(int a1, int a2)
{
	int* p;
	int* n;
	int* result;

	result = 0;
	p = *(int**) 0x6b7d68;
	if (p != 0) {
		n = (int*) p[0x38 / 4];
		if (n != 0) {
			fcn_0064d530(a1, (int) n, a2);
			result = n;
		}
	}
	return result;
}
