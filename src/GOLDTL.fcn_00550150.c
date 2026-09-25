// FUNCTION: GOLD 0x005481e0
// SIZE: 373
// FUNCTION: GOLDTL 0x550150
// SIZE: 373

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
void __cdecl fcn_005015e0(int*, int*, int*, int);
void __cdecl fcn_00546190(char*);
int __cdecl fcn_004c4450(int);
char* __cdecl fcn_004c4480(int);
void __cdecl fcn_004c5da0(int, int, int, int, int, char*);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_00545e80(int, int, char*, int, int, int, int, int, char*);

void __cdecl fcn_00550150(char* e)
{
	int a;
	int b;
	char buf[0x200];
	char* h;
	int k;

	b = 0;
	a = 0;
	*(struct pos14*) (e + 0x52) = g_7f4c00;
	fcn_00500bb0((struct pos14*) (e + 0x52), 0, 4, 0);
	fcn_005015e0(&a, 0, 0, *(int*) (e + 0xb0));
	fcn_005015e0(0, 0, &b, *(int*) (e + 0xac));
	if (*(int*) (e + 0x70) == -2 || a == 0) {
		fcn_00546190(e);
	}
	if (*(int*) (e + 0x70) == 0 && fcn_004c4450(*(int*) (e + 0xbc)) != 0) {
		h = fcn_004c4480(*(int*) (e + 0xbc));
		if (h != 0) {
			k = (h[9] != 0 ? 0x230 : 0x20d) + *(unsigned char*) (h + 0x165);
			fcn_004c5da0(*(int*) (h + 4), *(int*) (e + 0xb0), *(int*) (e + 0xb4), 0, 0, "RndGeselle");
			fcn_0051af00(buf, *(unsigned short*) (e + 0xb8), *(unsigned short*) h, k, a);
			fcn_00545e80(*(int*) (e + 0xac), *(int*) (e + 0xac), buf, 0, 0x5ec, *(int*) (e + 0xb0), *(int*) (e + 0xb4), 0,
			    "_NACHRICHTEN_HS_00");
		}
		fcn_00546190(e);
	}
}
