// FUNCTION: GOLD 0x00554a70
// SIZE: 54
// FUNCTION: GOLDTL 0x0055cc40
// SIZE: 54

typedef struct {
	short w[7];
} Rec14;
// SIZE 0xe

void __cdecl fcn_00500bb0(char*, int, int, int);

void __cdecl fcn_0055cc40(char* e)
{
	*(Rec14*) (e + 0x52) = *(Rec14*) (e + 0x44);
	fcn_00500bb0(e + 0x52, 0, 0xf, 0);
}
