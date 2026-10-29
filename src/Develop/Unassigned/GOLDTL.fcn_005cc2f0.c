


void __cdecl fcn_00472640(int, int);

void __cdecl fcn_005cc2f0(int n, char* arr)
{
	int* p;

	if (n > 0) {
		p = (int*) (arr + 8);
		do {
			fcn_00472640(*p, 1);
			p = (int*) ((char*) p + 0x38);
		} while (--n);
	}
}
