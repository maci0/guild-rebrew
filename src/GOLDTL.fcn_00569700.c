// FUNCTION: GOLD 0x00561420
// SIZE: 87
// FUNCTION: GOLDTL 0x00569700
// SIZE: 87

typedef struct {
	short w[7];
} Rec14;
// SIZE 0xe

extern Rec14 g_7f4c00;

void __cdecl fcn_00569700(char* e)
{
	*(Rec14*) (e + 0x52) = g_7f4c00;
	*(Rec14*) (e + 0xb4) = g_7f4c00;
}
