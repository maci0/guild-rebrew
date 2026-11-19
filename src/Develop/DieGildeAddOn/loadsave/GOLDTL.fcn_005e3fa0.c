


#include "Develop/DieGildeAddOn/game/game_data.h"
typedef struct VFS_DIR VFS_DIR;
extern VFS_DIR* g_6b7fdc;
extern char g_6a23b0[];

void* __cdecl vfs_Tfopen(const char* name, const char* mode, struct VFS_DIR* root);
unsigned char* __cdecl m_alloc(int, char*);
#include "Develop/DieGildeAddOn/loadsave/loadsave.h"
unsigned short __cdecl d2_PackColorForPixelFormat(unsigned char, unsigned char, unsigned char);
void __cdecl m_FreeTracked(void*);
#include "Develop/Units/vfs/vfs.h"

void __cdecl fcn_005e3fa0(char* name)
{
	void* fh;
	unsigned char* buf;
	int n;
	int x;
	int y;

	n = 0;
	fh = vfs_Tfopen(name, g_6750e8, g_6b7fdc);
	if (fh != 0) {
		buf = m_alloc(0xe100, g_6a23b0);
		ls_ReadVfsDataChecked(buf, 0xe100, 1, fh);
		for (y = 0; y < 120; y++) {
			for (x = 0; x < 160; x++) {
				ls_SavePreviewPixels[n] = d2_PackColorForPixelFormat(buf[n * 3], buf[n * 3 + 1], buf[n * 3 + 2]);
				n++;
			}
		}
		if (buf != 0) {
			m_FreeTracked(buf);
		}
		CloseVfsStream(fh);
	}
}
