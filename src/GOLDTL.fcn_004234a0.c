// FUNCTION: GOLDTL 0x4234a0
// SIZE: 52

char* __cdecl fcn_00422530(int, int);

int __cdecl fcn_004234a0(int a1, int a2)
{
	char* p;

	if (*(int*) 0x6b7d7c == 0) {
		return 1;
	}
	p = fcn_00422530(a1, a2);
	if (p != 0 && p[0x36] == 2) {
		return 1;
	}
	return 0;
}
