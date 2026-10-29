


#include <stdlib.h>

// SIZE 0x28
typedef struct {
	unsigned int biSize;
	int biWidth;
	int biHeight;
	unsigned short biPlanes;
	unsigned short biBitCount;
	unsigned int biCompression;
	unsigned int biSizeImage;
	int biXPelsPerMeter;
	int biYPelsPerMeter;
	unsigned int biClrUsed;
	unsigned int biClrImportant;
} BmpInfoHeader;

typedef struct VFS_DIR VFS_DIR;
extern VFS_DIR* g_6b7fdc;
void* __cdecl vfs_Tfopen(const char* name, const char* mode, struct VFS_DIR* root);
void __cdecl fcn_00430a80(void* f, int off, int whence);
int __cdecl vfs_ReadData(char* buf, int size, int count, char* f);
void __cdecl CloseVfsStream(void* f);

char __cdecl fcn_00401590(const char* name, int* width, int* height, int* bpp)
{
	BmpInfoHeader bih;
	char result;
	void* f;

	result = 0;
	f = vfs_Tfopen(name, "rb", g_6b7fdc);
	if (f != 0) {
		fcn_00430a80(f, 0xe, 0);
		vfs_ReadData((char*)&bih, 1, 0x28, f);
		CloseVfsStream(f);
		if (bih.biPlanes == 1 && (bih.biBitCount == 8 || bih.biBitCount == 0x18) &&
		    (bih.biCompression == 1 || bih.biCompression == 0)) {
			if (width != 0) {
				*width = bih.biWidth;
			}
			if (height != 0) {
				*height = abs(bih.biHeight);
			}
			if (bpp != 0) {
				*bpp = bih.biBitCount;
			}
			result = 1;
		}
	}
	return result;
}
