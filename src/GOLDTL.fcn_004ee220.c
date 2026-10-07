// FUNCTION: GOLD 0x004ec490
// FUNCTION: GOLDTL 0x004ee220

typedef struct
{
	int a;
	int b;
	int c;
} V12;
// SIZE 0xc

typedef struct
{
	int h0;
	int h4;
	int x8;
	V12 v;
	int x18;
	int x1c;
	int x20;
} Msg24;
// SIZE 0x24

int __cdecl fcn_004ecbe0(int id);
int __cdecl fcn_004c6cf0(Msg24* m);

int __cdecl fcn_004ee220(char* a, char* p)
{
	Msg24 m;
	char* q;

	q = (char*) fcn_004ecbe0(*(int*) (p + 0xc));
	if (q == 0) {
		return -1;
	}
	m.x8 = *(int*) (a + 1);
	m.v = *(V12*) (p + 4);
	m.x18 = *(int*) (p + 0x10);
	m.x1c = *(int*) (p + 0x14);
	m.x20 = *(int*) (q + 8);
	return fcn_004c6cf0(&m);
}
