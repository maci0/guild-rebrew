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

// FUNCTION: GOLDTL 0x572780
// SIZE: 101

void __cdecl fcn_00500bb0(struct pos14*, int, int, int);

void __cdecl fcn_00572780(char* o)
{
	*(struct pos14*) (o + 0x52) = *(struct pos14*) (o + 0x44);
	*(struct pos14*) (o + 0x60) = *(struct pos14*) (o + 0x44);
	fcn_00500bb0((struct pos14*) (o + 0x52), 4, fcn_0042e410(0x3c), 0);
}
