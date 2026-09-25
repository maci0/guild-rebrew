// FUNCTION: GOLD 0x5510f0
// SIZE: 62
// FUNCTION: GOLDTL 0x5591c0
// SIZE: 62

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

void __cdecl fcn_005591c0(char* e)
{
	*(int*) (e + 0x70) = 0;
	*(struct pos14*) (e + 0x52) = g_7f4c00;
	*(short*) (e + 0x56) = 7;
	*(int*) (e + 0x58) = 0;
}
