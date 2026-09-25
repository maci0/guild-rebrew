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

// FUNCTION: GOLD 0x00574320
// SIZE: 109
// FUNCTION: GOLDTL 0x57c860
// SIZE: 109

void __cdecl fcn_0057c860(char* o)
{
	*(int*) (o + 0x70) = -1;
	*(struct pos14*) (o + 0x44) = g_7f4c00;
	*(struct pos14*) (o + 0x52) = g_7f4c00;
	fcn_00500bb0((struct pos14*) (o + 0x52), 0x18, 0, 0);
}
