#pragma pack(push, 1)
typedef struct Rec {
    char type;
    char pad1[0x21];
    unsigned int cap;
    unsigned short weight[4];
    char pad2e[8];
    unsigned short div;
    char pad38[9];
} Rec;
#pragma pack(pop)

extern float g_6628a8;
extern char* g_99ec10;

/* ADDRESS: GOLDTL 0x0050b840 */
float __cdecl fcn_0050b840(int id)
{
	Rec* r;
	unsigned char* base;
	float acc;
	int i;
	int t;

	acc = g_6628a8;
	base = *(unsigned char**) 0x868050;
	t = ((int*) 0x99e0a0)[id];
	for (i = 0; i < 2; i++) {
		acc += base[t * 0x24d + 0x233 + i] * *(float*) 0x665be0 * *(double*) 0x665bd8;
	}
	r = &((Rec*) g_99ec10)[id];
	return acc * r->cap / r->div;
}
