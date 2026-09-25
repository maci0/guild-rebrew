// FUNCTION: GOLDTL 0x0057a130
// SIZE: 71

typedef struct {
	short w[7];
} Rec14;
// SIZE 0xe

extern Rec14 g_7f4c00;

void __cdecl fcn_00500bb0(char*, int, int, int);

void __cdecl fcn_0057a130(char* e)
{
	*(Rec14*) (e + 0x52) = g_7f4c00;
	*(int*) (e + 0x70) = 0;
	fcn_00500bb0(e + 0x52, 0x48, 0, 0);
}
