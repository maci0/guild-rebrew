// FUNCTION: GOLDTL 0x0054bc40
// SIZE: 71

typedef struct {
	short w[7];
} Rec14;
// SIZE 0xe

extern Rec14 g_7f4c00;

void __cdecl fcn_00500bb0(char*, int, int, int);

void __cdecl fcn_0054bc40(char* e)
{
	*(Rec14*) (e + 0x52) = g_7f4c00;
	fcn_00500bb0(e + 0x52, 2, 0, 0);
	*(int*) (e + 0x70) = 0;
}
