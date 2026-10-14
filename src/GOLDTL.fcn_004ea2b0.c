


typedef struct {
	unsigned char c0;
	char pad1[3];
	int id;
	unsigned char kind;
	char pad9[3];
	int fc;
	unsigned char f10;
	char pad11[3];
	int f14;
} rec18;
// SIZE 0x18

typedef struct {
	int a;
	int id;
	char pad8[0x10];
} tbl18;
// SIZE 0x18

int __cdecl fcn_004e8b80(int, int, rec18*);
unsigned char* __cdecl fcn_00508e40(int);

int __cdecl fcn_004ea2b0(int kind, char* x)
{
	rec18 list[6];
	int n;
	int i;
	unsigned char* a;
	unsigned char* b;

	if (x[0x10] != 2)
		return 0;
	n = fcn_004e8b80(kind, 6, list);
	a = fcn_00508e40(*(int*) (x + 0x14));
	b = fcn_00508e40(*(int*) (x + 4));
	if (a == 0 || a[8] <= 0 || a[0x1b1] != 0 || b == 0 || b[8] <= 0)
		return 0;
	for (i = 0; i < n; i++) {
		if (list[i].id == *(int*) (x + 0x14))
			return 1;
	}
	return 0;
}
