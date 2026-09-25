

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

// SIZE 0xf8
struct msg {
	int f0;
	char b4;
	char pad[3];
	int f8;
	int fc;
	char pad2[0x18];
	struct pos14 pos;
	char b36;
	char pad3[0x21];
	char b58;
	char pad4[3];
	char b5c;
	char pad5[0x9b];
};

// FUNCTION: GOLDTL 0x54f340
// SIZE: 102

void __cdecl fcn_00500bb0(struct pos14*, int, int, int);

void __cdecl fcn_0054f340(char* o)
{
	*(struct pos14*) (o + 0x44) = g_7f4c00;
	*(struct pos14*) (o + 0x52) = g_7f4c00;
	fcn_00500bb0((struct pos14*) (o + 0x52), 2, 0, 0);
}
