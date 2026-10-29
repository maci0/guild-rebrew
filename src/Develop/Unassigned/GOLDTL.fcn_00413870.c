/* Terrain height probe: converts three map points to cell coordinates,
 * sorts them by row, then walks every scanline between them through
 * fcn_004137e0 while keeping the lowest and highest terrain height.  Each
 * early guard bails out with 1; on success the two float outputs carry the
 * height range scaled back through the tile map. */

typedef struct GOLDTL_TileMap {
	int stride;                 /* 0x00, cells per row */
	char pad_04[0x0c];
	unsigned char* cells;       /* 0x10 */
	char pad_14[0x3c];
	float base_x;               /* 0x50 */
	float base_y;               /* 0x54 */
	float base_z;               /* 0x58 */
	char pad_5c[0x04];
	float cell_x;               /* 0x60 */
	char pad_64[0x14];
	float cell_z;               /* 0x78 */
	char pad_7c[0x08];
	float height_scale;         /* 0x84 */
} GOLDTL_TileMap;

extern float g_6628a0;

int __cdecl fcn_004137e0(GOLDTL_TileMap* m, int* lo, int* hi, int x0, int x1,
	int y);

/* ADDRESS: GOLDTL 0x00413870 */
int __cdecl fcn_00413870(void* obj, void* a, void* b, void* c, void* d,
	void* e)
{
	GOLDTL_TileMap* map;
	float* hi_out;
	float* lo_out;
	float* p1;
	float* p2;
	float* p3;
	float sx;
	float sy;
	float dx;
	float slope_a;
	float slope_b;
	float slope_c;
	float left;
	float right;
	int ax;
	int ay;
	int bx;
	int by;
	int cx;
	int cy;
	int x;
	int y;
	int lo;
	int hi;
	int hit;
	int t;

	map = (GOLDTL_TileMap*) obj;
	lo_out = (float*) a;
	hi_out = (float*) b;
	p1 = (float*) c;
	p2 = (float*) d;
	p3 = (float*) e;

	sx = g_6628a0 / map->cell_x;
	ax = (int) ((p1[0] - map->base_x) * sx);
	sy = g_6628a0 / map->cell_z;
	ay = (int) ((p1[2] - map->base_z) * sy);
	bx = (int) ((p2[0] - map->base_x) * sx);
	by = (int) ((p2[2] - map->base_z) * sy);
	cx = (int) ((p3[0] - map->base_x) * sx);
	cy = (int) ((p3[2] - map->base_z) * sy);

	/* order the three points by row, carrying their column along */
	if (ay > by) {
		t = ax;
		ax = bx;
		bx = t;
		t = ay;
		ay = by;
		by = t;
	}
	if (ay > cy) {
		t = ax;
		ax = cx;
		cx = t;
		t = ay;
		ay = cy;
		cy = t;
	}
	if (by > cy) {
		t = bx;
		bx = cx;
		cx = t;
		t = by;
		by = cy;
		cy = t;
	}

	if (ay >= map->stride) {
		return 1;
	}
	if (cy < 0) {
		return 1;
	}
	if (ax < 0 && bx < 0 && cx < 0) {
		return 1;
	}
	if (ax >= map->stride && bx >= map->stride && cx >= map->stride) {
		return 1;
	}

	lo = 0xff;
	hi = 0;
	if (ay != by) {
		/* general triangle: the top row collapses to the apex */
		slope_a = (float) (cx - ax) / (float) (cy - ay);
		slope_b = (float) (bx - ax) / (float) (by - ay);
		hit = 1;
		left = (float) ax;
		right = left;
		for (y = ay; y <= by; y++) {
			hit &= fcn_004137e0(map, &lo, &hi, (int) left, (int) right, y);
			left += slope_a;
			right += slope_b;
		}
		slope_c = (float) (cx - bx) / (float) (cy - by);
		right = (float) bx - slope_c;
		for (y = by + 1; y <= cy; y++) {
			hit &= fcn_004137e0(map, &lo, &hi, (int) left, (int) right, y);
			left += slope_a;
			right += slope_c;
		}
	} else if (ay != cy) {
		/* flat top: both sides fall at the same rate */
		hit = fcn_004137e0(map, &lo, &hi, ax, bx, ay);
		dx = (float) (cx - ax);
		slope_a = dx / (float) (cy - ay);
		slope_b = dx / (float) (cy - by);
		left = (float) ax + slope_a;
		right = (float) bx + slope_b;
		for (y = ay + 1; y <= cy; y++) {
			hit &= fcn_004137e0(map, &lo, &hi, (int) left, (int) right, y);
			left += slope_a;
			right += slope_b;
		}
	} else {
		/* one row: a single span from the leftmost to the rightmost x */
		t = ax < bx ? ax : bx;
		x = t < cx ? t : cx;
		t = ax > bx ? ax : bx;
		t = t > cx ? t : cx;
		hit = fcn_004137e0(map, &lo, &hi, x, t, ay);
	}

	if (hit != 0) {
		return hit;
	}
	*lo_out = (float) lo * map->height_scale + map->base_y;
	*hi_out = (float) hi * map->height_scale + map->base_y;
	return 0;
}
