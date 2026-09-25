unsigned short __cdecl fcn_0042e410(int);

#pragma pack(2)
// SIZE 0xe
struct pos14 {
	int a;
	int b;
	int c;
	short d;
};
#pragma pack()


extern struct pos14 g_7f4c00;

// FUNCTION: GOLD 0x00552450
// SIZE: 103
// FUNCTION: GOLDTL 0x55a540
// SIZE: 103

void __cdecl fcn_0055a540(char* o)
{
	*(int*) (o + 0x70) = 0;
	*(struct pos14*) (o + 0x52) = g_7f4c00;
	*(short*) (o + 0x56) = fcn_0042e410(3) + 9;
	*(int*) (o + 0x58) = fcn_0042e410(4) * 15;
	*(int*) (o + 0xb0) = 0;
}
