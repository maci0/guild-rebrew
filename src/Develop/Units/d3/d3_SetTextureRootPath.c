extern char g_10405cc[];
extern char vfs_RootDir[];


int __cdecl vfs_FindPathNode(int, int);

/* ADDRESS: GOLDDE 0x00451010 */
void __cdecl d3_SetTextureRootPath(int path)
{
	*(int*) &g_10405cc = vfs_FindPathNode(path, *(int*) &vfs_RootDir);
}
