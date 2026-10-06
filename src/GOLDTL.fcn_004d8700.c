// FUNCTION: GOLD 0x4d70a0
// FUNCTION: GOLDTL 0x4d8700

typedef struct {
	int v[9];
} blk24;
// SIZE 0x24

extern blk24 g_68bef4;

char* __cdecl fcn_004cef30(int);
void __cdecl fcn_00406120(int);
char* __cdecl fcn_00445600(int, int, int, int*);
void __cdecl fcn_004458a0(int, char*, char*);
void __cdecl fcn_00442c00(int, int);
char* __cdecl fcn_0040c120(int, int, int);

void __cdecl fcn_004d8700(int* a)
{
	char* e;
	char* q;
	char* o;
	int h;

	if (a[1] == 0 || a[0] == -1)
		return;
	e = fcn_004cef30(a[0]);
	fcn_00406120(*(int*) (e + 0x184));
	fcn_00445600(0, 0x40, 0, a + 4);
	h = *(int*) (e + 0x1ac);
	if (h != 0) {
		q = *(char**) (*(char**) (e + 0x184) + 0x34);
		fcn_004458a0(h, q + 0x4c, q + 0x18c);
		fcn_00442c00(h, 1);
		*(int*) (e + 0x1ac) = 0;
	}
	o = fcn_0040c120(*(int*) (e + 0x184), 0x2e, 1);
	*(blk24*) (o + 0xf0) = g_68bef4;
}
