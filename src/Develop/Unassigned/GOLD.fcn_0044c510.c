
// fcn_0044c510 — *(void**)0xfba940 = fcn_0042f7e0(a, [0x6333fc]).

int __cdecl vfs_FindPathNode(int, int);

void __cdecl d3_SetAnimDir(int a)
{
	*(void**) 0xfba940 = (void*) vfs_FindPathNode(a, *(int*) 0x6333fc);
}
