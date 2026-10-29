


int __cdecl vfs_ReadData(char* buf, int size, int count, char* stream);

int __cdecl fcn_00430870(void* a1)
{
	char c;

	if (vfs_ReadData(&c, 1, 1, a1) == 1) {
		return c;
	}
	return -1;
}
