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

extern Ent g_7f4ca0[768];

unsigned short __cdecl fcn_0042e410(int n);

// FUNCTION: GOLD 0x48fea0
// SIZE: 160
// FUNCTION: GOLDTL 0x48f450
// SIZE: 157
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
		if (g_7f4ca0[i].id != 0xffff && g_7f4ca0[i].kind == 0x14 && g_7f4ca0[i].owner == owner && g_7f4ca0[i].age > 0
		    && g_7f4ca0[i].task != 0x88 && g_7f4ca0[i].task != 0x90 && g_7f4ca0[i].task != 0x89 && g_7f4ca0[i].task != 0x8a) {
			list[n++] = i;
		}
	}
	if (n < 2) {
		return 0;
	}
	return &g_7f4ca0[list[fcn_0042e410(n)]];
}
