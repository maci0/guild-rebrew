


// fcn_004011d0 — fcn_00430bd0(b, 4, 1, a).

int __cdecl vfs_ReadData(void* buf, int size, int count, void* stream);

int __cdecl vfs_ReadDword(void* a, void* b)
{
	return vfs_ReadData(b, 4, 1, a);
}
