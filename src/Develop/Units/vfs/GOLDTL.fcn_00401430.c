


void __cdecl fcn_00401360(int, int);
int __cdecl vfs_fwrite(int, int, int, int);

int __cdecl vfs_WriteArray(int stream, int size, int count, int buffer)
{
	fcn_00401360(stream, count);
	fcn_00401360(stream, size);
	return vfs_fwrite(buffer, size, count, stream);
}
