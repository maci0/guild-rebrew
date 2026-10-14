

typedef int (__stdcall* fcn_0042de60_a)(int);
typedef void (__stdcall* fcn_0042de60_b)(int);

void __cdecl fcn_0042de60(void)
{
	int r;

	if (*(int*) 0x6b7fa8 != 0) {
		r = (*(fcn_0042de60_a*) 0x66232c)(*(int*) 0x6b7fa8);
		if (r == 0) {
			*(int*) 0x6b7fa8 = r;
		}
	}
	(*(fcn_0042de60_b*) 0x662328)(*(int*) 0x1052c48 + 5);
}
