

// SIZE 0x70
typedef struct Tex {
	char name[0x40];
	int refs;
	int parent;
	int id;
	void* handle;
	int x50;
	unsigned char flags;
	char pad55[7];
	unsigned char x5c;
	char pad5d[0x13];
} Tex;

extern char* g_104049c;
extern unsigned int g_10404a0;

void __cdecl fcn_0045bfb0(Tex*);

void* __cdecl fcn_0045d320(Tex* t, char all)
{
	void* r;
	unsigned int i;

	if (t == 0) {
		return 0;
	}
	if (t->handle == 0) {
		r = t;
	} else {
		r = t->handle;
		t->handle = 0;
		if (t->id != -1 && t->x5c > 0 && all != 0) {
			for (i = 0; i < g_10404a0; i++) {
				if (((Tex*)g_104049c)[i].refs > 0 && ((Tex*)g_104049c)[i].id == t->id) {
					fcn_0045d320(&((Tex*)g_104049c)[i], 0);
				}
			}
		}
		fcn_0045bfb0(t);
	}
	return r;
}
