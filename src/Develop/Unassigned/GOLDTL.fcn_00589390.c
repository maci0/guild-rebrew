extern char g_77dda0[];
extern char g_77dda0[];



typedef struct {
	int f0;
	float f4;
	int f8;
	int fc;
} KANONE_HIT_SLOT;
// SIZE 0x10

typedef struct {
	int head0;
	int head4;
	KANONE_HIT_SLOT s[3];
} KANONE_HIT_GROUP;
// SIZE 0x38

void __cdecl d2_ResetKanoneHitTable(void)
{
	KANONE_HIT_GROUP* base;
	int i;
	int j;

	base = (KANONE_HIT_GROUP*) g_77dda0;
	for (i = 0; i < 3; i++) {
		base[i].head0 = -1;
		for (j = 0; j < 3; j++) {
			base[i].s[j].f0 = -1;
			base[i].s[j].f4 = 100000.0f;
			base[i].s[j].f8 = 0;
			base[i].s[j].fc = 0;
		}
	}
}
