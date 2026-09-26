// FUNCTION: GOLD 0x50e0d0
// SIZE: 598
// FUNCTION: GOLDTL 0x00511580
// SIZE: 598

// SIZE 0x21c
typedef struct {
	unsigned short slot;
	unsigned char type;
	char pad3;
	int owner;
	char pad8[0x21c - 8];
} Entity;

// SIZE 0x8
typedef struct {
	char pad0[4];
	int owner;
} Figure;

extern char g_7f4ca0[];
extern unsigned char g_773d75;
extern char* g_773dac;
extern char* g_773db0;
extern char* g_aed32c;

void __cdecl fcn_0064d3f8(void);
unsigned short __cdecl fcn_0042e410(int);
int __cdecl fcn_0050b750(int, char);
void __cdecl fcn_004c4510(void*, int);
void __cdecl fcn_004c4670(int, int, int, void*);
void __cdecl fcn_004c5360(void);
void __cdecl fcn_004c44a0(void);
int __cdecl fcn_004c4fc0(int, int, int, short, int, char, int, int);
void __cdecl fcn_004c44b0(void);
int __cdecl fcn_004c44c0(void);
void __cdecl fcn_004c3ff0(void);
void __cdecl fcn_004c4940(void);
void __cdecl ls_ID2Ptr(void);
Figure* __cdecl fcn_004c4480(int);
void __cdecl fcn_004c4570(int, int, int, void*);
void __cdecl fcn_00535960(void);
void __cdecl fcn_004c51f0(int, int, int, int, char, int);

void __cdecl fcn_00511580(void)
{
	int flag;
	int money;
	int figures[16];
	int i;
	int a;
	int b;

	fcn_0064d3f8();
	for (i = 0; i < 16; i++) {
		if (((Entity*)g_7f4ca0)[i].slot != 0xffff && ((Entity*)g_7f4ca0)[i].type < 5) {
			money = fcn_0050b750(fcn_0042e410(0x122) + 10, (*(char*)&g_773d75));
			fcn_004c4510(&((Entity*)g_7f4ca0)[i], ((Entity*)g_7f4ca0)[i].owner);
			fcn_004c4670(4, 1, 0x1ac, &money);
			fcn_004c5360();
		}
	}
	fcn_004c44a0();
	a = fcn_004c4fc0(0xc, -1, -1, 0x12, -1, 0, 0, 0);
	b = fcn_004c4fc0(0xc, -1, -1, 0x12, -1, 0, 0, 0);
	fcn_004c44b0();
	while (fcn_004c44c0() == 0) {
		fcn_004c3ff0();
		fcn_004c4940();
		ls_ID2Ptr();
	}
	(*(Figure**)&g_773dac) = fcn_004c4480(a);
	(*(Figure**)&g_773db0) = fcn_004c4480(b);
	fcn_004c44a0();
	flag = 0;
	fcn_004c4510((*(Figure**)&g_773dac), (*(Figure**)&g_773dac)->owner);
	fcn_004c4570(1, 1, (char*) (*(Figure**)&g_773dac) - g_aed32c + 0xc, &flag);
	fcn_004c5360();
	flag = 1;
	fcn_004c4510((*(Figure**)&g_773db0), (*(Figure**)&g_773db0)->owner);
	fcn_004c4570(1, 1, (char*) (*(Figure**)&g_773db0) - g_aed32c + 0xc, &flag);
	fcn_004c5360();
	fcn_004c44b0();
	while (fcn_004c44c0() == 0) {
		fcn_004c3ff0();
		fcn_004c4940();
		ls_ID2Ptr();
	}
	fcn_004c44a0();
	for (i = 0; i < 8; i++) {
		figures[i] = fcn_004c4fc0(0, -1, -1, fcn_0042e410(8) + 0x10, -1, (char) (fcn_0042e410(3) + 4), 0, 0);
	}
	fcn_004c44b0();
	while (fcn_004c44c0() == 0) {
		fcn_00535960();
	}
	fcn_004c44a0();
	for (i = 0; i < 8; i++) {
		figures[i] = fcn_004c4fc0(0xb, -1, -1, fcn_0042e410(8) + 0x10, -1, 0, 0x13, 0);
		fcn_004c51f0(-2, -1, 0x154, 1, (*(char*)&g_773d75), 0);
	}
	fcn_004c44b0();
	while (fcn_004c44c0() == 0) {
		fcn_00535960();
	}
}
