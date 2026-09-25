typedef struct
{
	int used;
	char pad04[0x1f4 - 0x4];
} fcn_00459d90_Cell;
// SIZE 0x1f4

typedef struct
{
	int obj;
	char pad04[0x158 - 0x4];
} fcn_00459d90_Part;
// SIZE 0x158

typedef struct
{
	int size;
	int size2;
	char pad08[0x10 - 0x8];
	int f10;
	int f14;
	int f18;
	int f1c;
	int pad20;
	int mips[3];
	char pad30[0x258 - 0x30];
	fcn_00459d90_Cell cells[8][8];
	char pad7f58[0x8035 - 0x7f58];
	unsigned char nparts;
} fcn_00459d90_Tex;
// SIZE 0x8038

#define PARTS(t) (*(fcn_00459d90_Part**) ((char*) (t) + 0x7da0))

void __cdecl fcn_00459be0(int a);
int __cdecl fcn_00459d00(int obj, int flag);

// FUNCTION: GOLDTL 0x459d90
// SIZE: 262
int __cdecl fcn_00459d90(fcn_00459d90_Tex* t, char flag)
{
	int r;
	int sq;
	int i;
	int j;
	int s;

	r = 0;
	if (t != 0) {
		sq = t->size * t->size;
		if (flag) {
			fcn_00459be0(0x14);
		}
		r = 0x8038;
		if (t->f10 != 0) {
			r = sq + 0x8038;
		}
		if (t->f14 != 0) {
			r += sq;
		}
		if (t->f18 != 0) {
			r += sq;
		}
		if (t->f1c != 0) {
			r += sq;
		}
		for (i = 0; i < 3; i++) {
			if (t->mips[i] != 0) {
				s = t->size >> i;
				r += s * s;
			}
		}
		if (PARTS(t) != 0) {
			r += t->nparts * sizeof(fcn_00459d90_Part);
			for (i = 0; i < t->nparts; i++) {
				if (PARTS(t)[i].obj != 0) {
					r += fcn_00459d00(PARTS(t)[i].obj, 1);
				}
			}
		}
		for (i = 0; i < 8; i++) {
			for (j = 0; j < 8; j++) {
				if (t->cells[i][j].used != 0) {
					r += t->size2 * t->size2 / 2 * 20;
				}
			}
		}
	}
	return r;
}
