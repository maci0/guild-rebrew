

int __cdecl vfs_fwrite(int*, int, int, int);

/* ADDRESS: GOLDDE 0x004011f0 */
void __cdecl vfs_WriteByte(int a, int b)
{
	vfs_fwrite(&b, 1, 1, a);
}
