typedef struct
{
	int x0;
	int w;
	int h;
	char padc[0x14];
	int x20;
} fcn_0046dd60_Surf;

typedef struct
{
	char pad0[0x50];
	int color;
} fcn_0046dd60_Pal;

typedef struct
{
	char pad0[0x50];
	short w;
	short h;
} fcn_0046dd60_Def;
// SIZE 0x54

// SIZE 0x3cc
typedef struct
{
	int pad0;
	int x;
	int y;
	int w;
	int h;
	int flags;
	char pad18[0x38 - 0x18];
	fcn_0046dd60_Surf* surf;
	char pad3c[0x258 - 0x3c];
	int sy;
	char pad25c[0x268 - 0x25c];
	int sx;
	char pad26c[0x398 - 0x26c];
	int tex;
	char pad39c[4];
	fcn_0046dd60_Pal* pal;
	float alpha;
	int ml;
	int mt;
	int mr;
	int mb;
	char pad3b8[0x3c8 - 0x3b8];
	int img;
} fcn_0046dd60_Win;

extern fcn_0046dd60_Surf* g_77256c;
extern fcn_0046dd60_Pal* g_77253c;
extern fcn_0046dd60_Def* g_772500;
extern int g_7725f8;
extern int g_7725fc;
extern int g_67d964;
extern int g_67d968;

void* __cdecl fcn_0047bf80(int x, int y, int w, int h, int a5, void* r);
void __cdecl fcn_0047b9a0(void* p, int r, int g, int b);
void __cdecl fcn_0047c9c0(int x, int y, int w, int h, int color, float alpha);
void __cdecl fcn_0047cb60(int x, int y, int a3, int img);
int __cdecl fcn_00466190(int id);
void __cdecl fcn_0047a040(int a, int b, int c, int d);
void __cdecl fcn_0047cba0(int x, int y, int surf, int tex, int c);
void __cdecl fcn_0047c7b0(int x, int y, int w, int h, int bits, float alpha);

// FUNCTION: GOLDTL 0x0046dd60
// SIZE: 646
void __cdecl fcn_0046dd60(fcn_0046dd60_Win* w, int dst)
{
	void* p;
	fcn_0046dd60_Def* d;
	int tex;
	int x0;
	int y0;
	int cw;
	int ch;
	int s1;
	int s2;
	int s3;
	int s4;
	int oy;
	int i;
	int rows;

	if (w->flags & 0x400) {
		p = fcn_0047bf80(w->x, w->y, w->w, w->h, g_77256c->x20, 0);
		if (p != 0)
			fcn_0047b9a0(p, 0, 0, 0);
	}
	x0 = w->ml + w->x;
	y0 = w->mt + w->y;
	cw = w->w - w->mr - w->ml;
	ch = w->h - w->mb - w->mt;
	if (w->flags & 1)
		fcn_0047c9c0(x0, y0, cw, ch, g_77253c->color, w->alpha);
	else if (w->pal != 0)
		fcn_0047c9c0(x0, y0, cw, ch, w->pal->color, w->alpha);
	else if (w->img != 0)
		fcn_0047cb60(w->x - w->sx, w->y - w->sy, dst, w->img);
	if (w->tex != -1 && (tex = fcn_00466190(w->tex)) != 0) {
		s1 = g_7725f8;
		s2 = g_7725fc;
		s3 = g_67d964;
		s4 = g_67d968;
		fcn_0047a040(w->x, w->y, w->w + w->x, w->h + w->y);
		d = &g_772500[w->tex];
		if (w->sy >= 0)
			oy = w->y - w->sy % d->h;
		else
			oy = w->y - w->sy % d->h - d->h;
		for (rows = 0; rows < w->h / d->h + 1.5; rows++) {
			for (i = 0; i < w->w / d->w; i++)
				fcn_0047cba0(w->x + d->w * i, d->h * rows + oy, dst, tex, 0);
		}
		fcn_0047a040(s1, s2, s3, s4);
	}
	if (w->surf != 0)
		fcn_0047c7b0(w->x, w->y, w->surf->w, w->surf->h, w->surf->x20, 1.0f);
}
