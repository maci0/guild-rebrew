

int __cdecl vfs_fwrite(int*, int, int, int);

void __cdecl vfs_WriteInt(int a, int b)
{
	vfs_fwrite(&b, 4, 1, a);
}
