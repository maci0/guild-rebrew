typedef struct Slot {
	int id;
	int used;
	int value;
	char* data;
	int x;
	int y;
	int w;
	int h;
	int type;
	char pad24[0x38 - 0x24];
	int text;
	char pad3c[0x48 - 0x3c];
	int hidden;
	char pad4c[0x58 - 0x4c];
	int dirty;
	char pad5c[0x88 - 0x5c];
	int result;
	char* buf;
	char pad90[0x2f4 - 0x90];
} Slot;
// SIZE 0x2f4

extern char* g_1015ea0;

char* __cdecl fcn_00466190(int idx);

// FUNCTION: GOLDTL 0x472050
// SIZE: 163
int __cdecl fcn_00472050(int slot, int* w, int* h)
{
	Slot* s;
	char* f;
	char* g;

	if (slot != -1) {
		s = &((Slot*)g_1015ea0)[slot];
		if (s->type == 1 || s->type == 8 || s->type == 5) {
			f = fcn_00466190(s->value);
			if (f) {
				if (s->type != 8 && s->type != 5) {
					*w = *(unsigned short*) (f + 6);
					*h = *(unsigned short*) (f + 8);
					return 1;
				}
				g = ((char**) *(char**) (f + 0x18))[s->result];
				if (g) {
					*w = *(unsigned short*) (g + 2);
					*h = *(unsigned short*) (g + 6);
				}
				return 1;
			}
		}
	}
	return 0;
}
