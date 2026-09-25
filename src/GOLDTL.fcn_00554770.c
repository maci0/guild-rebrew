// FUNCTION: GOLDTL 0x00554770
// SIZE: 78

typedef struct {
	short w[7];
} Rec14;
// SIZE 0xe

extern Rec14 g_7f4c00;

void __cdecl fcn_00554770(char* e)
{
	*(Rec14*) (e + 0x52) = g_7f4c00;
	*(short*) (e + 0x56) = 10;
	*(int*) (e + 0x58) = 0;
	*(int*) (e + 0x5c) = 0;
	*(int*) (e + 0xac) = 0;
	*(int*) (e + 0xb0) = 0;
	*(int*) (e + 0xb4) = 0;
}
