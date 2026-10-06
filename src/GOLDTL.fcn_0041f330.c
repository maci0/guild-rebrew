// FUNCTION: GOLDTL 0x41f330

char* __cdecl fcn_0041f9b0(int);

int __cdecl fcn_0041f330(int a1)
{
	char* p;

	p = fcn_0041f9b0(a1);
	if (p != 0) {
		return *(int*) (p + 0x114);
	}
	return 0;
}
