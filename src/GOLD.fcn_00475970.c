// FUNCTION: GOLD 0x00475970
// SIZE: 105

typedef struct Slot00475970 {
	char pad0[0xc];
	char* data;
	char pad10[0x18 - 0x10];
	int type;
	char pad1c[0x28 - 0x1c];
	int text;
	char pad2c[0x48 - 0x2c];
	int dirty;
	char pad4c[0x7c - 0x4c];
	char* buf;
	char pad80[0x2ec - 0x80];
} Slot00475970;
// SIZE 0x2ec

extern Slot00475970* g_00f8f080; /* 0x00f8f080 */

int __cdecl fcn_00475970(int slot)
{
	Slot00475970* s;
	char* d;

	s = &g_00f8f080[slot];
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
