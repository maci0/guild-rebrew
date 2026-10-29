#include <stdlib.h>
#include <string.h>

typedef struct VFS_DIR VFS_DIR;

/* SIZE 0x28 */
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

extern VFS_DIR* g_6b7fdc;
void* __cdecl vfs_Tfopen(const char* name, const char* mode, VFS_DIR* root);
void __cdecl fcn_00430a80(void* f, int off, int whence);
int __cdecl vfs_ReadData(char* buf, int size, int count, void* f);
void __cdecl CloseVfsStream(void* f);
void* __cdecl m_alloc(int size, const char* tag);
void __cdecl m_FreeTracked(void* p);
int __cdecl fcn_0041bcd0(void* dst, void* src, int w, int h, int mode, int pitch, void* fmt);

#pragma optimize("y", off)

/* ADDRESS: GOLDTL 0x00401650 */
int __cdecl fcn_00401650(const char* name, char* buf, char* palbuf, int flags)
{
	BmpInfoHeader bih;
	char pal[0x300];
	unsigned char pair[2];
	void* f;
	char* pixels;
	char* pal2;
	char* tmp;
	char* rowA;
	char* rowB;
	int bpr;
	int bpp24;
	int noflip;
	int flip;
	int needpal;
	int f1;
	int i;
	int row;
	int col;
	int n;

	flip = 0;
	noflip = 0;
	needpal = 0;
	bpp24 = 0;
	f = vfs_Tfopen(name, "rb", g_6b7fdc);
	if (f == 0) {
		return 0;
	}
	fcn_00430a80(f, 0xe, 0);
	vfs_ReadData((char*) &bih, 1, 0x28, f);
	pixels = 0;
	pal2 = 0;
	if (buf == 0) {
		flags &= ~1;
	}
	if ((flags & 0x10) == 0x10) {
		flags |= 8;
	}
	if (palbuf == 0 || ((flags & 8) == 8 && (flags & 2) == 2)) {
		flags &= ~2;
	}
	if (bih.biPlanes == 1) {
		if (bih.biBitCount == 0x18 && bih.biCompression == 0) {
			bpp24 = 1;
		} else {
			bpp24 = 0;
			if (bih.biBitCount != 8 ||
			    (bih.biCompression != 1 && bih.biCompression != 0)) {
				CloseVfsStream(f);
				return 0;
			}
			if (bih.biClrUsed == 0) {
				bih.biClrUsed = 0x100;
			}
		}
		noflip = (flags & 8) == 8;
	}
	bpr = bih.biWidth;
	if (bpp24) {
		bpr *= 3;
	}
	f1 = flags & 1;
	if (f1 == 1) {
		flip = 1;
	}
	if ((flags & 2) == 2) {
		needpal = 1;
		if (bpp24) {
			if (!flip) {
				flip = 1;
			}
			goto alloc_pixels;
		}
	}
	if (!flip) {
		goto have_pixels;
	}
alloc_pixels:
	if (bpp24 == noflip && buf != 0) {
		pixels = buf;
		goto have_pixels;
	}
	pixels = (char*) m_alloc(abs(bih.biWidth) * bpr, "!bmp:LoadBMPBuffer");
	if (bpp24) {
		goto have_pixels;
	}
have_pixels:
	if (needpal == 0 || bpp24 != 0) {
		goto read_pixels;
	}
	pal2 = (noflip != 0 || palbuf == 0)
	    ? (char*) m_alloc(0x300, "!bmp:tLoadBMP4bPal")
	    : palbuf;
	tmp = (char*) m_alloc(0x400, "!bmp:tLoadBMPPal");
	fcn_00430a80(f, bih.biClrUsed * 4 + 0x36, 0);
	vfs_ReadData(tmp, 4, bih.biClrUsed, f);
	for (i = 0; i < bih.biClrUsed; i++) {
		pal2[i * 3 + 0] = tmp[i * 4 + 2];
		pal2[i * 3 + 1] = tmp[i * 4 + 1];
		pal2[i * 3 + 2] = tmp[i * 4 + 0];
	}
	m_FreeTracked(tmp);
read_pixels:
	if (!flip) {
		goto close_stream;
	}
	fcn_00430a80(f, bih.biClrUsed * 4 + 0x36, 0);
	if (bih.biCompression != 1) {
		vfs_ReadData(pixels, bpr, abs(bih.biHeight), f);
	} else {
		row = 0;
		col = 0;
		while (row < abs(bih.biHeight)) {
			vfs_ReadData((char*) pair, 1, 2, f);
			if (pair[0] != 0) {
				memset(pixels + row * bih.biWidth + col,
				       pair[1], pair[0]);
				col += pair[0];
			} else if (pair[1] == 0) {
				col = 0;
				row++;
			} else if (pair[1] == 1) {
				col = 0;
				row = abs(bih.biHeight);
			} else if (pair[1] == 2) {
				vfs_ReadData((char*) pair, 1, 2, f);
				col += pair[0];
				row += pair[1];
			} else {
				vfs_ReadData(pixels + row * bih.biWidth + col,
					     pair[1] + (pair[1] & 1), 1, f);
				col += pair[1];
			}
		}
	}
	if (bih.biHeight > 0) {
		tmp = (char*) m_alloc(bpr, "!bmp:tGetBMPFlip");
		n = abs(bih.biHeight) / 2;
		rowA = pixels;
		rowB = pixels + (abs(bih.biHeight) - 1) * bpr;
		while (n > 0) {
			memcpy(tmp, rowA, bpr);
			memcpy(rowA, rowB, bpr);
			memcpy(rowB, tmp, bpr);
			rowA += bpr;
			rowB -= bpr;
			n--;
		}
		m_FreeTracked(tmp);
	}
close_stream:
	CloseVfsStream(f);
	if (bpp24 == noflip) {
		goto release;
	}
	if (f1 == 0) {
		goto release;
	}
	if (noflip) {
		n = abs(bih.biHeight) * bpr;
		for (i = 0; i < n; i++) {
			buf[i * 3 + 0] = pal2[pixels[i] * 3 + 0];
			buf[i * 3 + 1] = pal2[pixels[i] * 3 + 1];
			buf[i * 3 + 2] = pal2[pixels[i] * 3 + 2];
		}
	} else {
		if (pal2 == 0) {
			pal2 = palbuf;
		}
		fcn_0041bcd0(pixels, buf, bih.biWidth, abs(bih.biHeight),
			     0x100, 1, pal);
		if (pal2 != 0) {
			for (i = 0; i < 0x100; i++) {
				pal2[i * 3 + 0] = pal[i];
				pal2[i * 3 + 1] = pal[0x100 + i];
				pal2[i * 3 + 2] = pal[0x200 + i];
			}
		}
	}
release:
	if (pixels != buf) {
		m_FreeTracked(pixels);
	}
	if (pal2 != 0 && (noflip == 0 || palbuf == 0)) {
		m_FreeTracked(pal2);
	}
	if ((flags & 0x10) == 0x10 && buf != 0) {
		n = abs(bih.biHeight) * bpr;
		rowB = buf + n * 3 - 3;
		rowA = buf + n * 4 - 4;
		if ((flags & 0x20) != 0x20) {
			while (n > 0) {
				rowA[0] = rowB[2];
				rowA[1] = rowB[1];
				rowA[2] = rowB[0];
				rowA[3] = 0;
				rowB -= 3;
				rowA -= 4;
				n--;
			}
		} else {
			while (n > 0) {
				rowA[0] = rowB[0];
				rowA[1] = rowB[1];
				rowA[2] = rowB[2];
				rowA[3] = 0;
				rowB -= 3;
				rowA -= 4;
				n--;
			}
		}
		return 1;
	}
	return 1;
}
/* Layout scaffolding: shifts the next source object to its reference
 * VA. 0x90 filler, not reconstruction. Generated by the text lead pass. */
#pragma data_seg(".text")
unsigned char _tlead_GOLDTL_fcn_00401650[240] = {
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90
};
