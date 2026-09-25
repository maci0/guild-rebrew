extern char* g_99ec10;
extern int g_774800;

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

// FUNCTION: GOLD 0x00554060
// SIZE: 116
// FUNCTION: GOLDTL 0x55c1f0
// SIZE: 116

void __cdecl fcn_00500bb0(struct pos14*, int, int, int);

void __cdecl fcn_0055c1f0(char* o)
{
	char* t;

	t = g_99ec10 + *(unsigned short*) (o + 0xac) * 0x41;
	*(struct pos14*) (o + 0x52) = g_7f4c00;
	if (g_774800 != 0) {
		fcn_00500bb0((struct pos14*) (o + 0x52), 0, 0, 1);
	} else {
		fcn_00500bb0((struct pos14*) (o + 0x52), 0, *(int*) (t + 0x22), 0);
	}
}
