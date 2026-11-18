

int __cdecl fcn_0042b200(int);
typedef void (__stdcall* fcn_0042ad60_f)(int);

int __cdecl fcn_0042ad60(int a1)
{
	int result = 0;

	if (*(int*) 0x6b7f90 != 0) {
		if (fcn_0042b200(a1) >= 0) {
			(*(fcn_0042ad60_f*) 0x66240c)(a1);
		} else {
			result = -1;
		}
	} else {
		result = -1;
	}
	return result;
}
