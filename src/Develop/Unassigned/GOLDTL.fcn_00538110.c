

typedef int (__stdcall* fcn_00538110_a)(int);
typedef void (__stdcall* fcn_00538110_b)(int, int);

int __stdcall fcn_00538110(int a1, int a2)
{
	if (a1 != *(int*) 0x774940) {
		if ((*(fcn_00538110_a*) 0x662284)(a1) != 0) {
			(*(fcn_00538110_b*) 0x6622f0)(a1, a2);
		}
	}
	return 1;
}
