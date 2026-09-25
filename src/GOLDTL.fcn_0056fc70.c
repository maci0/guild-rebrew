// FUNCTION: GOLD 0x5678c0
// SIZE: 62
// FUNCTION: GOLDTL 0x56fc70
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

void __cdecl fcn_0056fc70(char* u)
{
	*(struct pos14*) (u + 0x52) = g_7f4c00;
	fcn_00500bb0((struct pos14*) (u + 0x52), 0, 0x14, 0);
}
