int __cdecl vfs_ReadDword(void*, void*);

/* ADDRESS: GOLDTL 0x0044dc00 */
int __cdecl d3_ReadMatUTile(int a, int* b)
{
	return vfs_ReadDword((void*) a, (void*) (b[2] * 224 + b[4] + 0xcc));
}
