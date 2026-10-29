

char* __cdecl fcn_0041f9b0(int);

int __cdecl fcn_0041f5c0(int a1, int a2)
{
	char* node;

	node = fcn_0041f9b0(a1);
	if (node != 0) {
		*(int*) (node + 0x118) = a2;
		return 1;
	}
	return 0;
}
