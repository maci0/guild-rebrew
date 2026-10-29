

int __cdecl vfs_ReadData(char* buf, int size, int count, char* stream);

int __cdecl fcn_0044e0d0(void* a1)
{
	return vfs_ReadData((char*) &a1, 4, 1, a1);
}
