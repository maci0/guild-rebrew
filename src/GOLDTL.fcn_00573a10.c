void __cdecl fcn_00500bb0(struct pos14*, int, int, int);

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

// FUNCTION: GOLDTL 0x573a10
// SIZE: 106

void __cdecl fcn_00573a10(char* o)
{
	*(struct pos14*) (o + 0x52) = *(struct pos14*) (o + 0x44);
	*(struct pos14*) (o + 0x60) = *(struct pos14*) (o + 0x44);
	fcn_00500bb0((struct pos14*) (o + 0x52), 0, 1, 0);
	*(int*) (o + 0xbc) = 0;
	*(int*) (o + 0xc0) = 0;
	*(int*) (o + 0xc4) = 0;
}
