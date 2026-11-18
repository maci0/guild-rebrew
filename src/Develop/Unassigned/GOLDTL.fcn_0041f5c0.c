

char* __cdecl FindVideoById(int);

int __cdecl fcn_0041f5c0(int id, int a2)
{
	char* node;

	node = FindVideoById(id);
	if (node != 0) {
		*(int*) (node + 0x118) = a2;
		return 1;
	}
	return 0;
}
