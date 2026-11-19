int __cdecl vfs_ReadData(char* buf, int size, int count, char* stream);

/* ADDRESS: GOLDTL 0x00401180 */
int __cdecl vfs_ReadByte(void* a, void* b)
{
	return vfs_ReadData((char*) b, 1, 1, (char*) a);
}
