/*
 * Builds a packed shape bank for one shape list: allocates the bank, splits
 * the shapes over as few surfaces as possible, draws every shape into its
 * surface and registers the resulting bank in the texture list.
 */
#include <string.h>
#include <stdio.h>

typedef struct { int left, top, right, bottom; } ShapeRect47acf0;
typedef struct { int word[6]; } ShapeHeader47acf0;

extern int g_67dab8;
extern int g_67dabc;
extern int g_67dac0;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_77260c;
extern int g_772610;
extern char g_772c44[];

void* __cdecl m_alloc(int, char*);
void __cdecl m_FreeTracked(void*);
void __cdecl ReportClientMessage(char*);
char* __cdecl d2_GetShapeListEntry(char*, int);
int __cdecl d2_ComputeShapeSheetSizes(int, int, int, int*, int*, int);
int __cdecl d2_DrawShapeToArgbSurface(int, int, char*, char*);
int __cdecl d2_BlitRgb24ShapeToSurface(int, int, char*, char*);
char* __cdecl d2_AllocShapeBuffer(int, int);
void __cdecl d2_AppendShapeNode(char*, char*);
char* __cdecl fcn_004770a0(int*, int);
int __cdecl d2_LockSurface(char*);
void __cdecl d2_UnlockSurface(char*);
void __cdecl d2_UpdateTextureBytes(char*);
void __cdecl fcn_00475f80(char*);
int __cdecl d2_NextPowerOfTwo(int);
char* __cdecl fcn_0047b620(char*, int);
long __stdcall fcn_006114ff(int, int, int*, int, int, int*, int, unsigned int);


/* ADDRESS: GOLDTL 0x0047acf0 */
char* __cdecl fcn_0047acf0(char* list)
{
	int hdr[0x17];
	int sizes[0x20];
	char path[0x100];
	char* bank;
	char* shape;
	char* node;
	char* surf;
	char* base;
	char* uv;
	int count;
	int i;
	int j;
	int k;
	int n;
	int split;
	int sheets;
	int cols;
	int rows;
	int cells;
	int sz;
	int w;
	int h;
	int maxw;
	int minw;
	int maxh;
	int minh;
	int x;
	int y;
	int flag;
	int sourceCols;
	int firstShape;
	ShapeRect47acf0 srcRect, dstRect;

	flag = 0;
	bank = m_alloc(0x20, "plyshpbank");
	*(unsigned short*) (bank + 4) = 0;
	*(unsigned int*) bank = (unsigned int) *(unsigned char*) (list + 9);
	*(unsigned short*) (bank + 6) = *(unsigned short*) (list + 0x2c);
	*(unsigned short*) (bank + 8) = *(unsigned short*) (list + 0x2e);
	*(unsigned char*) (bank + 0x14) = *(unsigned char*) (list + 0x42);
	*(unsigned short*) (bank + 0x16) = *(unsigned short*) (list + 0x43);
	*(int*) (bank + 0x18) = (int) m_alloc(*(unsigned short*) (list + 0x2a) << 2, "plyshpshapes");
	if (*(unsigned int*) bank == 2)
		*(int*) (bank + 0x1c) = 0;
	else
		*(int*) (bank + 0x1c) = 1;
	maxw = -1;
	if (*(unsigned short*) (list + 0x2a) > 1 &&
	    (*(unsigned short*) (list + 0x2c) >= 0x80 || *(unsigned short*) (list + 0x2e) >= 0x80)) {
		minw = 0x800;
		maxh = -1;
		minh = 0x800;
		i = 0;
		while (i < (int) *(unsigned short*) (list + 0x2a)) {
			shape = d2_GetShapeListEntry(list, i);
			w = (int) *(unsigned short*) (shape + 6);
			if (w > maxw)
				maxw = w;
			else if (w < minw)
				minw = w;
			h = (int) *(unsigned short*) (shape + 0xa);
			if (h > maxh)
				maxh = h;
			else if (h < minh)
				minh = h;
			i++;
		}
		if (2.0f < (float) maxw / (float) minw ||
		    2.0f < (float) maxh / (float) minh)
			flag = 1;
	}
	if ((int) *(unsigned short*) (bank + 6) > g_67dac0 || *(unsigned short*) (bank + 6) > 0x200 || flag) {
		for (i = 0; i < (int) *(unsigned short*) (list + 0x2a); i++) {
			shape = d2_GetShapeListEntry(list, i);
			sz = d2_NextPowerOfTwo(*(unsigned short*) (shape + 6) < *(unsigned short*) (shape + 0xa)
			                  ? *(unsigned short*) (shape + 6) : *(unsigned short*) (shape + 0xa));
			if (sz > g_67dac0)
				sz = g_67dac0;
			if (sz < 0x40)
				sz = 0x40;
			cols = (int) ((float) *(unsigned short*) (shape + 6) / (float) sz + 0.5f);
			rows = (int) ((float) *(unsigned short*) (shape + 0xa) / (float) sz + 0.5f);
			cells = rows * cols;
			sourceCols = cols;
			for (k = 0; k < cells; k++) {
				sizes[k] = sz;
			}
			split = cells;
			sheets = cells;
			if (cells >= 4) {
				n = g_67dac0;
				if (n > 0x200)
					n = 0x200;
				if (sz < n) {
					if (d2_ComputeShapeSheetSizes(cells, sz, sz, &sheets, sizes, 1)) {
						cells = sheets;
					}
				}
			}
			node = d2_AllocShapeBuffer(cells, split);
			*(unsigned short*) (node + 2) = *(unsigned short*) (shape + 6);
			*(unsigned short*) (node + 6) = *(unsigned short*) (shape + 0xa);
			*(unsigned short*) (node + 0) = 0;
			*(unsigned short*) (node + 4) = 0;
			**(int**) (node + 0x30) = 0;
			*(int*) (*(int*) (node + 0x30) + 4) = 0;
			*(unsigned int*) (node + 0x34) = (unsigned int) sz;
			memset(hdr, 0, 0x17 * 4);
			hdr[1] = sz;
			if (sz <= (int) *(unsigned short*) (shape + 6))
				hdr[1] = (int) *(unsigned short*) (shape + 6);
			hdr[2] = sz;
			if (sz <= (int) *(unsigned short*) (shape + 0xa))
				hdr[2] = (int) *(unsigned short*) (shape + 0xa);
			hdr[0xa] = 0x15;
			base = fcn_004770a0(hdr, 0x20);
			d2_LockSurface(base);
			d2_DrawShapeToArgbSurface(0, 0, shape, base);
			d2_UnlockSurface(base);
			j = 0;
			y = 0;
			if (sheets >= 1) {
				do {
					memset(hdr, 0, 0x17 * 4);
					n = sizes[j];
					hdr[1] = n;
					hdr[2] = n;
					if (g_67dabc != 0)
						hdr[0xa] = 0x35545844;
					else
						hdr[0xa] = g_67dab8;
					surf = fcn_004770a0(hdr, 0);
					srcRect.top = (j / sourceCols) * sz;
					srcRect.bottom = srcRect.top + sz;
					srcRect.left = (j % sourceCols) * sz;
					srcRect.right = srcRect.left + sz;
					if (split != sheets) {
						cols = n / sz;
						cells = cols * cols;
						if (cells >= 1) {
							rows = 0;
							while (y < split) {
								dstRect.top = (rows / cols) * sz;
								dstRect.bottom = dstRect.top + sz;
								dstRect.left = (rows % cols) * sz;
								dstRect.right = dstRect.left + sz;
								srcRect.top = (y / sourceCols) * sz;
								srcRect.bottom = srcRect.top + sz;
								srcRect.left = (y % sourceCols) * sz;
								srcRect.right = srcRect.left + sz;
								fcn_006114ff(*(int*) (surf + 0x24), 0, (int*) &dstRect, *(int*) (base + 0x24), 0, (int*) &srcRect, -1, 0xff000000);
								*(float*) (*(int*) (node + 0x30) + y * 0xc) = (float) dstRect.left / (float) *(int*) (surf + 0x54);
								*(float*) (*(int*) (node + 0x30) + y * 0xc + 4) = (float) dstRect.top / (float) *(int*) (surf + 0x58);
								*(int*) (*(int*) (node + 0x30) + y * 0xc + 8) = (int) surf;
								rows++;
								y++;
								if (cells <= rows)
									break;
							}
						}
					}
					else {
						fcn_006114ff(*(int*) (surf + 0x24), 0, 0, *(int*) (base + 0x24), 0, (int*) &srcRect, -1, 0xff000000);
						*(int*) (*(int*) (node + 0x30) + j * 0xc) = 0;
						*(int*) (*(int*) (node + 0x30) + j * 0xc + 4) = 0;
						*(int*) (*(int*) (node + 0x30) + j * 0xc + 8) = (int) surf;
					}
					*(int*) (*(int*) (node + 0x28) + j * 4) = (int) surf;
					d2_UpdateTextureBytes(surf);
					g_772610 = g_772610 + *(int*) (surf + 0x4c);
					g_77260c = g_77260c + 1;
					j++;
				} while (j < sheets);
			}
			d2_AppendShapeNode(node, bank);
			n = 0;
			if (*(int*) (node + 0x2c) >= 1) {
				do {
					if (*(int*) (*(int*) (node + 0x30) + 8 + n * 0xc) == 0) {
						__asm { int 3 }
						return 0;
					}
					n++;
				} while (n < *(int*) (node + 0x2c));
			}
			fcn_00475f80(base);
		}
	}
	else {
		if (!d2_ComputeShapeSheetSizes(count, (int) *(unsigned short*) (bank + 6), (int) *(unsigned short*) (bank + 8), &split, sizes, 1)) {
			m_FreeTracked(bank);
			return 0;
		}
		node = 0;
		x = 0;
		sheets = 0;
		base = 0;
		if (split <= 0)
			goto done;
		do {
			firstShape = x;
			memset(hdr, 0, 0x17 * 4);
			sz = sizes[sheets];
			hdr[0xa] = g_67dab8;
			hdr[1] = sz;
			hdr[2] = sz;
			surf = fcn_004770a0(hdr, 0);
			g_77260c = g_77260c + 1;
			if (surf == 0) {
				m_FreeTracked(bank);
				return 0;
			}
			if (d2_LockSurface(surf) != 0) {
				cols = sz / (int) *(unsigned short*) (bank + 6);
				rows = sz / (int) *(unsigned short*) (bank + 8);
				cells = rows * cols;
				j = 0;
				if (cells >= 1) {
					while (x < (int) *(unsigned short*) (list + 0x2a)) {
						y = (int) *(unsigned short*) (bank + 6) * (j % cols);
						n = (int) *(unsigned short*) (bank + 8) * (j / cols);
						shape = d2_GetShapeListEntry(list, x);
						if (g_67dab8 != 0x15) {
							if (g_67dab8 == 0x19)
								d2_BlitRgb24ShapeToSurface(y, n, shape, surf);
						}
						else {
							d2_DrawShapeToArgbSurface(y, n, shape, surf);
						}
						node = d2_AllocShapeBuffer(1, 1);
						*(unsigned short*) (node + 0) = *(unsigned short*) (shape + 4);
						*(unsigned short*) (node + 2) = *(unsigned short*) (shape + 6);
						*(unsigned short*) (node + 4) = *(unsigned short*) (shape + 8);
						*(unsigned short*) (node + 6) = *(unsigned short*) (shape + 0xa);
						*(ShapeHeader47acf0*) (node + 9) = *(ShapeHeader47acf0*) (shape + 0xe);
						*(int*) (*(int*) (node + 0x28)) = (int) surf;
						uv = *(char**) (node + 0x30);
						*(float*) uv = (float) y / (float) sz;
						*(float*) (uv + 4) = (float) n / (float) sz;
						*(int*) (uv + 8) = (int) surf;
						*(unsigned int*) (node + 0x34) = (unsigned int) *(unsigned short*) (shape + 6);
						d2_AppendShapeNode(node, bank);
						x = x + 1;
						j++;
						if (cells <= j)
							break;
					}
				}
				d2_UnlockSurface(surf);
				sprintf(path, "d:\\develop\\d2_test\\textures\\surf%02i.bmp", g_77260c);
				if (g_67dabc != 0 && *(int*) (bank + 0x1c) != 0) {
					memset(hdr, 0, 0x17 * 4);
					hdr[1] = *(int*) (surf + 4);
					hdr[2] = *(int*) (surf + 8);
					hdr[0xa] = 0x35545844;
					base = fcn_004770a0(hdr, 0);
					fcn_006114ff(*(unsigned int*) (base + 0x24), 0, 0, *(unsigned int*) (surf + 0x24), 0, 0, -1, 0xff000000);
					for (k = firstShape; k < x; k++) {
						char* sn;

						sn = fcn_0047b620(bank, k);
						*(int*) (*(int*) (sn + 0x28)) = (int) base;
						*(int*) (*(int*) (sn + 0x28) + 0x48) = *(int*) (*(int*) (sn + 0x28) + 0x48) + 1;
					}
					fcn_00475f80(surf);
					d2_UpdateTextureBytes(base);
					g_772610 = g_772610 + *(int*) (base + 0x4c);
				}
				else {
					g_772610 = g_772610 + *(int*) (surf + 0x4c);
				}
			}
			sheets++;
		} while (sheets < split);
	}
done:
	if (*(short*) (bank + 4) == *(short*) (list + 0x2a))
		return bank;
	__asm { int 3 }
	ReportClientMessage("Invalid shapebank created...");
	return bank;
}
