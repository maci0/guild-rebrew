

// SIZE 0x70
typedef struct Tex {
	char name[0x40];
	int refs;
	int parent;
	int id;
	int pad4c;
	int x50;
	unsigned char flags;
	char pad55[0xf];
	int x64;
	int x68;
	int pad6c;
} Tex;

extern char* g_104049c;
extern unsigned int g_10404a0;

void __cdecl fcn_0045ce20(Tex* t)
{
	Tex* list;
	int idx;
	unsigned int i;

	if ((t->flags & 2) == 0 && t->name[0] != '*') {
		idx = t - ((Tex*)g_104049c);
		list = ((Tex*)g_104049c);
		for (i = 0; i < g_10404a0; i++) {
			if (list[i].refs > 0 && (list[i].flags & 2) != 0 && list[i].parent == idx) {
				list[i].x50 = t->x50;
				list[i].x64 = t->x64;
				list[i].x68 = t->x68;
			}
		}
	}
}
