void __cdecl sim_SetSyncParams(struct pos14*, int, int, int);

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

// FUNCTION: GOLD 0x0055fd10
// SIZE: 107
// FUNCTION: GOLDTL 0x567ff0
// SIZE: 107

void __cdecl fcn_00500bb0(struct pos14*, int, int, int);

void __cdecl fcn_00567ff0(char* o)
{
	struct pos14* p;

	p = (struct pos14*) (o + 0x52);
	*p = g_7f4c00;
	sim_SetSyncParams(p, 5, 0, 0);
	*(struct pos14*) (o + 0x60) = *p;
	fcn_00500bb0(p, 1, 0, 0);
}
