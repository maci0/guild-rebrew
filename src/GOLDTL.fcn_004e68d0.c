// FUNCTION: GOLD 0x4e4f40
// SIZE: 64
// FUNCTION: GOLDTL 0x4e68d0
// SIZE: 64

typedef struct
{
	int id;
	char pad4[4];
	unsigned char type;
	char pad9[0xb];
	int key;
	char pad18[0xe];
	unsigned char flags;
	char pad27[9];
	char active;
	char pad31[3];
	int list[16];
	char tail[0xa0];
} Ent114;
// SIZE 0x114

extern Ent114 g_9a9660[96];

void* __cdecl fcn_004e6a30(unsigned int);

void* __cdecl fcn_004e68d0(void)
{
	unsigned int best;
	int i;

	best = (unsigned int) -1;
	for (i = 0; i < 96; i++) {
		if (g_9a9660[i].active != 0 && g_9a9660[i].id != -1 && (g_9a9660[i].flags & 1) != 0 &&
		    best >= (unsigned int) g_9a9660[i].id) {
			best = g_9a9660[i].id;
		}
	}
	if (best != (unsigned int) -1) {
		return fcn_004e6a30(best);
	}
	return 0;
}
