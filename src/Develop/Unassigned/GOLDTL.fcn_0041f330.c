

char* __cdecl FindVideoById(int);

int __cdecl fcn_0041f330(int a1)
{
	char* p;

	p = FindVideoById(a1);
	if (p != 0) {
		return *(int*) (p + 0x114);
	}
	return 0;
}
