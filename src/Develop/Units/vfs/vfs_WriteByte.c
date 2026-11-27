

int __cdecl vfs_fwrite(int*, int, int, int);

void __cdecl vfs_WriteByte(int a, int b)
{
	vfs_fwrite(&b, 1, 1, a);
}
