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

// FUNCTION: GOLDTL 0x551160
// SIZE: 62

void __cdecl fcn_00551160(char* o)
{
	*(struct pos14*) (o + 0x52) = g_7f4c00;
	fcn_00500bb0((struct pos14*) (o + 0x52), 0x60, 0, 0);
}
