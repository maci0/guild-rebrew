// FUNCTION: GOLDTL 0x45c310
// SIZE: 101

// SIZE 0x70
typedef struct Tex {
	char name[0x40];
	int refs;
	int pad44;
	int id;
	char pad[0x24];
} Tex;

extern char* g_104049c;
extern unsigned int g_10404a0;

void __cdecl fcn_0045c310(Tex* t, char all)
{
	unsigned int i;
	Tex* list;

	if (t == 0) {
		return;
	}
	if (all != 0 && *(int*) ((char*) t + 0x5c) > 0 && ((char*) t)[0x5d] == 0 && t->id != -1) {
		list = ((Tex*)g_104049c);
		for (i = 0; i < g_10404a0; i++) {
			if (list[i].refs > 0 && list[i].id == t->id) {
				list[i].refs++;
			}
		}
		return;
	}
	t->refs++;
}
