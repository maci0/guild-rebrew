int __cdecl vfs_ReadDword(int, int);

/* ADDRESS: GOLDTL 0x0044dc90 */
int __cdecl d3_ReadMatVOffset(int a1, int* p)
{
	return vfs_ReadDword(a1, p[2] * 224 + p[4] + 0xd8);
}
