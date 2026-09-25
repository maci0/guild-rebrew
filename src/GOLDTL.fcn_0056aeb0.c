// FUNCTION: GOLD 0x562b80
// SIZE: 62
// FUNCTION: GOLDTL 0x56aeb0
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

void __cdecl fcn_0056aeb0(char* e)
{
	*(struct pos14*) (e + 0x52) = g_7f4c00;
	fcn_00500bb0((struct pos14*) (e + 0x52), 0, 0, 1);
}
