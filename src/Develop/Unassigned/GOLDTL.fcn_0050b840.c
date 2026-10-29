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
extern char* lpObjektePROT;

/* ADDRESS: GOLDTL 0x0050b840 */
float __cdecl fcn_0050b840(int id)
{
	unsigned char* base;
	float acc;
	int i;
	int t;
	Rec* r;

	base = *(unsigned char**) 0x868050;
	t = ((int*) 0x99e0a0)[id];
	acc = g_6628a8;
	for (i = 0; i < 2; i++) {
		acc += base[t * 0x24d + 0x233 + i] * *(float*) 0x665be0 * *(double*) 0x665bd8;
	}
	r = (Rec*) lpObjektePROT;
	return acc * r[id].cap / r[id].div;
}
