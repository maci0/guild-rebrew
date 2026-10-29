typedef struct Ent {
	unsigned short id;
	unsigned char kind;
	char pad3[5];
	unsigned char age;
	char pad9[0x16c - 9];
	int owner;
	char pad170[0x180 - 0x170];
	unsigned char task;
	char pad181[0x21c - 0x181];
} Ent;
// SIZE 0x21c

extern char g_7f4ca0[];

unsigned short __cdecl gm_RandomMod(int n);

/* ADDRESS: GOLDTL 0x0048f450 */
Ent* __cdecl fcn_0048f450(int owner)
{
	unsigned short list[8];
	int n;
	int i;

	n = 0;
	for (i = 0; i < 768; i++) {
		if (n >= 8) {
			break;
		}
		if (((Ent*)g_7f4ca0)[i].id != 0xffff && ((Ent*)g_7f4ca0)[i].kind == 0x14 && ((Ent*)g_7f4ca0)[i].owner == owner && ((Ent*)g_7f4ca0)[i].age > 0
		    && ((Ent*)g_7f4ca0)[i].task != 0x88 && ((Ent*)g_7f4ca0)[i].task != 0x90 && ((Ent*)g_7f4ca0)[i].task != 0x89 && ((Ent*)g_7f4ca0)[i].task != 0x8a) {
			list[n++] = i;
		}
	}
	if (n < 2) {
		return 0;
	}
	return &((Ent*)g_7f4ca0)[list[gm_RandomMod(n)]];
}
