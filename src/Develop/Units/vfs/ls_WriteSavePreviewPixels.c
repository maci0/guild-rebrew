

#include "Develop/DieGildeAddOn/game/game_data.h"
extern struct VFS_DIR* g_6b7fdc;
extern char g_6a23b0[];

void __cdecl d2_SetBackdropResource(int);
void __cdecl ls_CaptureSavePreview(void);
void* __cdecl vfs_Tfopen(const char* name, const char* mode, struct VFS_DIR* root);
unsigned char* __cdecl m_alloc(int, char*);
void __cdecl gfx_UnpackPixelRgb(int, unsigned char*, unsigned char*, unsigned char*);
int __cdecl vfs_fwrite(void*, int, int, void*);
void __cdecl m_FreeTracked(void*);
#include "Develop/Units/vfs/vfs.h"

void __cdecl ls_WriteSavePreviewPixels(int previewModeArg, char* name)
{
	void* fh;
	unsigned char* buf;
	int n;
	int x;
	int y;

	n = 0;
	d2_SetBackdropResource(previewModeArg);
	ls_CaptureSavePreview();
	fh = vfs_Tfopen(name, g_6790b0, g_6b7fdc);
	if (fh != 0) {
		buf = m_alloc(0xe100, g_6a23b0);
		for (y = 0; y < 120; y++) {
			for (x = 0; x < 160; x++) {
				gfx_UnpackPixelRgb(ls_SavePreviewPixels[n], &buf[n * 3], &buf[n * 3 + 1], &buf[n * 3 + 2]);
				n++;
			}
		}
		vfs_fwrite(buf, 0xe100, 1, fh);
		if (buf != 0) {
			m_FreeTracked(buf);
		}
		CloseVfsStream(fh);
	}
}
