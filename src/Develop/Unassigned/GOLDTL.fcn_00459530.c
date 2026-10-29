#include <math.h>

#pragma pack(push, 1)
typedef struct Node459 {
	char pad0[4];
	float f4;
	float f8;
	float fc;
	float f10;
	char pad14[0x0c];
	struct Node459* next;
	char pad24[2];
	unsigned char flags26;
	char pad27;
	unsigned char from28;
	unsigned char to29;
	unsigned char cur2a;
	char pad2b[5];
} Node459;
// SIZE 0x30

typedef struct Ent459 {
	char* p0;
	int f4;
	char pad8[4];
	int f_c;
	char pade[0x14];
	Node459* node;
	unsigned long last;
	float dt;
} Ent459;

typedef struct Dev459 Dev459;

typedef struct Vtbl459 {
	void* m[50];
	int (__stdcall* SetRenderState)(Dev459*, unsigned int, unsigned int);
	void* m2[0x130 / 4 - 51];
	int (__stdcall* SetVertexShader)(Dev459*, unsigned int);
	void* m3[0x14c / 4 - 0x134 / 4];
	int (__stdcall* SetStreamSource)(Dev459*, unsigned int, void*, unsigned int);
	void* m84;
	int (__stdcall* fn154)(Dev459*, unsigned int, unsigned int);
} Vtbl459;

struct Dev459 {
	Vtbl459* vtbl;
};
#pragma pack(pop)

extern char* g_6b5de0;
extern int g_6b86d4;
extern unsigned char g_67a2ac;
extern unsigned char g_6b7ff9;

int __cdecl fcn_00459050(Ent459*);
void __cdecl fcn_00458e00(Ent459*, Node459*);

/* ADDRESS: GOLDTL 0x00459530 */
char __cdecl fcn_00459530(Ent459* e)
{
	Node459* n;
	Node459* found;
	float v;
	int from;
	int to;
	int c;
	int arg;

	if (e) {
	if (e->f_c == -1) {
		fcn_00459050(e);
	}
	e->dt = (float) (*(unsigned long*) 0x6b7fac - e->last);
	e->last = *(unsigned long*) 0x6b7fac;
	n = e->node;
	if (!n) {
		return 1;
	}
	do {
		v = n->fc + e->dt * n->f10;
		n->fc = v;
		if (v > 1.0) {
			n->f10 = 0;
			n->fc = 1.0f;
		}
		from = n->from28;
		to = n->to29;
		c = (int) (from + (to - from) * v);
		if (c > 0xff) {
			c = 0xff;
		}
		n->cur2a = (unsigned char) c;
		n->f4 = (float) fmod(n->f4 + n->f8 * e->dt, 1.0);
		n = n->next;
	} while (n);
	found = e->node;
	for (n = found->next; n; n = n->next) {
		if (n->cur2a == 0xff && !(n->flags26 & 3)) {
			found = n;
		}
	}
	if (found && e->f_c > 0 && g_6b86d4 <= 1) {
		((Dev459*) g_6b5de0)->vtbl->SetRenderState((Dev459*) g_6b5de0, 0x88, 0);
		((Dev459*) g_6b5de0)->vtbl->SetRenderState((Dev459*) g_6b5de0, 7, 0);
		((Dev459*) g_6b5de0)->vtbl->SetVertexShader((Dev459*) g_6b5de0, 0x1c4);
		((Dev459*) g_6b5de0)->vtbl->SetStreamSource((Dev459*) g_6b5de0, 0, *(void**) e, 0x20);
		((Dev459*) g_6b5de0)->vtbl->fn154((Dev459*) g_6b5de0, e->f4, 0);
		do {
			fcn_00458e00(e, found);
			found = found->next;
		} while (found);
		((Dev459*) g_6b5de0)->vtbl->SetRenderState((Dev459*) g_6b5de0, 0x88, 1);
		if (g_67a2ac) {
			arg = (g_6b7ff9 != 0) + 1;
		}
		else {
			arg = 0;
		}
		((Dev459*) g_6b5de0)->vtbl->SetRenderState((Dev459*) g_6b5de0, 7, arg);
	}
	return 1;
	}
	return 0;
}
