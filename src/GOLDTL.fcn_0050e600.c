// FUNCTION: GOLD 0x0050b170
// SIZE: 100
// FUNCTION: GOLDTL 0x0050e600
// SIZE: 100

typedef struct
{
	unsigned short id;
	unsigned char x2;
	char pad3[0x1a9];
	int x1ac;
	char pad1b0[0x6c];
} Ent21c;
// SIZE 0x21c

extern char g_7f4ca0[];

int __cdecl fcn_0050e600(int i, int add)
{
	int r;
	int v;
	int j;

	r = 1;
	if (i < 0 || i >= 0x300) {
		return 0;
	}
	v = ((Ent21c*)g_7f4ca0)[i].x1ac + add;
	for (j = 0; j < 768; j++) {
		if (v <= ((Ent21c*)g_7f4ca0)[j].x1ac && ((Ent21c*)g_7f4ca0)[j].id != 0xffff && ((Ent21c*)g_7f4ca0)[j].x2 < 10 && j != i) {
			r++;
		}
	}
	return r;
}
