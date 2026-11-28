

int __cdecl vfs_ReadDword(void* stream, void* dst);

/* ADDRESS: GOLDDE 0x00401240 */
void __cdecl vfs_ReadVec3(void* stream, void* dst)
{
	vfs_ReadDword(stream, dst);
	vfs_ReadDword(stream, (char*) dst + 4);
	vfs_ReadDword(stream, (char*) dst + 8);
}
