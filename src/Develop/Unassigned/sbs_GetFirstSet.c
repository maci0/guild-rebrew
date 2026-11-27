

int __cdecl fcn_0064d530(int, int, int);

int* __cdecl sbs_GetFirstSet(int nameBuf, int bufSize)
{
	int* p;
	int* n;
	int* result;

	result = 0;
	p = *(int**) 0x6b7d68;
	if (p != 0) {
		n = (int*) p[0x3c / 4];
		if (n != 0) {
			fcn_0064d530(nameBuf, (int) n, bufSize);
			result = n;
		}
	}
	return result;
}
