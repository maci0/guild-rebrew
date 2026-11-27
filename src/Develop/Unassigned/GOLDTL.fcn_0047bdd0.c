typedef struct {
	float x;
	float y;
	float z;
	float rhw;
	unsigned int color;
	float u;
	float v;
} D2_VERTEX;

typedef struct {
	D2_VERTEX v[6];
	int tex;
} D2_QUAD;

typedef struct {
	char pad_0[0x20];
	int handle;
	char pad_24[0x54 - 0x24];
	int size;
} D2_TEX;

typedef struct {
	unsigned short field_0;
	unsigned short tile;
	char pad_4[0x24 - 4];
	int count;
	int **lists;
	int count2;
	int *cells;
	int size;
} D2_SPRITE;

typedef struct {
	float u;
	float v;
	D2_TEX *tex;
} D2_SPRITE_CELL;

void __cdecl d2_SetQuadVertexColor(D2_QUAD *q, unsigned char r, unsigned char g,
                          unsigned char b);
int __cdecl d2_QueueScaledQuad(int x, int y, char *sprite, float scale);
D2_QUAD *__cdecl d2_QueueTexturedQuad(int x, int y, int w, int h, int tex,
                                 void *src);
D2_QUAD *__cdecl d2_QueueClippedTexturedQuad(float u, float v, int w, int h,
                                 D2_TEX *tex, int x, int y);

/* ADDRESS: GOLDTL 0x0047bdd0 */
int __cdecl d2_DrawTintedSprite(int x, int y, D2_SPRITE *sprite, float scale,
                         unsigned char r, unsigned char g, unsigned char b)
{
	D2_QUAD *q;
	int tile;
	int whole;
	int count;
	int i;
	int n;
	int off;

	count = sprite->count;
	if (count == 1 && sprite->count2 == 1) {
		q = (D2_QUAD *) d2_QueueScaledQuad(x, y, (char *) sprite, scale);
		if (q)
			d2_SetQuadVertexColor(q, r, g, b);
		return (int) q;
	}
	whole = sprite->size;
	if (whole >= *(int *) ((char *) *sprite->lists + 4)) {
		tile = *(int *) ((char *) *sprite->lists + 4);
		n = (int) ((float) sprite->tile / (float) tile + 0.99f);
		i = 0;
		if (count > 0) {
			do {
				q = d2_QueueTexturedQuad(
				    (i % n) * tile + x, (i / n) * tile + y, tile,
				    tile, *(int *) ((char *) sprite->lists[i] + 0x20),
				    0);
				if (q)
					d2_SetQuadVertexColor(q, r, g, b);
				i++;
			} while (i < sprite->count);
			return (int) q;
		}
	} else {
		n = (int) ((float) sprite->tile / (float) whole + 0.99f);
		i = 0;
		if (sprite->count2 > 0) {
			off = 0;
			do {
				whole = sprite->size;
				q = d2_QueueClippedTexturedQuad(
				    ((D2_SPRITE_CELL *) ((char *) sprite->cells + off))->u,
				    ((D2_SPRITE_CELL *) ((char *) sprite->cells + off))->v,
				    whole, whole,
				    ((D2_SPRITE_CELL *) ((char *) sprite->cells + off))->tex,
				    (i % n) * whole + x, (i / n) * whole + y);
				if (q)
					d2_SetQuadVertexColor(q, r, g, b);
				i++;
				off += 0xc;
			} while (i < sprite->count2);
			return (int) q;
		}
	}
	return y;
}
