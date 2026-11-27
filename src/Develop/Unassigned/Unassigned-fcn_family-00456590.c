#include <string.h>

typedef struct Col {
	unsigned char a;
	unsigned char b;
	unsigned char c0 : 1;
	unsigned char c1 : 1;
	unsigned char c2 : 6;
	unsigned char d;
} Col;

typedef struct Tex {
	int h;
	int* owner;
	int x8;
	unsigned int id;
	char flag;
} Tex;

extern int g_6b89b8;
extern char g_6b89bd;
extern char g_67bcb0[];

void __cdecl d3_ReleaseTexture(int);
int __cdecl d3_CreateTexture(char*, unsigned int, int, int, Col, int, int, char);
typedef struct
{
	int f00;
	int f04;
	unsigned int stamp;
	unsigned int key;
	char b;
	char pad11[0x14 - 0x11];
} D3_SHADOW_TEX_CACHE_SLOT;

extern D3_SHADOW_TEX_CACHE_SLOT* g_6b89b4;
extern unsigned int g_6b89a8;
extern unsigned int g_6b89ac;

int __cdecl d3_BindShadowMapTexture(D3_SHADOW_TEX_CACHE_SLOT* s, int a, char b, unsigned int key, unsigned int stamp);

/* ADDRESS: GOLDTL 0x00456590 */
int __cdecl d3_BindShadowMapTexture(Tex* t, int* owner, char flag, unsigned int id, int x8)
{
	Col c;

	t->x8 = x8;
	owner[3] = (int) t;
	if (t->id > 0 && t->owner != 0) {
		*t->owner = 0;
	}
	t->owner = owner;
	if (t->id != id || t->flag != flag) {
		if (t->h != 0) {
			d3_ReleaseTexture(t->h);
		}
		memset(&c, 0, sizeof(c));
		c.c1 = 1;
		t->id = id;
		t->flag = flag;
		c.a = 0x7f;
		t->h = d3_CreateTexture(g_67bcb0, id, g_6b89b8, g_6b89bd != 0, c, 0, 0, flag);
	}
	return t->h;
}

/* ADDRESS: GOLDTL 0x00456630 */
int __cdecl d3_AcquireCachedShadowTexture(int a, char b, unsigned int key, unsigned int stamp, int unused)
{
	D3_SHADOW_TEX_CACHE_SLOT* s;
	D3_SHADOW_TEX_CACHE_SLOT* best;
	unsigned int i;
	unsigned int bs;

	best = 0;
	bs = stamp;
	s = g_6b89b4;
	for (i = 0; i < g_6b89a8; i++, s++) {
		if (s->key == key && s->b == b && s->stamp < bs) {
			bs = s->stamp;
			best = s;
		}
		if (s->key == 0) {
			return d3_BindShadowMapTexture(s, a, b, key, stamp);
		}
	}
	if (best != 0 && stamp - bs > g_6b89ac) {
		return d3_BindShadowMapTexture(best, a, b, key, stamp);
	}
	best = 0;
	bs = stamp;
	s = g_6b89b4;
	for (i = g_6b89a8; i > 0; i--, s++) {
		if (s->key > 0 && s->b == b && s->stamp < bs) {
			bs = s->stamp;
			best = s;
		}
	}
	if (best != 0 && stamp - bs > 1) {
		return d3_BindShadowMapTexture(best, a, b, key, stamp);
	}
	return 0;
}
