// FUNCTION: GOLDTL 0x00402950
// SIZE: 170

// SIZE 0xc
typedef struct {
	char* e;
	char b;
	int c;
} E402950;

// SIZE 0x4
typedef struct {
	unsigned char r;
	unsigned char g;
	unsigned char f0 : 1;
	unsigned char f1 : 7;
	unsigned char x;
} V402950;

extern E402950 g_1551f40[16];
extern int g_6b5c24;
void __cdecl fcn_00402a00(char* e, int on);
void __cdecl fcn_0043a3f0(char* o, int v, V402950 c);

void __cdecl fcn_00402950(char* e, char b)
{
	int i;
	V402950 v;
	char* o;

	for (i = 0; i < 16; i++) {
		if (g_1551f40[i].e == 0) {
			break;
		}
	}
	if (i >= 16) {
		return;
	}
	g_1551f40[i].e = e;
	g_1551f40[i].b = b;
	g_1551f40[i].c = g_6b5c24 - 1;
	fcn_00402a00(e, 1);
	*(int*) &v = 0;
	v.r = 0xff;
	v.f0 = 0;
	o = *(char**) (e + 0x34);
	fcn_0043a3f0(o, *(int*) (o + 0x1cc), v);
	if (*(char***) (e + 0x124) != 0) {
		o = **(char***) (e + 0x124);
		fcn_0043a3f0(o, *(int*) (o + 0x1cc), v);
	}
	*(short*) (e + 0x8c) |= 0x40;
}
