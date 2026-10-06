// FUNCTION: GOLD 0x004e5050
// FUNCTION: GOLDTL 0x4e69e0

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

extern char g_9a9660[];

Ent114* __cdecl fcn_004e69e0(int type, int key)
{
	int i;

	for (i = 0; i < 96; i++) {
		if (((Ent114*)g_9a9660)[i].active != 0 && ((Ent114*)g_9a9660)[i].type == type && ((Ent114*)g_9a9660)[i].key == key) {
			return &((Ent114*)g_9a9660)[i];
		}
	}
	return 0;
}
