

char __cdecl d3_CalculateObjectMemorySize(int, int, int*);

char __cdecl fcn_0045a200(int a1, int* a2)
{
	int v;

	if (d3_CalculateObjectMemorySize(a1, a2[1], &v)) {
		*a2 += v;
	}
	return 1;
}
