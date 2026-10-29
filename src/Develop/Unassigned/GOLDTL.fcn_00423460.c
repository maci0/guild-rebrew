extern int g_6b7d7c;



int __cdecl fcn_0042aaa0(int);

int __cdecl fcn_00423460(int* a1)
{
	int r;

	r = 0;
	if (g_6b7d7c == 0) {
		return 1;
	}
	if (a1 != 0 && *a1 != 0 && fcn_0042aaa0(*a1) == 4) {
		r = -1;
	}
	return r;
}
