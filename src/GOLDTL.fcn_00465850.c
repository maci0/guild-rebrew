typedef struct VfsEntry {
	char name[0x30];
	int offset;
	void* data;
	int size;
	int kind;
	int refs;
	int flags;
	int stamp;
	char pad[8];
} VfsEntry;
// SIZE 0x54

extern VfsEntry* g_772500;
extern int g_772504;
extern int g_772508;
extern int g_6b7fac;

void __cdecl fcn_0047b5d0(void* p);
void __cdecl fcn_0041ddd0(void* p);

// FUNCTION: GOLDTL 0x465850
// SIZE: 200
int __cdecl fcn_00465850(void)
{
	int i;
	int best;
	int stamp;

	best = -1;
	stamp = g_6b7fac;
	for (i = 1; i < g_772504; i++) {
		if (g_772500[i].stamp < stamp && g_772500[i].refs <= 0 && !(g_772500[i].flags & 1) && g_772500[i].data != 0 && g_772500[i].size != 0) {
			stamp = g_772500[i].stamp;
			best = i;
		}
	}
	if (best == -1) {
		return 0;
	}
	if (g_772500[best].kind < 0x10) {
		fcn_0047b5d0(g_772500[best].data);
	} else {
		fcn_0041ddd0(g_772500[best].data);
		g_772500[best].data = 0;
	}
	g_772500[best].data = 0;
	g_772508 -= g_772500[best].size;
	return 1;
}
