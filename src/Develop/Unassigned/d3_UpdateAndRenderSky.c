#include <math.h>

#pragma pack(push, 1)
typedef struct D3_SKY_LAYER_NODE {
	char pad0[4];
	float f4;
	float f8;
	float fc;
	float f10;
	char pad14[0x0c];
	struct D3_SKY_LAYER_NODE* next;
	char pad24[2];
	unsigned char flags26;
	char pad27;
	unsigned char from28;
	unsigned char to29;
	unsigned char cur2a;
	char pad2b[5];
} D3_SKY_LAYER_NODE;
// SIZE 0x30

typedef struct D3_SKY_DOME_STATE {
	char* p0;
	int f4;
	char pad8[4];
	int f_c;
	char pade[0x14];
	D3_SKY_LAYER_NODE* node;
	unsigned long last;
	float dt;
} D3_SKY_DOME_STATE;

typedef struct D3_SKY_DEV D3_SKY_DEV;

typedef struct D3_SKY_DEV_VTBL {
	void* m[50];
	int (__stdcall* SetRenderState)(D3_SKY_DEV*, unsigned int, unsigned int);
	void* m2[0x130 / 4 - 51];
	int (__stdcall* SetVertexShader)(D3_SKY_DEV*, unsigned int);
	void* m3[0x14c / 4 - 0x134 / 4];
	int (__stdcall* SetStreamSource)(D3_SKY_DEV*, unsigned int, void*, unsigned int);
	void* m84;
	int (__stdcall* fn154)(D3_SKY_DEV*, unsigned int, unsigned int);
} D3_SKY_DEV_VTBL;

struct D3_SKY_DEV {
	D3_SKY_DEV_VTBL* vtbl;
};
#pragma pack(pop)

extern char* g_6b5de0;
extern int g_6b86d4;
extern unsigned char g_67a2ac;
extern unsigned char g_6b7ff9;
extern volatile int g_6b7fac;
int __cdecl d3_RebuildSkyDomeMesh(D3_SKY_DOME_STATE*);
void __cdecl d3_RenderSkyLayer(D3_SKY_DOME_STATE*, D3_SKY_LAYER_NODE*);

/* ADDRESS: GOLDTL 0x00459530 */
char __cdecl d3_UpdateAndRenderSky(D3_SKY_DOME_STATE* e)
{
	D3_SKY_LAYER_NODE* n;
	D3_SKY_LAYER_NODE* found;
	float v;
	int from;
	int to;
	int c;
	int arg;

	if (e) {
	if (e->f_c == -1) {
		d3_RebuildSkyDomeMesh(e);
	}
	e->dt = (float) ((unsigned long) g_6b7fac - e->last);
	e->last = (unsigned long) g_6b7fac;
	n = e->node;
	if (n) {
	do {
		v = n->fc + e->dt * n->f10;
		n->fc = v;
		if (v > 1.0) {
			n->f10 = 0;
			n->fc = 1.0f;
		}
		from = n->from28;
		to = n->to29;
		c = (int) ((double) from + ((double) to - (double) from) * n->fc);
		if (c > 0xff) {
			c = 0xff;
		}
		n->cur2a = (unsigned char) c;
		n->f4 = (float) fmod(n->f4 + n->f8 * e->dt, 1.0);
		n = n->next;
	} while (n);
	found = e->node;
	for (n = found->next; n; n = n->next) {
		if (n->cur2a == 0xff && !(n->flags26 & 1) && !(n->flags26 & 2)) {
			found = n;
		}
	}
	if (found && e->f_c > 0 && g_6b86d4 <= 1) {
		((D3_SKY_DEV*) g_6b5de0)->vtbl->SetRenderState((D3_SKY_DEV*) g_6b5de0, 0x88, 0);
		((D3_SKY_DEV*) g_6b5de0)->vtbl->SetRenderState((D3_SKY_DEV*) g_6b5de0, 7, 0);
		((D3_SKY_DEV*) g_6b5de0)->vtbl->SetVertexShader((D3_SKY_DEV*) g_6b5de0, 0x1c4);
		((D3_SKY_DEV*) g_6b5de0)->vtbl->SetStreamSource((D3_SKY_DEV*) g_6b5de0, 0, *(void**) e, 0x20);
		((D3_SKY_DEV*) g_6b5de0)->vtbl->fn154((D3_SKY_DEV*) g_6b5de0, e->f4, 0);
		do {
			d3_RenderSkyLayer(e, found);
			found = found->next;
		} while (found);
		((D3_SKY_DEV*) g_6b5de0)->vtbl->SetRenderState((D3_SKY_DEV*) g_6b5de0, 0x88, 1);
		if (g_67a2ac) {
			arg = (g_6b7ff9 != 0) + 1;
		}
		else {
			arg = 0;
		}
		((D3_SKY_DEV*) g_6b5de0)->vtbl->SetRenderState((D3_SKY_DEV*) g_6b5de0, 7, arg);
	}
	}
	return 1;
	}
	return 0;
}
