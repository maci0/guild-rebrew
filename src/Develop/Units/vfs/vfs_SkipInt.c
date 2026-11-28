
// fcn_0044f7c0 — fcn_004011d0(arg, &x) with x=0.

int __cdecl vfs_ReadDword(void* stream, void* dst);

void __cdecl vfs_SkipInt(void* a)
{
	int x;
	x = 0;
	vfs_ReadDword(a, &x);
}
