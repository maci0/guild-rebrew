// FUNCTION: GOLDTL 0x0055ffa0

typedef struct {
	short w[7];
} Rec14;
// SIZE 0xe

void __cdecl fcn_00500bb0(char*, int, int, int);

void __cdecl fcn_0055ffa0(char* e)
{
	*(Rec14*) (e + 0x52) = *(Rec14*) (e + 0x44);
	fcn_00500bb0(e + 0x52, 2, 0, 0);
}
