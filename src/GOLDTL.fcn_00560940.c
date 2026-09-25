// FUNCTION: GOLDTL 0x560940
// SIZE: 126

#pragma pack(2)
// SIZE 0xe
struct pos14 {
	int a;
	int b;
	int c;
	short d;
};
#pragma pack()

char* __cdecl fcn_00508e40(int);
void __cdecl fcn_00529160(int, int, int, char*);
void __cdecl fcn_00500bb0(struct pos14*, int, int, int);

void __cdecl fcn_00560940(char* e)
{
	char* p;
	int i;

	for (i = 0; i < *(unsigned char*) (e + 0xac); i++) {
		p = fcn_00508e40(((int*) (e + 0x8c))[i]);
		if (p != 0) {
			fcn_00529160(0, 0, *(unsigned short*) p, e);
		}
	}
	*(struct pos14*) (e + 0x52) = *(struct pos14*) (e + 0x44);
	fcn_00500bb0((struct pos14*) (e + 0x52), 0, 1, 0);
}
