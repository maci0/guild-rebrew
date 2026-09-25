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

// FUNCTION: GOLDTL 0x57d950
// SIZE: 139

void __cdecl fcn_00500bb0(struct pos14*, int, int, int);

void __cdecl fcn_0057d950(char* o)
{
	*(struct pos14*) (o + 0x44) = g_7f4c00;
	*(struct pos14*) (o + 0x52) = g_7f4c00;
	*(int*) (o + 0x70) = 0;
	fcn_00500bb0((struct pos14*) (o + 0x52), fcn_0042e410(2), fcn_0042e410(0x1e), 0);
}
