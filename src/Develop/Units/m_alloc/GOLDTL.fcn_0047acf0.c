/*
 * Builds a packed shape bank for one shape list: allocates the bank, splits
 * the shapes over as few surfaces as possible, draws every shape into its
 * surface and registers the resulting bank in the texture list.
 */
#include <string.h>
#include <stdio.h>

extern int g_67dab8;
extern int g_67dabc;
extern int g_67dac0;
extern float g_662918;
extern int g_77260c;
extern int g_772610;
extern char g_772c44[];

void* __cdecl m_alloc(int, char*);
void __cdecl m_FreeTracked(void*);
void __cdecl ReportClientMessage(char*);
char* __cdecl fcn_0047a070(char*, int);
int __cdecl fcn_0047a570(int, int, int, int*, int*, int);
int __cdecl fcn_0047a710(int, int, char*, char*);
int __cdecl fcn_0047a990(int, int, char*, char*);
char* __cdecl fcn_0047abd0(int, int);
void __cdecl fcn_0047ac20(char*, char*);
char* __cdecl fcn_004770a0(int*, int);
int __cdecl fcn_00475fd0(char*);
void __cdecl fcn_00476060(char*);
void __cdecl fcn_004760e0(char*);
void __cdecl fcn_00475f80(char*);
int __cdecl fcn_00477420(int);
char* __cdecl fcn_0047b620(char*, int);
void __cdecl fcn_006114ff(int, int, int*, int, int, int*, int, int);


/* ADDRESS: GOLDTL 0x0047acf0 */
char* __cdecl fcn_0047acf0(char* list)
{
	int sizes[0x20];
	int hdr[0x17];
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

	flag = 0;
	bank = m_alloc(0x20, "plyshpbank");
	*(unsigned short*) (bank + 4) = 0;
	*(unsigned int*) bank = (unsigned int) *(unsigned char*) (list + 9);
	*(unsigned short*) (bank + 6) = *(unsigned short*) (list + 0x2c);
	*(unsigned short*) (bank + 8) = *(unsigned short*) (list + 0x2e);
	*(unsigned char*) (bank + 0x14) = *(unsigned char*) (list + 0x42);
	*(unsigned short*) (bank + 0x16) = *(unsigned short*) (list + 0x43);
	count = (int) *(unsigned short*) (list + 0x2a);
	*(int*) (bank + 0x18) = (int) m_alloc(count << 2, "plyshpshapes");
	if (*(unsigned int*) bank != 2)
		*(int*) (bank + 0x1c) = 1;
	else
		*(int*) (bank + 0x1c) = 0;
	maxw = -1;
	if ((int) *(unsigned short*) (list + 0x2a) >= 2 &&
	    (*(unsigned short*) (list + 0x2c) >= 0x80 || *(unsigned short*) (list + 0x2e) >= 0x80)) {
		minw = 0x800;
		maxh = -1;
		minh = 0x800;
		i = 0;
		while (i < (int) *(unsigned short*) (list + 0x2a)) {
			shape = fcn_0047a070(list, i);
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
		if (g_662918 < (float) maxw / (float) minw ||
		    g_662918 < (float) maxh / (float) minh)
			flag = 1;
	}
	w = (int) *(unsigned short*) (bank + 6);
	if (w <= g_67dac0 && w <= 0x200 && !flag) {
		if (!fcn_0047a570(count, w, (int) *(unsigned short*) (bank + 8), &split, sizes, 1)) {
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
			if (fcn_00475fd0(surf) != 0) {
				cols = sz / (int) *(unsigned short*) (bank + 6);
				rows = sz / (int) *(unsigned short*) (bank + 8);
				cells = rows * cols;
				j = 0;
				if (cells >= 1) {
					while (x < (int) *(unsigned short*) (list + 0x2a)) {
						y = (int) *(unsigned short*) (bank + 6) * (j % cols);
						n = (int) *(unsigned short*) (bank + 8) * (j / cols);
						shape = fcn_0047a070(list, x);
						if (g_67dab8 != 0x15) {
							if (g_67dab8 == 0x19)
								fcn_0047a990(y, n, shape, surf);
						}
						else {
							fcn_0047a710(y, n, shape, surf);
						}
						node = fcn_0047abd0(1, 1);
						*(unsigned short*) (node + 0) = *(unsigned short*) (shape + 4);
						*(unsigned short*) (node + 2) = *(unsigned short*) (shape + 6);
						*(unsigned short*) (node + 4) = *(unsigned short*) (shape + 8);
						*(unsigned short*) (node + 6) = *(unsigned short*) (shape + 0xa);
						*(int*) (node + 0x09) = *(int*) (shape + 0x0e);
						*(int*) (node + 0x0d) = *(int*) (shape + 0x12);
						*(int*) (node + 0x11) = *(int*) (shape + 0x16);
						*(int*) (node + 0x15) = *(int*) (shape + 0x1a);
						*(int*) (node + 0x19) = *(int*) (shape + 0x1e);
						*(int*) (node + 0x1d) = *(int*) (shape + 0x22);
						*(int*) (*(int*) (node + 0x28)) = (int) surf;
						uv = *(char**) (node + 0x30);
						*(float*) uv = (float) y / (float) sz;
						*(float*) (uv + 4) = (float) n / (float) sz;
						*(int*) (uv + 8) = (int) surf;
						*(unsigned int*) (node + 0x34) = (unsigned int) *(unsigned short*) (shape + 6);
						fcn_0047ac20(node, bank);
						x = x + 1;
						j++;
						if (cells <= j)
							break;
					}
				}
				k = fcn_00475fd0(surf);
				sprintf((char*) 0x6806280, "d:\\develop\\d2_test\\textures\\surf%02i.bmp", g_77260c);
				if (g_67dabc != 0 && *(int*) (bank + 0x1c) != 0) {
					memset(hdr, 0, 0x17 * 4);
					hdr[1] = *(int*) (shape + 8);
					hdr[2] = *(int*) (shape + 0xc);
					hdr[0xa] = 0x35545844;
					base = fcn_004770a0(hdr, 0);
					fcn_006114ff(*(unsigned int*) (base + 0x24), 0, 0, *(unsigned int*) (surf + 0x24), 0, 0, -1, 0xff000000);
					for (k = 0; k < x; k++) {
						char* sn;

						sn = fcn_0047b620(bank, k);
						*(int*) (*(int*) (sn + 0x28)) = (int) base;
						*(int*) (*(int*) (sn + 0x28) + 0x48) = *(int*) (*(int*) (sn + 0x28) + 0x48) + 1;
					}
					fcn_00476060(base);
					g_772610 = g_772610 + *(int*) (base + 0x4c);
				}
				else {
					g_772610 = g_772610 + *(int*) (shape + 0x4c);
				}
				fcn_004760e0(surf);
			}
			sheets++;
		} while (sheets < split);
	}
	else {
		i = 0;
		if (*(short*) (list + 0x2a) == 0)
			goto done;
		do {
			shape = fcn_0047a070(list, i);
			w = (int) *(unsigned short*) (shape + 6);
			h = (int) *(unsigned short*) (shape + 0xa);
			sz = fcn_00477420(w < h ? w : h);
			if (sz >= g_67dac0)
				sz = g_67dac0;
			if (sz <= 0x3f)
				sz = 0x40;
			cols = (int) ((float) *(unsigned short*) (shape + 6) / (float) sz + 0.5f);
			rows = (int) ((float) *(unsigned short*) (shape + 0xa) / (float) sz + 0.5f);
			cells = rows * cols;
			if (cells >= 1) {
				k = 0;
				while (k < cells) {
					sizes[k] = sz;
					k++;
				}
			}
			split = cells;
			if (cells >= 4) {
				n = g_67dac0;
				if (n > 0x200)
					n = 0x200;
				if (sz < n) {
					if (fcn_0047a570(cells, sz, sz, &sheets, sizes, 1)) {
						cells = sheets;
					}
				}
			}
			node = fcn_0047abd0(cells, split);
			*(unsigned short*) (node + 2) = *(unsigned short*) (shape + 6);
			*(unsigned short*) (node + 6) = *(unsigned short*) (shape + 0xa);
			*(unsigned short*) (node + 0) = 0;
			*(unsigned short*) (node + 4) = 0;
			uv = *(char**) (node + 0x30);
			*(int*) uv = 0;
			*(int*) (uv + 4) = 0;
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
			fcn_00475fd0(base);
			fcn_0047a710(0, 0, shape, base);
			fcn_00476060(base);
			j = 0;
			y = 0;
			if (sheets >= 1) {
				do {
					memset(hdr, 0, 0x17 * 4);
					n = sizes[j];
					hdr[0xa] = g_67dabc != 0 ? 0x35545844 : g_67dab8;
					hdr[1] = n;
					hdr[2] = n;
					surf = fcn_004770a0(hdr, 0);
					if (split != sheets) {
						cols = n / sz;
						cells = cols * cols;
						if (cells >= 1) {
							rows = 0;
							while (y < split) {
								x = (rows / cols) * sz;
								k = (rows % cols) * sz;
								fcn_006114ff(*(int*) (surf + 0x24), 0, &x, *(int*) (base + 0x24), 0, &k, -1, 0xff000000);
								uv = *(char**) (node + 0x30);
								*(float*) (uv + y * 0xc) = (float) ((rows % cols) * sz) / (float) *(int*) (shape + 0x54);
								*(float*) (uv + y * 0xc + 4) = (float) ((rows / cols) * sz) / (float) *(int*) (shape + 0x58);
								*(int*) (uv + y * 0xc + 8) = (int) shape;
								rows++;
								y++;
								if (cells <= rows % cells)
									break;
							}
						}
					}
					else {
						k = 0;
						fcn_006114ff(*(int*) (surf + 0x24), 0, 0, *(int*) (base + 0x24), 0, &k, -1, 0xff000000);
						uv = *(char**) (node + 0x30);
						*(int*) (uv) = 0;
						*(int*) (uv + 4) = 0;
						*(int*) (uv + 8) = (int) shape;
					}
					*(int*) (*(int*) (node + 0x28) + j * 4) = (int) shape;
					fcn_004760e0(shape);
					g_772610 = g_772610 + *(int*) (shape + 0x4c);
					g_77260c = g_77260c + 1;
					j++;
				} while (j < sheets);
			}
			fcn_0047ac20(node, bank);
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
			i++;
		} while (i < (int) *(unsigned short*) (list + 0x2a));
	}
done:
	if (*(short*) (bank + 4) == *(short*) (list + 0x2a))
		return bank;
	__asm { int 3 }
	ReportClientMessage("Invalid shapebank created...");
	return bank;
}
