/*
 * Reconstructed from the native body at 0x0043c640 (5419 bytes).
 *
 * Per-region material analysis for one tile: edge flags from the material map,
 * a 256-mask overdraw search, then for every material slot of every 8x8 region
 * the cell classification, index list and vertex emission.
 *
 * Tile layout: +0x000 W, +0x004 H, +0x014 material map, +0x020 vertex array,
 * +0x024 edge flags, +0x030 material slot table, +0x0a0 region table
 * (64 regions of 500 bytes, each holding 8 records of 0x34), +0x802c jitter
 * step, +0x8030 vertex step.
 */

#include <stdlib.h>
#include <string.h>

extern void* __cdecl m_alloc(unsigned int size, const char* tag);
extern void __cdecl m_FreeTracked(void* ptr);

extern float g_662a18;

#define MATERIALS	8
#define MASK_LIMIT	0x100
#define SCORE_LIMIT	0x40000000
#define REGION_STRIDE	500

typedef struct RegionRecord RegionRecord;
typedef struct Region Region;
typedef struct Tile Tile;

struct RegionRecord {
	void* p00;		/* +0x00 */
	int* p04;		/* +0x04 */
	int* p08;		/* +0x08 */
	unsigned short* p0c;	/* +0x0c */
	unsigned short* p10;	/* +0x10 */
	int unk14;		/* +0x14 */
	int unk18;		/* +0x18 */
	int material;		/* +0x1c */
	int n20;		/* +0x20 */
	int n24;		/* +0x24 */
	int n28;		/* +0x28 */
	int n2c;		/* +0x2c */
	int n30;		/* +0x30 */
};

struct Region {
	RegionRecord rec[MATERIALS];	/* +0x000 */
	unsigned char tail[0x54];	/* +0x1a0 */
};

struct Tile {
	int W;				/* +0x000 */
	int H;				/* +0x004 */
	unsigned char gap08[0x0c];
	unsigned char* mat;		/* +0x014 */
	unsigned char gap18[8];
	float* verts;			/* +0x020 */
	unsigned char* flags;		/* +0x024 */
	unsigned char gap28[8];
	int slot[MATERIALS];		/* +0x030 */
	unsigned char gap50[0x50];
	Region region[64];		/* +0x0a0 */
	unsigned char gap7da0[0x28c];
	float jitter;			/* +0x802c */
	float vstep;			/* +0x8030 */
};

#pragma optimize("y", off)
/* ADDRESS: GOLDTL 0x0043c640 */
void __cdecl fcn_0043c640(Tile* t)
{
	int x;
	int y;
	int y1;
	int row;
	int col;
	int bit;
	int m;
	int best;
	int bestscore;
	int i;
	int n;
	int count1;
	int count2;
	int count;
	int limitX;
	int limitY;
	int v0;
	int v1;
	int off;
	int* slot;
	int* idx;
	unsigned char* map;
	unsigned char* cand;
	unsigned char* bestmap;
	RegionRecord* r;
	unsigned short* out;
	unsigned char* p;
	float jx;
	float jy;
	float jx2;
	float jy2;
	float f;

	for (y = 0; y < t->W - 1; y++) {
		y1 = y + 1;
		for (x = 0; x < t->W - 1; x++) {
			if (t->mat[y * t->W + x] != t->mat[y1 * t->W + x + 1]) {
				t->flags[y * t->W + x] |= 0x80;
			} else if (t->mat[y * t->W + x + 1] != t->mat[y1 * t->W + x]) {
				t->flags[y * t->W + x] &= 0x7f;
			}
		}
	}

	map = (unsigned char*) m_alloc(t->H * t->H, (const char*) 0x67a694);
	cand = (unsigned char*) m_alloc(t->H * t->H, (const char*) 0x67a680);
	bestmap = (unsigned char*) m_alloc(t->H * t->H, (const char*) 0x67a668);
	idx = (int*) m_alloc((t->H + 1) * (t->H + 1) * 4, (const char*) 0x67a654);

	for (y = 0; y < 8; y++) {
		for (x = 0; x < 8; x++) {
			y1 = y + 1;
			best = -1;
			bestscore = SCORE_LIMIT;
			for (count = 1; count < MASK_LIMIT; count++) {
				if (bestscore <= 0) {
					break;
				}
				m = count;
				slot = t->slot;
				while (m > 0) {
					if ((m & 1) == 1 && *slot == 0) {
						break;
					}
					m >>= 1;
					slot++;
				}
				if (m != 0) {
					continue;
				}
				memset(cand, 0, t->H * t->H);
				limitY = t->H * y1;
				if (limitY > t->W - 1) {
					limitY = t->W - 1;
				}
				for (row = t->H * y; row < limitY; row++) {
					limitX = t->H * (x + 1);
					if (limitX > t->W - 1) {
						limitX = t->W - 1;
					}
					for (col = t->H * x; col < limitX; col++) {
						m = count;
						for (bit = 0; bit < 8; bit++) {
							p = &t->mat[row * t->W + col];
							if ((p[0] == 0 || p[1] == 0 ||
							     t->mat[(row + 1) * t->W + col] == 0 ||
							     t->mat[(row + 1) * t->W + col + 1] == 0) &&
							    (p[0] != 0 || p[1] != 0 ||
							     t->mat[(row + 1) * t->W + col] != 0 ||
							     t->mat[(row + 1) * t->W + col + 1] != 0)) {
								cand[(row - t->H * y) * t->H + (col - t->H * x)] |= 0x10;
								if ((m & 1) == 1) {
									cand[(row - t->H * y) * t->H + (col - t->H * x)]++;
								}
							}
							m >>= 1;
						}
					}
				}
				n = 0;
				for (row = 0; row < t->H; row++) {
					if (n >= SCORE_LIMIT) {
						break;
					}
					for (col = 0; col < t->H; col++) {
						m = cand[row * t->H + col];
						if ((m & 0x10) == 0x10) {
							if ((m & 0xf) == 0) {
								n = SCORE_LIMIT;
								break;
							}
							n += (m & 0xf) - 1;
						}
					}
				}
				if (n < bestscore) {
					bestscore = n;
					best = count;
					memcpy(bestmap, cand, t->H * t->H);
				}
			}
			off = (x + y * 8) * REGION_STRIDE;
			r = (RegionRecord*) ((char*) t + off + 0xbc);
			for (i = 8; i != 0; i--) {
				r->material = 2;
				r = (RegionRecord*) ((char*) r + 0x34);
			}
			if (bestscore < SCORE_LIMIT) {
				for (m = best; m > 0; m >>= 1) {
					r->material = (m & 1) == 1 ? 1 : 2;
					r = (RegionRecord*) ((char*) r + 0x34);
				}
			}
			for (i = 0; i < MATERIALS; i++) {
				r = &((Region*) ((char*) t + off + 0xa0))->rec[i];
				count2 = 0;
				count1 = 0;
				if (r->p04 != 0) {
					m_FreeTracked(r->p04);
					r->p04 = 0;
				}
				if (r->p08 != 0) {
					m_FreeTracked(r->p08);
					r->p08 = 0;
				}
				if (r->p0c != 0) {
					m_FreeTracked(r->p0c);
					r->p0c = 0;
				}
				if (r->p10 != 0) {
					m_FreeTracked(r->p10);
					r->p10 = 0;
				}
				if (r->p00 != 0) {
					m_FreeTracked(r->p00);
					r->p00 = 0;
				}
				r->n24 = 0;
				r->n20 = 0;
				r->n30 = 0;
				r->n2c = 0;
				memset(map, 0, t->H * t->H);
				limitY = t->H * y1;
				if (limitY > t->W - 1) {
					limitY = t->W - 1;
				}
				for (row = t->H * y; row < limitY; row++) {
					limitX = t->H * (x + 1);
					if (limitX > t->W - 1) {
						limitX = t->W - 1;
					}
					for (col = t->H * x; col < limitX; col++) {
						p = &t->mat[row * t->W + col];
						if (p[0] == i && p[1] == i &&
						    t->mat[(row + 1) * t->W + col] == i &&
						    t->mat[(row + 1) * t->W + col + 1] == i) {
							map[(row - t->H * y) * t->H + (col - t->H * x)] = 1;
							count1++;
						} else if (p[0] == i || p[1] == i ||
							   t->mat[(row + 1) * t->W + col] == i ||
							   t->mat[(row + 1) * t->W + col + 1] == i) {
							map[(row - t->H * y) * t->H + (col - t->H * x)] = 2;
							count2++;
						}
					}
				}
				if (count1 > 0) {
					n = count1 * 4;
					memset(idx, -1, (t->H + 1) * (t->H + 1) * 4);
					for (row = 0; row < t->H; row++) {
						for (col = 0; col < t->H; col++) {
							p = &map[row * t->H + col];
							if (p[0] == 1) {
								if (col < t->H - 1 && row < t->H - 1 &&
								    p[1] == 1 && map[(row + 1) * t->H + col] == 1) {
									n -= 3;
								} else if (col < t->H - 1 && p[1] == 1) {
									n -= 2;
								} else if (row < t->H - 1 &&
									   map[(row + 1) * t->H + col] == 1) {
									n -= 2;
								} else if (col < t->H - 1 && row < t->H - 1 &&
									   map[(row + 1) * t->H + col + 1] == 1) {
									n -= 1;
								}
							}
						}
					}
					r->n20 = n;
					r->p04 = (int*) m_alloc(n * 4, (const char*) 0x67a638);
					r->n2c = count1 * 2;
					r->p0c = (unsigned short*) m_alloc(r->n2c * 6, (const char*) 0x67a624);
					out = r->p0c;
					limitX = x == 7 ? t->H - 4 : t->H;
					limitY = y == 7 ? t->H - 4 : t->H;
					count = 0;
					r->n2c = 0;
					for (row = 0; row < limitY; row++) {
						for (col = 0; col < limitX; col++) {
							if (map[row * t->H + col] != 1) {
								continue;
							}
							v0 = (t->H + 1) * row + col;
							v1 = (row + 1) * (t->H + 1) + col;
							if (idx[v0] == -1) {
								r->p04[count] = t->H * x +
									(row + t->H * y) * t->W + col - 0x1000000;
								idx[v0] = count;
								count++;
								jx = col != 0 ? t->jitter : 0;
								jy = row != 0 ? t->jitter : 0;
								f = (float) rand() * g_662a18 * jx;
								t->verts[2 * (t->W * (row + t->H * y) + t->H * x + col)] =
									((float) (t->H * x + col) * t->vstep + f + f) - jx;
								f = (float) rand() * g_662a18 * jy;
								t->verts[2 * (t->W * (row + t->H * y) + t->H * x + col) + 1] =
									((float) (t->H * y + row) * t->vstep + f + f) - jy;
							}
							if (idx[v0 + 1] == -1) {
								r->p04[count] = t->H * x +
									(row + t->H * y) * t->W + col + 1 - 0x1000000;
								idx[v0 + 1] = count;
								count++;
								jx = col == t->H - 1 ? 0 : t->jitter;
								jy = row != 0 ? t->jitter : 0;
								f = (float) rand() * g_662a18 * jx;
								t->verts[2 * (t->W * (row + t->H * y) + t->H * x + col) + 2] =
									((float) (t->H * x + col + 1) * t->vstep + f + f) - jx;
								f = (float) rand() * g_662a18 * jy;
								t->verts[2 * (t->W * (row + t->H * y) + t->H * x + col) + 3] =
									((float) (t->H * y + row) * t->vstep + f + f) - jy;
							}
							if (idx[v1] == -1) {
								r->p04[count] = t->H * x +
									(row + 1 + t->H * y) * t->W + col - 0x1000000;
								idx[v1] = count;
								count++;
								jx = col != 0 ? t->jitter : 0;
								jy = row == t->H - 1 ? 0 : t->jitter;
								f = (float) rand() * g_662a18 * jx;
								t->verts[2 * (t->W * (row + 1 + t->H * y) + t->H * x + col)] =
									((float) (t->H * x + col) * t->vstep + f + f) - jx;
								f = (float) rand() * g_662a18 * jy;
								t->verts[2 * (t->W * (row + 1 + t->H * y) + t->H * x + col) + 1] =
									((float) (t->H * y + row + 1) * t->vstep + f + f) - jy;
							}
							if (idx[v1 + 1] == -1) {
								r->p04[count] = t->H * x +
									(row + 1 + t->H * y) * t->W + col + 1 - 0x1000000;
								idx[v1 + 1] = count;
								count++;
								jx = col == t->H - 1 ? 0 : t->jitter;
								jy = row == t->H - 1 ? 0 : t->jitter;
								f = (float) rand() * g_662a18 * jx;
								t->verts[2 * (t->W * (row + 1 + t->H * y) + t->H * x + col) + 2] =
									((float) (t->H * x + col + 1) * t->vstep + f + f) - jx;
								f = (float) rand() * g_662a18 * jy;
								t->verts[2 * (t->W * (row + 1 + t->H * y) + t->H * x + col) + 3] =
									((float) (t->H * y + row + 1) * t->vstep + f + f) - jy;
							}
							if ((signed char) t->flags[t->W * (row + t->H * y) +
										   t->H * x + col] < 0) {
								out[0] = (unsigned short) idx[v0];
								out[1] = (unsigned short) idx[v0 + 1];
								out[2] = (unsigned short) idx[v1];
								out[3] = (unsigned short) idx[v1];
								out[4] = (unsigned short) idx[v0 + 1];
								out[5] = (unsigned short) idx[v1 + 1];
							} else {
								out[0] = (unsigned short) idx[v1];
								out[1] = (unsigned short) idx[v0];
								out[2] = (unsigned short) idx[v1 + 1];
								out[3] = (unsigned short) idx[v1 + 1];
								out[4] = (unsigned short) idx[v0];
								out[5] = (unsigned short) idx[v0 + 1];
							}
							out += 6;
							r->n2c += 2;
						}
					}
					r->n20 = count;
				}
				if (count2 > 0) {
					n = count2 * 4;
					memset(idx, -1, (t->H + 1) * (t->H + 1) * 4);
					for (row = 0; row < t->H; row++) {
						for (col = 0; col < t->H; col++) {
							p = &map[row * t->H + col];
							if (p[0] == 2) {
								if (col < t->H - 1 && row < t->H - 1 &&
								    p[1] == 2 && map[(row + 1) * t->H + col] == 2) {
									n -= 3;
								} else if (col < t->H - 1 && p[1] == 2) {
									n -= 2;
								} else if (row < t->H - 1 &&
									   map[(row + 1) * t->H + col] == 2) {
									n -= 2;
								} else if (col < t->H - 1 && row < t->H - 1 &&
									   map[(row + 1) * t->H + col + 1] == 2) {
									n -= 1;
								}
							}
						}
					}
					r->n24 = n;
					r->p08 = (int*) m_alloc(n * 4, (const char*) 0x67a60c);
					r->n30 = count2 * 2;
					r->p10 = (unsigned short*) m_alloc(r->n30 * 6, (const char*) 0x67a5f8);
					r->p00 = m_alloc(r->n30 * 4, (const char*) 0x67a5e0);
					out = r->p10;
					limitX = x == 7 ? t->H - 4 : t->H;
					limitY = y == 7 ? t->H - 4 : t->H;
					count = 0;
					r->n30 = 0;
					for (row = 0; row < limitY; row++) {
						for (col = 0; col < limitX; col++) {
							if (map[row * t->H + col] != 2) {
								continue;
							}
							v0 = (t->H + 1) * row + col;
							v1 = (row + 1) * (t->H + 1) + col;
							if (idx[v0] == -1) {
								r->p08[count] =
									(t->mat[(row + t->H * y) * t->W + t->H * x + col] == i ?
									 0xFF000000 : 0) +
									(row + t->H * y) * t->W + t->H * x + col;
								idx[v0] = count;
								count++;
								jx2 = col != 0 ? t->jitter : 0;
								jy2 = row != 0 ? t->jitter : 0;
								f = (float) rand() * g_662a18 * jx2;
								t->verts[2 * (t->W * (row + t->H * y) + t->H * x + col)] =
									((float) (t->H * x + col) * t->vstep + f + f) - jx2;
								f = (float) rand() * g_662a18 * jy2;
								t->verts[2 * (t->W * (row + t->H * y) + t->H * x + col) + 1] =
									((float) (t->H * y + row) * t->vstep + f + f) - jy2;
							}
							if (idx[v0 + 1] == -1) {
								r->p08[count] =
									(t->mat[(row + t->H * y) * t->W + t->H * x + col + 1] == i ?
									 0xFF000000 : 0) +
									(row + t->H * y) * t->W + t->H * x + col + 1;
								idx[v0 + 1] = count;
								count++;
								jx2 = col == t->H - 1 ? 0 : t->jitter;
								jy2 = row != 0 ? t->jitter : 0;
								f = (float) rand() * g_662a18 * jx2;
								t->verts[2 * (t->W * (row + t->H * y) + t->H * x + col) + 2] =
									((float) (t->H * x + col + 1) * t->vstep + f + f) - jx2;
								f = (float) rand() * g_662a18 * jy2;
								t->verts[2 * (t->W * (row + t->H * y) + t->H * x + col) + 3] =
									((float) (t->H * y + row) * t->vstep + f + f) - jy2;
							}
							if (idx[v1] == -1) {
								r->p08[count] =
									(t->mat[(row + 1 + t->H * y) * t->W + t->H * x + col] == i ?
									 0xFF000000 : 0) +
									(row + 1 + t->H * y) * t->W + t->H * x + col;
								idx[v1] = count;
								count++;
								jx2 = col != 0 ? t->jitter : 0;
								jy2 = row == t->H - 1 ? 0 : t->jitter;
								f = (float) rand() * g_662a18 * jx2;
								t->verts[2 * (t->W * (row + 1 + t->H * y) + t->H * x + col)] =
									((float) (t->H * x + col) * t->vstep + f + f) - jx2;
								f = (float) rand() * g_662a18 * jy2;
								t->verts[2 * (t->W * (row + 1 + t->H * y) + t->H * x + col) + 1] =
									((float) (t->H * y + row + 1) * t->vstep + f + f) - jy2;
							}
							if (idx[v1 + 1] == -1) {
								r->p08[count] =
									(t->mat[(row + 1 + t->H * y) * t->W + t->H * x + col + 1] == i ?
									 0xFF000000 : 0) +
									(row + 1 + t->H * y) * t->W + t->H * x + col + 1;
								idx[v1 + 1] = count;
								count++;
								jx2 = col == t->H - 1 ? 0 : t->jitter;
								jy2 = row == t->H - 1 ? 0 : t->jitter;
								f = (float) rand() * g_662a18 * jx2;
								t->verts[2 * (t->W * (row + 1 + t->H * y) + t->H * x + col) + 2] =
									((float) (t->H * x + col + 1) * t->vstep + f + f) - jx2;
								f = (float) rand() * g_662a18 * jy2;
								t->verts[2 * (t->W * (row + 1 + t->H * y) + t->H * x + col) + 3] =
									((float) (t->H * y + row + 1) * t->vstep + f + f) - jy2;
							}
							if ((signed char) t->flags[t->W * (row + t->H * y) +
										   t->H * x + col] < 0) {
								out[0] = (unsigned short) idx[v0];
								out[1] = (unsigned short) idx[v0 + 1];
								out[2] = (unsigned short) idx[v1];
								out[3] = (unsigned short) idx[v1];
								out[4] = (unsigned short) idx[v0 + 1];
								out[5] = (unsigned short) idx[v1 + 1];
							} else {
								out[0] = (unsigned short) idx[v1];
								out[1] = (unsigned short) idx[v0];
								out[2] = (unsigned short) idx[v1 + 1];
								out[3] = (unsigned short) idx[v1 + 1];
								out[4] = (unsigned short) idx[v0];
								out[5] = (unsigned short) idx[v0 + 1];
							}
							out += 6;
							r->n30 += 2;
						}
					}
					r->n24 = count;
				}
				if (r->n28 == 0) {
					m_FreeTracked(r->p00);
					r->p00 = 0;
				}
				r->n24 = count;
			}
		}
	}
	m_FreeTracked(idx);
	m_FreeTracked(cand);
	m_FreeTracked(bestmap);
	m_FreeTracked(map);
}
#pragma optimize("", on)
