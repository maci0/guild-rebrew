// FUNCTION: GOLDTL 0x4e69e0
// SIZE: 76

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

Ent114* __cdecl fcn_004e69e0(int type, int key)
{
	int i;

	for (i = 0; i < 96; i++) {
		if (g_9a9660[i].active != 0 && g_9a9660[i].type == type && g_9a9660[i].key == key) {
			return &g_9a9660[i];
		}
	}
	return 0;
}
