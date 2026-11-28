

extern struct VFS_DIR* vfs_RootDir;
#include "Develop/DieGildeAddOn/game/game_data.h"

void* __cdecl vfs_Tfopen(const char* name, const char* mode, struct VFS_DIR* root);
int __cdecl vfs_ReadData(char* buf, int size, int count, char* stream);
int __cdecl vfs_ReadByte(void* stream, void* dst);
int __cdecl fcn_004011f0(void* stream, void* dst);
#include "Develop/Units/vfs/vfs.h"

char __cdecl d3_CheckVfsHeaderFlag(char* name)
{
	int v;
	int magic;
	char c;
	char ok;
	void* h;

	ok = 1;
	h = vfs_Tfopen(name, g_6750e8, vfs_RootDir);
	if (h != 0) {
		vfs_ReadData((char*) &magic, 4, 1, h);
		vfs_ReadByte(h, &c);
		fcn_004011f0(h, &v);
		vfs_ReadByte(h, &c);
		fcn_004011f0(h, &v);
		vfs_ReadByte(h, &c);
		if (c == 2) {
			vfs_ReadByte(h, &c);
			if ((c & 2) == 2) {
				ok = 0;
			}
		}
		CloseVfsStream(h);
	}
	return ok;
}
