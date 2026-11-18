

char* __cdecl FindVideoById(int);

int __cdecl fcn_0041f330(int id)
{
	char* p;

	p = FindVideoById(id);
	if (p != 0) {
		return *(int*) (p + 0x114);
	}
	return 0;
}
