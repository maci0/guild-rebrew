// FUNCTION: GOLDTL 0x005166a0
// SIZE: 273
// FUNCTION: GOLD 0x00512f60
// SIZE: 273

// SIZE 0x6c4
typedef struct {
	int key;
	char names[16][48];
	char pad304[0x6c4 - 0x304];
} NameSet;

// SIZE 0x21c
typedef struct {
	char pad0[0x16c];
	unsigned char* home;
	char pad170[0x184 - 0x170];
	char* view;
	char pad188[0x21c - 0x188];
} Obj;

extern NameSet g_699b18[];
extern char g_7f4ca0[];
extern unsigned char* g_868050;

void __cdecl fcn_00530a00(unsigned char* home);
void __cdecl fcn_00404a00(char* view, int n, ...);

void __cdecl fcn_005166a0(unsigned char* home)
{
	NameSet* s;
	int k;
	unsigned char* rec;
	int i;

	rec = (unsigned char*) ((char*)g_868050) + *home * 589;
	for (k = 0; g_699b18[k].key != 0; k++) {
		if (g_699b18[k].key == *rec) {
			break;
		}
	}
	s = &g_699b18[k];
	fcn_00530a00(home);
	for (i = 0; i < 768; i++) {
		if (((Obj*)g_7f4ca0)[i].view != 0 &&
		    (((Obj*)g_7f4ca0)[i].home == home || *(int*) (((Obj*)g_7f4ca0)[i].view + 0x2c) == *(int*) (home + 1))) {
			fcn_00404a00(((Obj*)g_7f4ca0)[i].view, 0x10, s->names[0], s->names[1], s->names[2], s->names[3],
				     s->names[4], s->names[5], s->names[6], s->names[7], s->names[8], s->names[9],
				     s->names[10], s->names[11], s->names[12], s->names[13], s->names[14],
				     s->names[15]);
		}
	}
}
