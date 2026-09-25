extern unsigned char* g_868050;

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

// FUNCTION: GOLDTL 0x5500a0
// SIZE: 173

void __cdecl fcn_005015e0(unsigned char**, int, int, int);
void __cdecl fcn_00546190(char*);
int __cdecl fcn_004c6090(unsigned char*, int, int, int);
void __cdecl fcn_00500bb0(struct pos14*, int, int, int);

void __cdecl fcn_005500a0(char* o)
{
	unsigned char* e;
	unsigned char* t;

	e = 0;
	fcn_005015e0(&e, 0, 0, *(int*) (o + 0xb0));
	if (e == 0) {
		fcn_00546190(o);
	}
	t = g_868050 + *e * 0x24d;
	*(int*) (o + 0xbc) = fcn_004c6090(e, 0, t[0x22f], 0);
	*(struct pos14*) (o + 0x52) = g_7f4c00;
	fcn_00500bb0((struct pos14*) (o + 0x52), 0, 6, 0);
}
