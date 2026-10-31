#include <stdio.h>

struct unk_436ff0;

// SIZE 0xc
struct unkvtbl_436ff0 {
	long (__stdcall* QueryInterface)(struct unk_436ff0*, void*, void**);
	unsigned long (__stdcall* AddRef)(struct unk_436ff0*);
	unsigned long (__stdcall* Release)(struct unk_436ff0*);
};

// SIZE 0x4
struct unk_436ff0 {
	struct unkvtbl_436ff0* vtbl;
};

extern unsigned long g_14ce728;
extern struct VFS_DIR* g_6b7fdc;
extern unsigned char g_6b7ff8;
extern void* g_6b5de0;

char* __cdecl m_alloc(int size, const char* tag);
void* __cdecl vfs_Tfopen(const char* name, const char* mode, struct VFS_DIR* root);
int __cdecl vfs_ReadData(char* buf, int size, int count, char* stream);
void __cdecl CloseVfsStream(void*);
#include "Develop/Units/Error/error_message.h"
long __stdcall fcn_006129e7(void*, void*, unsigned int, unsigned int, unsigned int, unsigned int, unsigned long, int, int,
    unsigned long, unsigned long, unsigned long, void*, void*, struct unk_436ff0**);
void __cdecl m_FreeTracked(void*);


/* Loads a texture file through the VFS into a managed Direct3D texture,
 * scaled down by the texture detail shift. */
/* ADDRESS: GOLDTL 0x00436ff0 */
void __cdecl fcn_00436ff0(char* name, int format, struct unk_436ff0** tex, unsigned char mips, unsigned int width, unsigned int height)
{
	char* buf;
	int size;
	int read;
	void* f;
	char msg[0x100];

	if (*tex != 0) {
		g_14ce728 = (*tex)->vtbl->Release(*tex);
		*tex = 0;
	}
	size = width * height * 4 + 0x1036;
	buf = m_alloc(size, "d3d:LoadTexture");
	f = vfs_Tfopen(name, "rb", g_6b7fdc);
	if (f != 0) {
		read = vfs_ReadData(buf, size, 1, f);
		if (read >= size) {
			sprintf(msg, "Memory size estimate for \"%s\" is too small!", name);
			ReportClientMessage(msg);
		}
		CloseVfsStream(f);
	}
	fcn_006129e7(g_6b5de0, buf, read, width >> (unsigned char) (*(unsigned int*)&g_6b7ff8), height >> (unsigned char) (*(unsigned int*)&g_6b7ff8), mips, 0,
	    format, 1, 0xffffffff, 0xffffffff, 0xff000000, 0, 0, tex);
	m_FreeTracked(buf);
}
