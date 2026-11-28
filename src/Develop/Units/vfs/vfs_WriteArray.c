


void __cdecl vfs_WriteInt(int, int);
int __cdecl vfs_fwrite(int, int, int, int);

/* ADDRESS: GOLDDE 0x00401340 */
int __cdecl vfs_WriteArray(int stream, int size, int count, int buffer)
{
	vfs_WriteInt(stream, count);
	vfs_WriteInt(stream, size);
	return vfs_fwrite(buffer, size, count, stream);
}
