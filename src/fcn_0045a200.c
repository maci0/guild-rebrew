// FUNCTION: GOLDTL 0x45a200
// SIZE: 45

char __cdecl fcn_00459ea0(int, int, int*);

char __cdecl fcn_0045a200(int a1, int* a2)
{
	int v;

	if (fcn_00459ea0(a1, a2[1], &v)) {
		*a2 += v;
	}
	return 1;
}
