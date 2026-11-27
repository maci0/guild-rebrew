

int __cdecl vfs_FindPathNode(int, int);

void __cdecl d3_SetTextureRootPath(int path)
{
	*(int*) 0x10405cc = vfs_FindPathNode(path, *(int*) 0x6b7fdc);
}
