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

void __cdecl d2_SetQuadVertexColor(Quad47bdd0 *q, unsigned char r, unsigned char g,
                          unsigned char b);
int __cdecl d2_QueueScaledQuad(int x, int y, char *sprite, float scale);
Quad47bdd0 *__cdecl d2_QueueTexturedQuad(int x, int y, int w, int h, int tex,
                                 void *src);
Quad47bdd0 *__cdecl d2_QueueClippedTexturedQuad(float u, float v, int w, int h,
                                 Tex47bdd0 *tex, int x, int y);

/* ADDRESS: GOLDTL 0x0047bdd0 */
int __cdecl fcn_0047bdd0(int x, int y, Sprite47bdd0 *sprite, float scale,
                         unsigned char r, unsigned char g, unsigned char b)
{
	Quad47bdd0 *q;
	int tile;
	int whole;
	int count;
	int i;
	int n;
	int off;

	count = sprite->count;
	if (count == 1 && sprite->count2 == 1) {
		q = (Quad47bdd0 *) d2_QueueScaledQuad(x, y, (char *) sprite, scale);
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
				    ((Cell47bdd0 *) ((char *) sprite->cells + off))->u,
				    ((Cell47bdd0 *) ((char *) sprite->cells + off))->v,
				    whole, whole,
				    ((Cell47bdd0 *) ((char *) sprite->cells + off))->tex,
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
