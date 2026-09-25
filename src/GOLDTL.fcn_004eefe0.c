// FUNCTION: GOLDTL 0x4eefe0
// SIZE: 30

typedef struct
{
	char pad[0xf2];
	char used;
	char tail;
} Rec0f4;
// SIZE 0xf4

extern Rec0f4 g_68e020[32];

int __cdecl fcn_004eefe0(void)
{
	int n;
	unsigned int i;

	n = 0;
	for (i = 0; i < 32; i++) {
		if (g_68e020[i].used == 0) {
			n++;
		}
	}
	return n;
}
