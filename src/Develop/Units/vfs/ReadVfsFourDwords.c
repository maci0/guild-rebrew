

/* Inferred name: four-dword reader shared by TL 0x4012b0 and Gold 0x401270. */

int __cdecl vfs_ReadDword(void* stream, void* dst);

void __cdecl ReadVfsFourDwords(void* stream, void* dst)
{
	vfs_ReadDword(stream, dst);
	vfs_ReadDword(stream, (char*) dst + 4);
	vfs_ReadDword(stream, (char*) dst + 8);
	vfs_ReadDword(stream, (char*) dst + 0xc);
}
