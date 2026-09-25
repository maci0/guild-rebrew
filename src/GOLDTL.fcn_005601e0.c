void __cdecl fcn_00546190(char*);

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

// FUNCTION: GOLD 0x00557fc0
// SIZE: 167
// FUNCTION: GOLDTL 0x5601e0
// SIZE: 167

unsigned short* __cdecl fcn_00508e40(int);
void __cdecl fcn_00529160(int, int, int, char*);
void __cdecl fcn_00500bb0(struct pos14*, int, int, int);

void __cdecl fcn_005601e0(char* o)
{
	int any;
	int i;
	unsigned short* e;

	any = 0;
	for (i = 0; i < *(unsigned char*) (o + 0xac); i++) {
		e = fcn_00508e40(((int*) (o + 0x8c))[i]);
		if (e != 0) {
			any |= 1;
			fcn_00529160(0, 0, *e, o);
		}
	}
	if (any == 0) {
		fcn_00546190(o);
		return;
	}
	*(struct pos14*) (o + 0x52) = g_7f4c00;
	*(int*) (o + 0x70) = 1;
	fcn_00500bb0((struct pos14*) (o + 0x52), 0, 5, 0);
}
