// FUNCTION: GOLDTL 0x41f5c0
// SIZE: 36

int* __cdecl fcn_0041f9b0(int);

int __cdecl fcn_0041f5c0(int a1, int a2)
{
	int* node;

	node = fcn_0041f9b0(a1);
	if (node != 0) {
		*(int*) ((char*) node + 0x118) = a2;
		return 1;
	}
	return 0;
}
