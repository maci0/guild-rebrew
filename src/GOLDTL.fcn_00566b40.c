// FUNCTION: GOLDTL 0x566b40
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

void __cdecl fcn_00500bb0(struct pos14*, int, int, int);

void __cdecl fcn_00566b40(char* u)
{
	*(struct pos14*) (u + 0x52) = g_7f4c00;
	fcn_00500bb0((struct pos14*) (u + 0x52), 4, 0, 0);
}
