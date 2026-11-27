

void __cdecl vfs_WriteByte(void*, int);
void __cdecl fcn_00446540(void*, void*);

char __cdecl d3_WriteSceneObjectCallback(void* node, void* stream)
{
	int saved;

	vfs_WriteByte(stream, 1);
	saved = *(int*) ((char*) node + 0x1f4);
	*(int*) ((char*) node + 0x1f4) = 0;
	fcn_00446540(stream, node);
	*(int*) ((char*) node + 0x1f4) = saved;
	return 1;
}
