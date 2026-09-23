// FUNCTION: GOLD 0x4fe280
// SIZE: 58
// FUNCTION: GOLDTL 0x500d20
// SIZE: 58

#pragma pack(push, 1)
typedef struct {
	int f0;
	unsigned short f4;
	int f6;
} fcn_00500d20_rec;
#pragma pack(pop)
// SIZE 0xa

int __cdecl fcn_00500d20(fcn_00500d20_rec* a1, fcn_00500d20_rec* a2)
{
	return ((a2->f0 - a1->f0) * 24 - a1->f4 + a2->f4) * 60 - a1->f6 + a2->f6;
}
