#include <string.h>
typedef struct BoxRec {
	char name[0x40];
	float lo[4];
	float hi[4];
} BoxRec;

typedef struct BoxVtx {
	float p[3];
	char padc[0x44];
} BoxVtx;

typedef BoxVtx* (__cdecl* BoxFn)(char* name, char* obj, float* m);

typedef struct Query {
	int count;
	char* list[0x200];
	char path[0x80];
} Query;

extern int g_10058e0;
extern BoxRec* g_10058e4;
extern int g_67a370;

int __cdecl fcn_0065f2f0(const char* a, const char* b, int n);
int __cdecl fcn_0065f220(const char* a, const char* b);
void* __cdecl fcn_0064fde9(void* p, int size);
void __cdecl fcn_004379a0(int, int, int, int (__cdecl*)(), Query*);
int __cdecl fcn_00513d00(char* name, int* list);
char* __cdecl fcn_00439750(int kind, char* name);
void __cdecl fcn_00439aa0(char* o);
char __cdecl fcn_004458e0(char* e, char* parent);
void __cdecl fcn_00438b40(char* o, float* pos);
void __cdecl fcn_00438cb0(char* o, float* rot);
void __cdecl fcn_004442be0(char* o);

/* ADDRESS: GOLDTL 0x00513d40 */
void __cdecl fcn_00513d40(char* name)
{
	char* c;
	char* e;
	char* oo;
	char* o;
	BoxVtx* v;
	int i;
	int j;
	Query q;
	float m[16];

	memset(&q, 0, sizeof(q));
	strcpy(q.path, name);
	fcn_004379a0(g_67a370, 0, 0x1c0, fcn_00513d00, &q);
	if (q.count == 0) {
		return;
	}
	o = q.list[0];
	if (fcn_0065f2f0(name, "bk_", 3) == 0 || fcn_0065f2f0(name, "!bk_", 4) == 0) {
		for (i = 0; i < g_10058e0; i++) {
			if (fcn_0065f220(name, g_10058e4[i].name) == 0) {
				break;
			}
		}
		if (i >= g_10058e0) {
			m[1] = m[2] = m[3] = m[4] = m[6] = m[7] = m[8] = m[9] = m[11] = m[12] = m[13] = m[14] = 0.0f;
			m[0] = m[5] = m[10] = m[15] = 1.0f;
			v = (*(BoxFn*) (*(char**) (*(char**) (o + 0x1cc) + 0x318) + 0x1f0))(o, *(char**) (o + 0x1cc), m);
			g_10058e4 = fcn_0064fde9(g_10058e4, (g_10058e0 + 1) * sizeof(BoxRec));
			strcpy(g_10058e4[g_10058e0].name, name);
			g_10058e4[g_10058e0].lo[0] = v->p[0];
			g_10058e4[g_10058e0].lo[1] = v->p[1];
			g_10058e4[g_10058e0].lo[2] = v->p[2];
			g_10058e4[g_10058e0].hi[0] = v->p[0];
			g_10058e4[g_10058e0].hi[1] = v->p[1];
			g_10058e4[g_10058e0].hi[2] = v->p[2];
			for (i = 1; i < 8; i++) {
				g_10058e4[g_10058e0].lo[0] = (double)v[i].p[0] < (double)g_10058e4[g_10058e0].lo[0] ? v[i].p[0] : g_10058e4[g_10058e0].lo[0];
				g_10058e4[g_10058e0].lo[1] = (double)v[i].p[1] < (double)g_10058e4[g_10058e0].lo[1] ? v[i].p[1] : g_10058e4[g_10058e0].lo[1];
				g_10058e4[g_10058e0].lo[2] = (double)v[i].p[2] < (double)g_10058e4[g_10058e0].lo[2] ? v[i].p[2] : g_10058e4[g_10058e0].lo[2];
				g_10058e4[g_10058e0].hi[0] = (double)v[i].p[0] > (double)g_10058e4[g_10058e0].hi[0] ? v[i].p[0] : g_10058e4[g_10058e0].hi[0];
				g_10058e4[g_10058e0].hi[1] = (double)v[i].p[1] > (double)g_10058e4[g_10058e0].hi[1] ? v[i].p[1] : g_10058e4[g_10058e0].hi[1];
				g_10058e4[g_10058e0].hi[2] = (double)v[i].p[2] > (double)g_10058e4[g_10058e0].hi[2] ? v[i].p[2] : g_10058e4[g_10058e0].hi[2];
			}
			g_10058e0++;
		}
	}
	for (j = 0; j < q.count; j++) {
		e = fcn_00439750(2, name);
		oo = q.list[j];
		fcn_00439aa0(e);
		fcn_004458e0(e, *(char**) (oo + 0x1fc));
		fcn_00438b40(e, (float*) (oo + 0x4c));
		fcn_00438cb0(e, (float*) (oo + 0x84));
		c = *(char**) (oo + 0x200);
		while (c != 0) {
			fcn_004458e0(c, e);
			c = *(char**) (c + 0x1f4);
		}
		fcn_004442be0(oo);
	}
}
