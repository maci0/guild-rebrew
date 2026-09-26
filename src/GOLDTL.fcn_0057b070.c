extern unsigned char* g_868050;
extern float g_6652d8[];

// SIZE 0x21c
struct s_7f4ca0 {
	char pad[2];
	char kind;
	char pad2[0x219];
};

extern char g_7f4ca0[];

// FUNCTION: GOLD 0x00572b60
// SIZE: 235
// FUNCTION: GOLDTL 0x57b070
// SIZE: 235

unsigned char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
char* __cdecl fcn_00508e40(int);
void __cdecl fcn_004f2810(char*, unsigned char*, int, int, short, int);
void __cdecl fcn_005b2db0(struct s_7f4ca0*, char*, unsigned char*, int, int, int);

void __cdecl fcn_0057b070(char* o)
{
	unsigned char* e;
	char* x;
	struct s_7f4ca0* r;
	int a;
	int b;

	e = gm_StartFilteredEntitySearch(1, 1, *(int*) (o + 0xac));
	if (e != 0 && g_868050[*e * 0x24d] == 0x1d) {
		x = fcn_00508e40(*(int*) (o + 0xc));
		if (x != 0) {
			fcn_004f2810(x, e, *(int*) (o + 0xb0), *(unsigned char*) (o + 0xb4),
			             *(short*) (o + 0xbc), *(int*) (o + 0xb8));
			r = &((struct s_7f4ca0*)g_7f4ca0)[*(unsigned short*) (e + 0x27)];
			if (x != (char*) r && (((struct s_7f4ca0*)g_7f4ca0)[*(unsigned short*) (e + 0x27)].kind == 6 ||
			                       ((struct s_7f4ca0*)g_7f4ca0)[*(unsigned short*) (e + 0x27)].kind == 7)) {
				a = *(int*) (o + 0xb0);
				b = *(int*) (o + 0xb8);
				fcn_005b2db0(r, x, e, a, b, (int) (b * g_6652d8[a]));
			}
		}
	}
}
