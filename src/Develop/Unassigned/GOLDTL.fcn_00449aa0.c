

int __cdecl vfs_FindPathNode(int, int);

void __cdecl d3_SetObjectBasePath(int path)
{
	*(int*) 0x1041d08 = vfs_FindPathNode(path, *(int*) 0x6b7fdc);
}
