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

// FUNCTION: GOLD 0x00563350
// SIZE: 120
// FUNCTION: GOLDTL 0x56b680
// SIZE: 120

void __cdecl fcn_0056b680(char* o)
{
	struct pos14* p;

	p = (struct pos14*) (o + 0x52);
	*p = g_7f4c00;
	*(struct pos14*) (o + 0xcc) = g_7f4c00;
	fcn_00500bb0((struct pos14*) (o + 0xcc), 0x30, 0, 0);
	fcn_00500bb0(p, 0, 0, 1);
}
