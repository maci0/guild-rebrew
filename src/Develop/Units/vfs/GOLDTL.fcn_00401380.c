

void __cdecl vfs_WriteInt(int, int);
void __cdecl vfs_fwrite(int, int, int, int);

void __cdecl bio_wr_buffer(int stream, int size, int buf)
{
	vfs_WriteInt(stream, size);
	vfs_fwrite(buf, size, 1, stream);
}
