

int __cdecl vfs_ReadData(char* buf, int size, int count, char* stream);

/* ADDRESS: GOLDDE 0x00443de0 */
int __cdecl vfs_SkipDword(void* stream)
{
	return vfs_ReadData((char*) &stream, 4, 1, stream);
}
