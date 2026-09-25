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

// FUNCTION: GOLDTL 0x575470
// SIZE: 105

void __cdecl fcn_00575470(char* o)
{
	*(struct pos14*) (o + 0x52) = *(struct pos14*) (o + 0x44);
	*(int*) (o + 0x70) = 0;
	*(struct pos14*) (o + 0x60) = *(struct pos14*) (o + 0x44);
	*(int*) (o + 0xac) = -1;
	fcn_00500bb0((struct pos14*) (o + 0x52), 0, 0xa, 0);
}
