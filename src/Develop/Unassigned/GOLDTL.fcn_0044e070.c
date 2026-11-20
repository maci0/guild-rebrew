

char* __cdecl vfs_ReadCString(void* stream, char* text);

void __cdecl vfs_SkipCString(void* inputStream)
{
	char buf[0x100];

	vfs_ReadCString(inputStream, buf);
}
