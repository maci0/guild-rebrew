extern double g_6628f0;
extern double g_664088;
typedef struct Seg {
	unsigned int offset;
	unsigned int count;
} Seg;

typedef struct Row {
	unsigned int seg_count;
	Seg segs[1];
} Row;

typedef struct Block {
	char pad_000[0x0a];
	unsigned short row_count;
	char pad_00c[0x32 - 0x0c];
	Row rows[1];
} Block;

typedef struct Surf16 {
	char pad_000[0x10];
	int pitch;
	char pad_014[0x1c - 0x14];
	unsigned short* bits;
} Surf16;

void __cdecl fcn_0041bb70(int, unsigned char*, unsigned char*, unsigned char*);
short __cdecl fcn_0041bac0(int, int, int);


/* ADDRESS: GOLDTL 0x00478d50 */
void __cdecl fcn_00478d50(int x, int y, Surf16* s, Block* b)
{
	unsigned short* base;
	Row* r;
	int i;
	unsigned char cb;
	int v;
	unsigned char cr;
	unsigned char cg;
	unsigned short* p;
	Seg* seg;
	unsigned int j;
	unsigned int k;

	base = s->bits + (y * s->pitch + x);
	r = (Row*) ((char*) b + 0x32);
	seg = (Seg*) ((char*) r + 4);
	for (i = 0; i < b->row_count; i++) {
		p = base;
		for (j = 0; j < r->seg_count; j++) {
			p += seg->offset >> 1;
			for (k = 0; k < seg->count; k++) {
				fcn_0041bb70(((unsigned short*) (seg + 1))[k], &cb, &cg, &cr);
				v = (int) (((double) cr + (double) cb) * g_6628f0 + (double) cg * g_664088);
				*p = fcn_0041bac0(v, v, v);
				p++;
			}
			seg = (Seg*) ((char*) (seg + 1) + seg->count * 2);
		}
		base += s->pitch;
		r = (Row*) seg;
		seg = (Seg*) ((char*) r + 4);
	}
}
