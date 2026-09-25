// FUNCTION: GOLD 0x004e6fc0
// SIZE: 114
// FUNCTION: GOLDTL 0x4e8b80
// SIZE: 114

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

extern rec18 g_9a9220[];
extern tbl18 g_68da68[];

int __cdecl fcn_004e8b80(int kind, int max, rec18* out)
{
	int n;
	int i;
	int start;

	if (kind == 0)
		return 0;
	if (kind <= 6)
		start = 30;
	else if (kind == 8)
		start = 42;
	else
		return 0;
	n = 0;
	for (i = start - 1; i >= 0 && n < max; i--) {
		if (g_68da68[g_9a9220[i].kind].id == kind)
			out[n++] = g_9a9220[i];
	}
	return n;
}
