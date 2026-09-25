// FUNCTION: GOLD 0x00567fc0
// SIZE: 59
// FUNCTION: GOLDTL 0x00570370
// SIZE: 59

typedef struct {
	short w[7];
} Rec14;
// SIZE 0xe

extern Rec14 g_7f4c00;

void __cdecl fcn_00570370(char* e)
{
	*(Rec14*) (e + 0x52) = g_7f4c00;
	*(short*) (e + 0x56) = 7;
	*(int*) (e + 0x58) = 0;
}
