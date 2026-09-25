// FUNCTION: GOLD 0x004fc820
// SIZE: 104
// FUNCTION: GOLDTL 0x004fef80
// SIZE: 104

typedef struct
{
	unsigned short id;
	char pad2[6];
	unsigned char x8;
	char pad9;
	unsigned short xa;
	char padc[4];
	float f10;
	char pad14[8];
	float f1c;
	float f20;
	int x24;
} Obj28;
// SIZE 0x28

extern float g_662a94;
extern double g_662950;

float __cdecl fcn_004fef80(Obj28* p)
{
	float x;
	float v;

	if (p->id == 0xffff) {
		return g_662a94;
	}
	if (p->x8 == 0) {
		return g_662a94;
	}
	x = p->xa;
	if (x <= p->f20) {
		v = x * ((p->f1c - p->f10) / p->f20) + p->f10;
	} else {
		v = p->f1c;
	}
	v += p->x24;
	return v > g_662950 ? v : g_662950;
}
