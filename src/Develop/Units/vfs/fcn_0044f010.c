extern int g_6b7fdc;
void* __cdecl vfs_Tfopen(const char*, const char*, void*);
int __cdecl vfs_ReadData(char* buf, int size, int count, char* stream);
long __cdecl fcn_00430c50(char* a);
int __cdecl fcn_0044d770(void* h);
int __cdecl fcn_004011f0(void* a, void* x);
int __cdecl fcn_00430a80(char* s, int off, int whence);
void __cdecl CloseVfsStream(void* f);

/* ADDRESS: GOLDTL 0x0044f010 */
int __cdecl fcn_0044f010(char* a1)
{
	char* p;
	int local[2];
	int result;
	int c;

	p = vfs_Tfopen(a1, (char*) 0x6750e8, *(void**) &g_6b7fdc);
	if (p == 0)
		return -1;
	vfs_ReadData((char*) &local[1], 4, 1, p);
	for (;;) {
		result = fcn_00430c50(p);
		c = fcn_0044d770(p);
		if (c == 0x2d) {
			fcn_004011f0(p, &a1);
			fcn_004011f0(p, &local[0]);
			if (local[0] == 0xfab50005) {
				CloseVfsStream(p);
				return result;
			}
			fcn_00430a80(p, a1 - 4, 1);
		} else if (c == 0x2b) {
			CloseVfsStream(p);
			return -1;
		} else {
			fcn_004011f0(p, &a1);
			fcn_00430a80(p, a1, 1);
		}
	}
}
