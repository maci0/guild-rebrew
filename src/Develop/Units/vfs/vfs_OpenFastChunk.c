

extern struct VFS_DIR* vfs_RootDir;
#include "Develop/DieGildeAddOn/game/game_data.h"

void* __cdecl vfs_Tfopen(const char* name, const char* mode, struct VFS_DIR* root);
int __cdecl vfs_ReadData(char* buf, int size, int count, char* stream);
int __cdecl vfs_ReadStreamToken(void*);
int __cdecl fcn_004011f0(void* stream, void* dst);
int __cdecl vfs_fseek(void*, int, int);
#include "Develop/Units/vfs/vfs.h"

/* ADDRESS: GOLDDE 0x00444db0 */
void* __cdecl vfs_OpenFastChunk(char* name)
{
	int magic;
	int id;
	int size;
	int t;
	void* h;

	h = vfs_Tfopen(name, g_6750e8, vfs_RootDir);
	if (h == 0) {
		return 0;
	}
	vfs_ReadData((char*) &magic, 4, 1, h);
	for (;;) {
		t = vfs_ReadStreamToken(h);
		if (t == 0x2d) {
			fcn_004011f0(h, &size);
			fcn_004011f0(h, &id);
			if (id == 0xfab50005) {
				return h;
			}
			vfs_fseek(h, size - 4, 1);
		} else {
			if (t == 0x2b) {
				CloseVfsStream(h);
				return 0;
			}
			fcn_004011f0(h, &size);
			vfs_fseek(h, size, 1);
		}
	}
}
