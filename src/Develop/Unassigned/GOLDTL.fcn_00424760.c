

int __cdecl fcn_0064d530(int, int, int);

int* __cdecl fcn_00424760(int dst, int size)
{
	int* p;
	int* n;
	int* result;

	result = 0;
	p = *(int**) 0x6b7d68;
	if (p != 0) {
		n = (int*) p[0x38 / 4];
		if (n != 0) {
			fcn_0064d530(dst, (int) n, size);
			result = n;
		}
	}
	return result;
}
