// FUNCTION: GOLD 0x00545830
// SIZE: 87
// FUNCTION: GOLDTL 0x0054d7b0
// SIZE: 87

typedef struct {
	short w[7];
} Rec14;
// SIZE 0xe

extern Rec14 g_7f4c00;

int __cdecl fcn_0042e410(int);

void __cdecl fcn_0054d7b0(char* e)
{
	*(Rec14*) (e + 0x52) = g_7f4c00;
	*(short*) (e + 0x56) = fcn_0042e410(10) + 10;
	*(int*) (e + 0x58) = (unsigned short) fcn_0042e410(0x3b);
	*(int*) (e + 0x5c) = 0;
}
