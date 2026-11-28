

int __cdecl vfs_fwrite(int*, int, int, int);

/* ADDRESS: GOLDDE 0x00401320 */
void __cdecl vfs_WriteInt(int a, int b)
{
	vfs_fwrite(&b, 4, 1, a);
}
