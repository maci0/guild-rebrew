extern unsigned short g_774970;

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

// SIZE 0x21c
struct s_7f4ca0 {
	int f0;
	int f4;
	char pad[0x214];
};

extern struct s_7f4ca0 g_7f4ca0[];

// FUNCTION: GOLD 0x005412c0
// SIZE: 137
// FUNCTION: GOLDTL 0x549130
// SIZE: 137

char* __cdecl fcn_005463a0(int, int, int, ...);
void __cdecl fcn_00546190(char*);
void __cdecl fcn_004c5530(struct msg*);

void __cdecl fcn_00549130(void)
{
	struct msg m;
	char* p;

	p = fcn_005463a0(1, 0, 0x3b);
	if (p != 0) {
		fcn_00546190(p);
	}
	m.b4 = (char) 0x3b;
	m.fc = -1;
	m.b36 = 1;
	m.f8 = g_7f4ca0[g_774970].f4;
	m.pos = g_7f4c00;
	fcn_004c5530(&m);
}
