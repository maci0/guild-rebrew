// FUNCTION: GOLDTL 0x00573de0
// SIZE: 44

char __cdecl fcn_00573de0(int v, int* list)
{
	list[list[0x41] + 1] = v;
	return ++list[0x41] < 0x40;
}
