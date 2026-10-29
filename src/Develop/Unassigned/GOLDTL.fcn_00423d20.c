

int* __cdecl fcn_00423c50(int, int);

int __cdecl fcn_00423d20(int a1, int a2)
{
	int r;
	int* p;

	r = 0;
	p = (int*) fcn_00423c50(a1, a2);
	if (p != 0) {
		r = p[0x100 / 4];
	}
	return r;
}
