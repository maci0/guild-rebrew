

extern struct VFS_DIR* g_6b7fdc;
extern char g_6750e8[];

void* __cdecl vfs_Tfopen(const char* name, const char* mode, struct VFS_DIR* root);
int __cdecl vfs_ReadData(char* buf, int size, int count, char* stream);
int __cdecl fcn_0044d770(void*);
int __cdecl fcn_004011f0(void* stream, void* dst);
int __cdecl fcn_00430a80(void*, int, int);
#include "Develop/Units/vfs/vfs.h"

void* __cdecl fcn_0044f190(char* name)
{
	int magic;
	int id;
	int size;
	int t;
	void* h;

	h = vfs_Tfopen(name, g_6750e8, g_6b7fdc);
	if (h == 0) {
		return 0;
	}
	vfs_ReadData((char*) &magic, 4, 1, h);
	for (;;) {
		t = fcn_0044d770(h);
		if (t == 0x2d) {
			fcn_004011f0(h, &size);
			fcn_004011f0(h, &id);
			if (id == 0xfab50005) {
				return h;
			}
			fcn_00430a80(h, size - 4, 1);
		} else {
			if (t == 0x2b) {
				CloseVfsStream(h);
				return 0;
			}
			fcn_004011f0(h, &size);
			fcn_00430a80(h, size, 1);
		}
	}
}
