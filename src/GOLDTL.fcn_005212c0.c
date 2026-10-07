// FUNCTION: GOLD 0x51c320
// FUNCTION: GOLDTL 0x005212c0

// SIZE 0x114
typedef struct {
	int id;
	char pad4[4];
	char b8;
	char pad9[3];
	int xc;
	char pad10[4];
	int x14;
	char stamp[0xe];
	char b26;
	char pad27[9];
	char b30;
	char pad31[3];
	int x34[16];
	char b74;
	char pad75[7];
	char x7c[0x98];
} Rec;

extern char g_9a9660[];

unsigned int __cdecl fcn_00430910(void* p, int size, int n, int f);

int __cdecl fcn_005212c0(int f)
{
	int count;
	int i;
	Rec* p;

	count = 0;
	for (i = 0; i < 96; i++) {
		if (((Rec*)g_9a9660)[i].id != -1) {
			count++;
		}
	}
	if (fcn_00430910(&count, 4, 1, f) <= 0) {
		return 0;
	}
	for (i = 0; i < 96; i++) {
		p = &((Rec*)g_9a9660)[i];
		if (p->id == -1) {
			continue;
		}
		if (fcn_00430910(&p->id, 4, 1, f) <= 0) {
			return 0;
		}
		if (fcn_00430910(&p->b8, 1, 1, f) <= 0) {
			return 0;
		}
		if (fcn_00430910(&p->x14, 4, 1, f) <= 0) {
			return 0;
		}
		if (fcn_00430910(&p->b26, 1, 1, f) <= 0) {
			return 0;
		}
		if (fcn_00430910(&p->b30, 1, 1, f) <= 0) {
			return 0;
		}
		if (fcn_00430910(p->x34, 4, 0x10, f) <= 0) {
			return 0;
		}
		if (fcn_00430910(&p->b74, 1, 1, f) <= 0) {
			return 0;
		}
		if (fcn_00430910(p->x7c, 0x98, 1, f) <= 0) {
			return 0;
		}
		if (fcn_00430910(p->stamp, 0xe, 1, f) <= 0) {
			return 0;
		}
		if (fcn_00430910(&p->xc, 4, 1, f) <= 0) {
			return 0;
		}
	}
	return 1;
}
