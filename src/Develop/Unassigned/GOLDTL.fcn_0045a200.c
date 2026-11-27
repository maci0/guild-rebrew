

char __cdecl d3_CalculateObjectMemorySize(int, int, int*);

char __cdecl d3_AccumulateObjectMemorySize(int object, int* state)
{
	int v;

	if (d3_CalculateObjectMemorySize(object, state[1], &v)) {
		*state += v;
	}
	return 1;
}
