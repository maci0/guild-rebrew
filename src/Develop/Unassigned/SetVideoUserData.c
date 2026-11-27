

char* __cdecl FindVideoById(int);

int __cdecl SetVideoUserData(int id, int data)
{
	char* node;

	node = FindVideoById(id);
	if (node != 0) {
		*(int*) (node + 0x118) = data;
		return 1;
	}
	return 0;
}
