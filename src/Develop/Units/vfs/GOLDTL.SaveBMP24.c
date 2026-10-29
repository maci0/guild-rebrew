#include <windows.h>

typedef struct VFS_DIR VFS_DIR;
extern VFS_DIR* g_6b7fdc;
#include "Develop/Units/vfs/vfs.h"
unsigned int __cdecl vfs_fwrite(void* data, int size, int count, char* stream);

void* __cdecl m_alloc(unsigned int size, const char* tag);
void __cdecl m_FreeTracked(void* ptr);

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

/* ADDRESS: GOLDTL 0x00401ed0 */
char __cdecl SaveBMP24(char* path, int width, int height, unsigned char* pixels)
{
	BITMAPFILEHEADER header;
	BITMAPINFO info;
	unsigned char* row;
	unsigned char* src;
	unsigned char* dst;
	unsigned char* p;
	int y;
	int x;
	char* stream;

	fill0((char*) &info, sizeof(info));
	fill0((char*) &header, sizeof(header));
	info.bmiHeader.biPlanes = 1;
	info.bmiHeader.biYPelsPerMeter = 1;
	header.bfType = 0x4d42;
	header.bfSize = width * height * 3 + 0x3a;
	header.bfReserved2 = 0;
	header.bfReserved1 = 0;
	info.bmiColors[0].rgbRed = 0;
	info.bmiColors[0].rgbGreen = 0;
	info.bmiColors[0].rgbBlue = 0;
	info.bmiHeader.biCompression = 0;
	info.bmiHeader.biSizeImage = 0;
	info.bmiHeader.biClrUsed = 0;
	info.bmiHeader.biClrImportant = 0;
	info.bmiHeader.biXPelsPerMeter = 1;
	header.bfOffBits = 0x3a;
	info.bmiHeader.biSize = sizeof(info.bmiHeader);
	info.bmiHeader.biWidth = width;
	info.bmiHeader.biHeight = height;
	info.bmiHeader.biBitCount = 24;
	stream = vfs_Tfopen(path, "wbn", g_6b7fdc);
	if (stream != 0) {
		row = (unsigned char*) m_alloc(width * 3, "!bmp:SaveBMP24(temp_row)");
		vfs_fwrite(&header, sizeof(header), 1, stream);
		vfs_fwrite(&info, sizeof(info), 1, stream);
		for (y = height - 1; y >= 0; y--) {
			src = pixels + y * width * 3;
			if (width > 0) {
				dst = row;
				p = src;
				for (x = 0; x < width; x++) {
					dst[0] = p[2];
					dst[1] = p[1];
					dst[2] = p[0];
					p += 3;
					dst += 3;
				}
			}
			vfs_fwrite(row, width * 3, 1, stream);
		}
		CloseVfsStream(stream);
		m_FreeTracked(row);
		return 1;
	}
	return 0;
}
