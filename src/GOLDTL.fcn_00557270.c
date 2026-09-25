// FUNCTION: GOLDTL 0x557270
// SIZE: 484

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
extern int g_6643d8[];
extern char* g_aed32c;
extern char g_67ec2c[];

unsigned short __cdecl fcn_0042e410(int);
void __cdecl fcn_00500bb0(struct pos14*, int, int, int);
char* __cdecl fcn_005463a0(int, int, int, ...);
char* __cdecl fcn_005462a0(void);
void __cdecl fcn_005015e0(char**, int, int, int);
char* __cdecl fcn_00502cd0(int, int, ...);
void __cdecl fcn_004c4510(char*, int);
void __cdecl fcn_004c4570(int, int, int, void*);
void __cdecl fcn_004c5360(void);
void __cdecl fcn_004c4eb0(char* s);
void __cdecl fcn_004c4ef0(char* s);
int __cdecl fcn_004c64b0(int, int, int, int, int, int, char*);
int __cdecl fcn_004c5620(int, char*);

void __cdecl fcn_00557270(char* u)
{
	char* e;
	char* o;
	char* q;

	if (u[0x78] & 4) {
		return;
	}
	*(int*) (u + 0xac) = -1;
	*(int*) (u + 0xc4) = fcn_0042e410(0x100);
	*(int*) (u + 0xc8) = g_6643d8[fcn_0042e410(0x10)];
	*(int*) (u + 0xbc) = fcn_0042e410(4) + 5;
	*(int*) (u + 0xc0) = 0;
	*(int*) (u + 0xb8) = -1;
	*(struct pos14*) (u + 0x52) = g_7f4c00;
	*(struct pos14*) (u + 0x44) = g_7f4c00;
	fcn_00500bb0((struct pos14*) (u + 0x52), 0, 1, 0);
	for (e = fcn_005463a0(1, 0, 0x74); e != 0; e = fcn_005462a0()) {
		if (*(int*) (e + 4) != *(int*) (u + 4) && *(int*) (e + 0xb0) == *(int*) (u + 0xb0)) {
			break;
		}
	}
	if (e == 0) {
		fcn_005015e0(&o, 0, 0, *(int*) (u + 0xb0));
		if (o != 0) {
			q = fcn_00502cd0(*(int*) (o + 0x5d), 2, 6, 0, 0x12c);
			if (q != 0) {
				int t = g_7f4c00.a;

				fcn_004c4510(q, *(int*) (q + 2));
				fcn_004c4570(4, 1, q - g_aed32c + 0x28, &t);
				fcn_004c5360();
				fcn_004c4eb0(g_67ec2c);
				*(int*) (u + 0xac) = fcn_004c64b0(0xe, *(int*) (o + 1), -1, 0, 0, 0, "DunkleEcke");
				*(int*) (u + 0x84) = fcn_004c5620(0, u);
				fcn_004c4ef0(g_67ec2c);
				return;
			}
		}
	}
	*(int*) (u + 0x84) = fcn_004c5620(-1, u);
}
