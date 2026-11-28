extern int vfs_RootDir;
void* __cdecl vfs_Tfopen(const char*, const char*, void*);
int __cdecl vfs_ReadData(char* buf, int size, int count, char* stream);
long __cdecl fcn_00430c50(char* a);
int __cdecl vfs_ReadStreamToken(void* h);
int __cdecl fcn_004011f0(void* a, void* x);
int __cdecl vfs_fseek(char* s, int off, int whence);
void __cdecl CloseVfsStream(void* f);

/* ADDRESS: GOLDTL 0x0044f010 */
int __cdecl vfs_SeekFastChunkOffset(char* a1)
{
	char* stream;
	int local[2];
	int result;
	int marker;

	stream = vfs_Tfopen(a1, (char*) 0x6750e8, *(void**) &vfs_RootDir);
	if (stream == 0)
		return -1;
	vfs_ReadData((char*) &local[1], 4, 1, stream);
	for (;;) {
		result = fcn_00430c50(stream);
		marker = vfs_ReadStreamToken(stream);
		if (marker == 0x2d) {
			fcn_004011f0(stream, &a1);
			fcn_004011f0(stream, &local[0]);
			if (local[0] == 0xfab50005) {
				CloseVfsStream(stream);
				return result;
			}
			vfs_fseek(stream, a1 - 4, 1);
		} else if (marker == 0x2b) {
			CloseVfsStream(stream);
			return -1;
		} else {
			fcn_004011f0(stream, &a1);
			vfs_fseek(stream, a1, 1);
		}
	}
}
