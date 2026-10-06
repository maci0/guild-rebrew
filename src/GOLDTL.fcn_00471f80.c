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

// FUNCTION: GOLDTL 0x471f80
int __cdecl fcn_00471f80(int slot)
{
	Slot* s;
	char* d;

	s = &((Slot*)g_1015ea0)[slot];
	if (s->type == 0x41) {
		d = s->data;
		if (*(int*) (d + 0x28) & 0x10) {
			return *(int*) (d + 0x14c);
		}
		if (*(int*) (d + 0x28) & 1) {
			return (int) (d + 0x2c);
		}
		if (*(int*) (d + 0x28) & 2) {
			return *(int*) (d + 0x12c);
		}
	}
	if (s->dirty) {
		return s->text;
	}
	if (s->type == 0x45) {
		return (int) s->buf;
	}
	return -1;
}
