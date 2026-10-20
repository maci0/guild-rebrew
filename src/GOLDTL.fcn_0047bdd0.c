typedef struct {
	float x;
	float y;
	float z;
	float rhw;
	unsigned int color;
	float u;
	float v;
} Vtx47bdd0;

typedef struct {
	Vtx47bdd0 v[6];
	int tex;
} Quad47bdd0;

typedef struct {
	char pad_0[0x20];
	int handle;
	char pad_24[0x54 - 0x24];
	int size;
} Tex47bdd0;

typedef struct {
	unsigned short field_0;
	unsigned short tile;
	char pad_4[0x24 - 4];
	int count;
	int **lists;
	int count2;
	int *cells;
	int size;
} Sprite47bdd0;

typedef struct {
	float u;
	float v;
	Tex47bdd0 *tex;
} Cell47bdd0;

void __cdecl fcn_0047b9a0(Quad47bdd0 *q, unsigned char r, unsigned char g,
                          unsigned char b);
int __cdecl fcn_0047ba20(int x, int y, char *sprite, float scale);
Quad47bdd0 *__cdecl fcn_0047bf80(int x, int y, int w, int h, int tex,
                                 void *src);
Quad47bdd0 *__cdecl fcn_0047c1f0(float u, float v, int w, int h,
                                 Tex47bdd0 *tex, int x, int y);

/* ADDRESS: GOLDTL 0x0047bdd0 */
int __cdecl fcn_0047bdd0(int x, int y, Sprite47bdd0 *sprite, float scale,
                         unsigned char r, unsigned char g, unsigned char b)
{
	Quad47bdd0 *q;
	Cell47bdd0 *cell;
	int tile;
	int whole;
	int i;
	int n;
	int off;

	if (sprite->count == 1 && sprite->count2 == 1) {
		q = (Quad47bdd0 *) fcn_0047ba20(x, y, (char *) sprite, scale);
		if (!q)
			return (int) q;
		fcn_0047b9a0(q, r, g, b);
		return (int) q;
	}
	whole = sprite->size;
	tile = *(int *) ((char *) *sprite->lists + 4);
	if (whole >= tile) {
		n = (int) ((float) sprite->tile / (float) tile + 0.5f);
		i = 0;
		if (sprite->count >= 1) {
			do {
				q = fcn_0047bf80(
				    (i % n) * tile + x, (i / n) * tile + y, tile,
				    tile, *(int *) ((char *) sprite->lists[i] + 0x20),
				    0);
				if (q)
					fcn_0047b9a0(q, r, g, b);
				i++;
			} while (i < sprite->count);
			return (int) q;
		}
	} else {
		n = (int) ((float) sprite->tile / (float) tile + 0.5f);
		i = 0;
		off = 0;
		if (sprite->count2 >= 1) {
			do {
				cell = (Cell47bdd0 *) ((char *) sprite->cells + off);
				q = fcn_0047c1f0(
				    cell->u, cell->v, tile, tile, cell->tex,
				    (i % n) * tile + x, (i / n) * tile + y);
				if (q)
					fcn_0047b9a0(q, r, g, b);
				i++;
				off += 0xc;
			} while (i < sprite->count2);
			return (int) q;
		}
	}
	return y;
}
