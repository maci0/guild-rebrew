// FUNCTION: GOLD 0x0054ce70
// SIZE: 48
// FUNCTION: GOLDTL 0x554ed0
// SIZE: 48

#pragma pack(2)
// SIZE 0xe
struct pos14 {
	int a;
	int b;
	int c;
	short d;
};
#pragma pack()

void __cdecl fcn_00554ed0(char* e)
{
	*(struct pos14*) (e + 0x52) = *(struct pos14*) (e + 0x44);
	*(int*) (e + 0x70) = 0;
	*(int*) (e + 0xb4) = 0;
}
