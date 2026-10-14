

typedef struct {
	int v[9];
} blk24;
// SIZE 0x24

extern blk24 g_68bef4;

char* __cdecl fcn_004cef30(int);
void __cdecl fcn_00406120(int);
char* __cdecl fcn_00445600(int, int, int, int*);
char* __cdecl fcn_0040c230(int, void*, int, int, int);
void __cdecl fcn_004d4ee0(void);

void __cdecl fcn_004d8660(int* a)
{
	char* e;
	unsigned short* s;
	char* p;
	char* o;

	if (a[1] == 0 || a[0] == -1)
		return;
	e = fcn_004cef30(a[0]);
	s = *(unsigned short**) (e + 0x16c);
	fcn_00406120(*(int*) (e + 0x184));
	p = fcn_00445600(0, 0x40, 0, a + 4);
	if (p == 0)
		return;
	*(int*) (*(char**) (p + 0x204) + 0xa) = *s;
	o = fcn_0040c230(*(int*) (e + 0x184), fcn_004d4ee0, 5, 0x2e, 1);
	*(char**) (o + 0x17c) = e;
	*(char**) (o + 0x180) = p;
	*(blk24*) (o + 0xf0) = g_68bef4;
}
