

int __cdecl vfs_ReadData(char* buf, int size, int count, char* stream);

int __cdecl fcn_0044e0d0(void* stream)
{
	return vfs_ReadData((char*) &stream, 4, 1, stream);
}
