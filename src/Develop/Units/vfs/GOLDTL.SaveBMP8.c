#include <windows.h>

typedef struct VFS_DIR VFS_DIR;
extern VFS_DIR* g_6b7fdc;
#include "Develop/Units/vfs/vfs.h"
unsigned int __cdecl vfs_fwrite(void* data, int size, int count, char* stream);


/* Inferred helper name; original operand-homed assembly is documented in
 * docs/msvc6-allocator.md and the target-scoped source evidence. */
static __inline void fill0(char* dst, int size)
{
	char* d;
	int n;

	n = size;
	d = dst;
	__asm {
		mov edi, d
		mov ebx, n
		xor eax, eax
		lea ecx, [edi+edi*2]
		and ecx, 3
		sub ebx, ecx
		jle short L1
		rep stosb
		mov ecx, ebx
		and ebx, 3
		shr ecx, 2
		rep stosd
	L1:
		add ecx, ebx
		rep stosb
	}
}

/* ADDRESS: GOLDTL 0x00401d10 */
char __cdecl SaveBMP8(char* path, int width, int height, unsigned char* pixels, unsigned char* palette)
{
    BITMAPFILEHEADER header;
    BITMAPINFOHEADER info;
    unsigned char colors[1024];
    char* stream;
    int i;

    fill0((char*) &info, sizeof(info));
    fill0((char*) &header, sizeof(header));
    header.bfType = 0x4d42;
    header.bfSize = height * width + 0x436;
    header.bfReserved2 = 0;
    header.bfReserved1 = 0;
    header.bfOffBits = 0x436;
    for (i = 0; i < 256; i++) {
        colors[i * 4] = palette != 0 ? palette[i * 3 + 2] : i;
        colors[i * 4 + 1] = palette != 0 ? palette[i * 3 + 1] : i;
        colors[i * 4 + 2] = palette != 0 ? palette[i * 3] : i;
        colors[i * 4 + 3] = 0;
    }
    info.biWidth = width;
    info.biSize = sizeof(info);
    info.biHeight = height;
    info.biPlanes = 1;
    info.biBitCount = 8;
    info.biCompression = 0;
    info.biSizeImage = 0;
    info.biYPelsPerMeter = 1;
    info.biXPelsPerMeter = 1;
    info.biClrUsed = 0;
    info.biClrImportant = 0;
    stream = vfs_Tfopen(path, "wbn", g_6b7fdc);
    if (stream != 0) {
        vfs_fwrite(&header, sizeof(header), 1, stream);
        vfs_fwrite(&info, sizeof(info), 1, stream);
        vfs_fwrite(colors, sizeof(colors), 1, stream);
        for (i = height - 1; i >= 0; i--)
            vfs_fwrite(pixels + i * width, width, 1, stream);
        CloseVfsStream(stream);
        return 1;
    }
    return 0;
}
