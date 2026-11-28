extern char g_1041d08[];
extern char vfs_RootDir[];


int __cdecl vfs_FindPathNode(int, int);

/* ADDRESS: GOLDDE 0x00440180 */
void __cdecl d3_SetObjectBasePath(int path)
{
	*(int*) &g_1041d08 = vfs_FindPathNode(path, *(int*) &vfs_RootDir);
}
