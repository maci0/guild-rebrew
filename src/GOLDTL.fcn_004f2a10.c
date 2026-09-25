// FUNCTION: GOLDTL 0x004f2a10
// SIZE: 106

#pragma pack(push, 1)
typedef struct
{
	int type;
	int a;
	int b;
	int c;
	char d;
	short e;
	int f;
	char pad[9];
} Msg20;
// SIZE 0x20
#pragma pack(pop)

int __cdecl fcn_004c6c30(Msg20* m);

int __cdecl fcn_004f2a10(int* a, char* b, int c, int d)
{
	Msg20 m;
	int t;

	if (b == 0 || d == -1) {
		return -1;
	}
	if (a == 0) {
		t = -1;
	} else {
		t = a[1];
	}
	m.a = t;
	m.b = *(int*) (b + 1);
	m.type = 3;
	m.c = c;
	m.d = (char) d;
	m.e = 0;
	m.f = 0;
	return fcn_004c6c30(&m);
}
