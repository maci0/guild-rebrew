int __cdecl vfs_ReadDword(int, void *);

/* ADDRESS: GOLDTL 0x0044dcc0 */
int __cdecl d3_ReadMatUvwRotate(int a1, int *a2)
{
	return vfs_ReadDword(a1, (void *) ((char *) a2[4] + a2[2] * 0xe0 + 0xdc));
}
