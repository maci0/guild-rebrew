// SIZE 0x60
typedef struct BoxRec {
	char name[0x40];
	float lo[4];
	float hi[4];
} BoxRec;

// SIZE 0x50
typedef struct BoxVtx {
	float p[3];
	char padc[0x44];
} BoxVtx;

typedef BoxVtx* (__cdecl* BoxFn)(char* name, char* obj, float* m);

extern int g_10058e0;
extern BoxRec* g_10058e4;

int __cdecl fcn_0065f2f0(const char* a, const char* b, int n);
int __cdecl fcn_0065f220(const char* a, const char* b);
void* __cdecl fcn_0064fde9(void* p, int size);

/* ADDRESS: GOLDTL 0x004bd1e0 */
char __cdecl fcn_004bd1e0(char* name)
{
	float m[16];
	BoxVtx* v;
	char* d;
	char* obj;
	int i;

	if (fcn_0065f2f0(name, "bk_", 3) != 0 && fcn_0065f2f0(name, "!bk_", 4) != 0) {
		return 1;
	}
	for (i = 0; i < g_10058e0; i++) {
		if (fcn_0065f220(name, g_10058e4[i].name) == 0) {
			return 1;
		}
	}
	obj = *(char**) (name + 0x1cc);
	m[1] = m[2] = m[3] = m[4] = m[6] = m[7] = m[8] = m[9] = m[11] = m[12] = m[13] = m[14] = 0.0f;
	m[0] = m[5] = m[10] = m[15] = 1.0f;
	v = (*(BoxFn*) (*(char**) (obj + 0x318) + 0x1f0))(name, obj, m);
	g_10058e4 = fcn_0064fde9(g_10058e4, (g_10058e0 + 1) * sizeof(BoxRec));
	d = g_10058e4[g_10058e0].name;
	while ((*d++ = *name++) != 0) {
	}
	g_10058e4[g_10058e0].lo[0] = v->p[0];
	g_10058e4[g_10058e0].lo[1] = v->p[1];
	g_10058e4[g_10058e0].lo[2] = v->p[2];
	g_10058e4[g_10058e0].hi[0] = v->p[0];
	g_10058e4[g_10058e0].hi[1] = v->p[1];
	g_10058e4[g_10058e0].hi[2] = v->p[2];
	for (i = 1; i < 8; i++) {
		g_10058e4[g_10058e0].lo[0] = v[i].p[0] < g_10058e4[g_10058e0].lo[0] ? v[i].p[0] : g_10058e4[g_10058e0].lo[0];
		g_10058e4[g_10058e0].lo[1] = v[i].p[1] < g_10058e4[g_10058e0].lo[1] ? v[i].p[1] : g_10058e4[g_10058e0].lo[1];
		g_10058e4[g_10058e0].lo[2] = v[i].p[2] < g_10058e4[g_10058e0].lo[2] ? v[i].p[2] : g_10058e4[g_10058e0].lo[2];
		g_10058e4[g_10058e0].hi[0] = v[i].p[0] > g_10058e4[g_10058e0].hi[0] ? v[i].p[0] : g_10058e4[g_10058e0].hi[0];
		g_10058e4[g_10058e0].hi[1] = v[i].p[1] > g_10058e4[g_10058e0].hi[1] ? v[i].p[1] : g_10058e4[g_10058e0].hi[1];
		g_10058e4[g_10058e0].hi[2] = v[i].p[2] > g_10058e4[g_10058e0].hi[2] ? v[i].p[2] : g_10058e4[g_10058e0].hi[2];
	}
	g_10058e0++;
	return 1;
}
