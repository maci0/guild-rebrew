

extern struct VFS_DIR* g_6b7fdc;
extern char g_6750e8[];

void* __cdecl vfs_Tfopen(const char* name, const char* mode, struct VFS_DIR* root);
int __cdecl vfs_ReadData(char* buf, int size, int count, char* stream);
int __cdecl fcn_00401180(void* stream, void* dst);
int __cdecl fcn_004011f0(void* stream, void* dst);
#include "Develop/Units/vfs/vfs.h"

char __cdecl fcn_0044f0e0(char* name)
{
	int v;
	int magic;
	char c;
	char ok;
	void* h;

	ok = 1;
	h = vfs_Tfopen(name, g_6750e8, g_6b7fdc);
	if (h != 0) {
		vfs_ReadData((char*) &magic, 4, 1, h);
		fcn_00401180(h, &c);
		fcn_004011f0(h, &v);
		fcn_00401180(h, &c);
		fcn_004011f0(h, &v);
		fcn_00401180(h, &c);
		if (c == 2) {
			fcn_00401180(h, &c);
			if ((c & 2) == 2) {
				ok = 0;
			}
		}
		CloseVfsStream(h);
	}
	return ok;
}
