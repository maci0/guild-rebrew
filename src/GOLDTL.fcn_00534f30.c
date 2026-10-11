// FUNCTION: GOLDTL 0x00534f30

// SIZE 0x274
typedef struct {
	char* obj;
	char* next;
	char pad8[0x228 - 8];
	int items[16];
	int cb_a;
	int cb_b;
	char first;
	char count;
	char sound;
	char pad273;
} Pager;

// SIZE 0x2bc
typedef struct {
	char pad0[4];
	char* a;
	char* b;
	char padc[0x114 - 0xc];
	int va;
	int vb;
	char pad11c[0x2bc - 0x11c];
} Item;

extern Item g_10382e0[];
extern int g_7747c4;
extern char g_6a3194[];

void __cdecl fcn_00413120(char* o);
void __cdecl fcn_00442c00(char* o, int v);
void __cdecl fcn_00442be0(char* o);
void __cdecl fcn_00471340(int h);
void __cdecl fcn_00471e30(int h);
void __cdecl fcn_0046b2b0(int h);
void __cdecl fcn_00436f70(int v);
void __cdecl m_FreeTracked(void* p);
void __cdecl fcn_004234e0(int h, char* s, int a, int b, int c, int d, int e);

void __cdecl fcn_00534f30(Pager* p)
{
	char* e;
	int i;
	int j;

	if (p != 0) {
		fcn_00413120(p->obj);
		if (p->next != 0) {
			fcn_00442c00(p->next, 1);
			for (j = 0; j < *(int*) (*(char**) (*(char**) (p->obj + 0x1cc) + 0x318) + 0x1e4); j++) {
				for (i = 0; i < p->count; i++) {
					e = (*(char***) (*(char**) (p->obj + 0x1cc) + 0x31c))[j];
					if (*(int*) (e + 0x50) == *(int*) (g_10382e0[p->items[i]].a + 0x20)) {
						*(int*) (e + 0x50) = g_10382e0[p->items[i]].va;
					} else if (*(int*) (e + 0x50) == *(int*) (g_10382e0[p->items[i]].b + 0x20)) {
						*(int*) (e + 0x50) = g_10382e0[p->items[i]].vb;
					}
				}
			}
			fcn_00442be0(p->obj);
			p->obj = p->next;
		}
		for (i = 0; i < p->count; i++) {
			fcn_00471340(p->items[i]);
			fcn_00471e30(p->items[i]);
		}
		if (p->cb_a != -1) {
			fcn_0046b2b0(p->cb_a);
		}
		if (p->cb_b != -1) {
			fcn_0046b2b0(p->cb_b);
		}
		if (p->sound != 0) {
			fcn_00436f70(1);
		}
		m_FreeTracked(p);
		fcn_004234e0(g_7747c4, g_6a3194, 1, 0x3f, 0x7f, 0, 0);
	}
}
