

void __cdecl fcn_00401360(int, int);
void __cdecl vfs_fwrite(int, int, int, int);

void __cdecl fcn_00401380(int stream, int size, int buf)
{
	fcn_00401360(stream, size);
	vfs_fwrite(buf, size, 1, stream);
}
