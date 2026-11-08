void __cdecl fcn_00469c40(int, int, int);
#include "client_types.h"
typedef Obj_1038140 Obj;

extern Obj_1038140 g_1038140[];

void __cdecl fcn_00471c80(int win, int flags);
extern char* g_1015ea0;
extern int g_772534;
extern Win_1015f40 g_1015f40[0x60];
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

int __cdecl fcn_00471f80(int id);

/* ADDRESS: GOLDTL 0x00471c80 */
void __cdecl fcn_00471c80(int idx, unsigned char flags, float limit)
{
	int* p;
	float value;
	float bound;
	int t;

	p = (int*) (0x1015f40 + idx * 0x3cc);
	if (flags & 1) {
		t = p[3] / 2;
		value = (float) (p[1] + t)
			- (float) *(int*) 0x1015eac / *(float*) 0x67d368
			+ (float) *(int*) 0x1015eac - (float) t;
	} else {
		value = (float) p[1];
	}
	if (flags & 2) {
		bound = (float) (p[2] + p[4] / 2) * *(float*) 0x67d368 - (float) (p[4] / 2);
	} else {
		bound = (float) p[2];
	}
	t = *(int*) 0x1040494 - p[3];
	if ((float) t < value) {
		value = (float) t;
	}
	t = *(int*) 0x1040490 - p[4];
	if ((float) t < bound) {
		bound = (float) t;
	}
	fcn_00469c40((int) value, (int) bound, *(int*) ((char*) p + 0x27c));
}

/* ADDRESS: GOLDTL 0x00471d80 */
void __cdecl fcn_00471d80(int k, int flags)
{
	fcn_00471c80(g_1038140[k].wins[0], flags);
}

/* ADDRESS: GOLDTL 0x00471ee0 */
void __cdecl fcn_00471ee0(int i, int v)
{
	*(int*) (g_1015ea0 + (*(int*) (((char*)g_1038140) + g_772534 * 0x2bc + 0x194) + i) * 0x2f4 + 0x38) = v;
}

/* ADDRESS: GOLDTL 0x00471f20 */
char* __cdecl fcn_00471f20(int j, int k)
{
	char* m;

	m = ((char*)g_1015f40) + ((int*) (((char*)g_1038140) + g_772534 * 0x2bc + 4))[k] * 0x3cc;
	if (j > *(int*) (m + 0x2c)) {
		return 0;
	}
	return g_1015ea0 + (*(int**) (m + 0x28))[j] * 0x2f4;
}

/* ADDRESS: GOLDTL 0x00471f80 */
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

/* ADDRESS: GOLDTL 0x00471ff0 */
int __cdecl fcn_00471ff0(int j, int k)
{
	char* m;

	m = ((char*)g_1015f40) + ((int*) (((char*)g_1038140) + g_772534 * 0x2bc + 4))[k] * 0x3cc;
	if (j > *(int*) (m + 0x2c)) {
		return 0;
	}
	return fcn_00471f80((*(int**) (m + 0x28))[j]);
}
