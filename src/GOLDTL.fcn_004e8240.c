// FUNCTION: GOLDTL 0x4e8240
// SIZE: 129

typedef struct {
	unsigned char c0;
	char pad1[3];
	int id;
	unsigned char kind;
	char pad9[7];
	unsigned char f10;
	char pad11[3];
	int f14;
} rec18;
// SIZE 0x18

extern rec18 g_9a9220[];

int __cdecl fcn_004c63a0(char*);

int __cdecl fcn_004e8240(unsigned char id, char* ea, char* eb, char x1, char x2)
{
	char m[0x10];
	int a;
	int b;
	int i;

	a = -1;
	b = -1;
	if (ea != 0)
		a = *(int*) (ea + 4);
	if (eb != 0)
		b = *(int*) (eb + 4);
	for (i = 0; i < 42; i++) {
		if (g_9a9220[i].c0 == id)
			break;
	}
	if (i >= 42)
		return -1;
	m[0] = id;
	*(int*) (m + 1) = a;
	m[5] = x1;
	m[6] = x2;
	*(int*) (m + 7) = b;
	return fcn_004c63a0(m);
}
