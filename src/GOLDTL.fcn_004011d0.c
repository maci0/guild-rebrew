int __cdecl vfs_ReadData(char* buf, int size, int count, char* stream);

/* ADDRESS: GOLDTL 0x004011d0 */
int __cdecl fcn_004011d0(void* a, void* b)
{
	return vfs_ReadData((char*) b, 4, 1, (char*) a);
}
