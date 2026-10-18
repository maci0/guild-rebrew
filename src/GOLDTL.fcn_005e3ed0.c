

extern unsigned short g_7ea3c0[];
extern struct VFS_DIR* g_6b7fdc;
extern char g_6790b0[];
extern char g_6a23b0[];

void __cdecl fcn_00469e30(int);
void __cdecl fcn_005e3d20(void);
void* __cdecl fcn_0042ff50(const char* name, const char* mode, struct VFS_DIR* root);
unsigned char* __cdecl m_alloc(int, char*);
void __cdecl fcn_0041bb70(int, unsigned char*, unsigned char*, unsigned char*);
int __cdecl fcn_00430910(void*, int, int, void*);
void __cdecl m_FreeTracked(void*);
#include "Develop/Units/vfs/vfs.h"

void __cdecl fcn_005e3ed0(int a1, char* name)
{
	void* fh;
	unsigned char* buf;
	int n;
	int x;
	int y;

	n = 0;
	fcn_00469e30(a1);
	fcn_005e3d20();
	fh = fcn_0042ff50(name, g_6790b0, g_6b7fdc);
	if (fh != 0) {
		buf = m_alloc(0xe100, g_6a23b0);
		for (y = 0; y < 120; y++) {
			for (x = 0; x < 160; x++) {
				fcn_0041bb70(g_7ea3c0[n], &buf[n * 3], &buf[n * 3 + 1], &buf[n * 3 + 2]);
				n++;
			}
		}
		fcn_00430910(buf, 0xe100, 1, fh);
		if (buf != 0) {
			m_FreeTracked(buf);
		}
		CloseVfsStream(fh);
	}
}
