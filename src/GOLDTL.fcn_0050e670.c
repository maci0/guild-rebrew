// FUNCTION: GOLD 0x0050b1e0
// SIZE: 170
// FUNCTION: GOLDTL 0x0050e670
// SIZE: 170

typedef struct
{
	unsigned short id;
	unsigned char x2;
	char pad3;
	int x4;
	char pad8[0x1a4];
	int x1ac;
	char pad1b0[0x6c];
} Ent21c;
// SIZE 0x21c

extern char g_7f4ca0[];

void __cdecl fcn_0050e670(int* ids, int* vals)
{
	int i;
	int j;

	for (i = 0; i < 5; i++) {
		ids[i] = 0xffff;
		vals[i] = 0;
	}
	for (i = 0; i < 768; i++) {
		if (((Ent21c*)g_7f4ca0)[i].x4 != -1 && ((Ent21c*)g_7f4ca0)[i].x2 < 10 && ((Ent21c*)g_7f4ca0)[i].x1ac > vals[4]) {
			vals[4] = ((Ent21c*)g_7f4ca0)[i].x1ac;
			ids[4] = ((Ent21c*)g_7f4ca0)[i].id;
			for (j = 3; j > -1; j--) {
				if (((Ent21c*)g_7f4ca0)[i].x1ac <= vals[j] || ((Ent21c*)g_7f4ca0)[i].x2 >= 10) {
					break;
				}
				vals[j + 1] = vals[j];
				ids[j + 1] = ids[j];
				vals[j] = ((Ent21c*)g_7f4ca0)[i].x1ac;
				ids[j] = ((Ent21c*)g_7f4ca0)[i].id;
			}
		}
	}
}
