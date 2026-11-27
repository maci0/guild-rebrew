

void __cdecl vfs_WriteByte(void*, int);
void __cdecl d3_WriteSceneNodeTree(void*, void*);

char __cdecl d3_WriteSceneObjectCallback(void* node, void* stream)
{
	int saved;

	vfs_WriteByte(stream, 1);
	saved = *(int*) ((char*) node + 0x1f4);
	*(int*) ((char*) node + 0x1f4) = 0;
	d3_WriteSceneNodeTree(stream, node);
	*(int*) ((char*) node + 0x1f4) = saved;
	return 1;
}
