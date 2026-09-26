// FUNCTION: GOLDTL 0x005e3c40
// SIZE: 210

// SIZE 0x10
typedef struct {
	int left;
	int top;
	int right;
	int bottom;
} Rect;

extern int g_1040490;
extern int g_1040494;
extern int g_1040480;
extern int g_6a3764;
extern int g_774954;
extern int g_774670;
extern char g_67d67c[];

unsigned char* __cdecl fcn_004730c0(int, int, int, int, char*, int, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00533cf0(int);
void __cdecl fcn_0046b4f0(void);
void __cdecl fcn_00473150(unsigned char*);
void __cdecl fcn_005270c0(int);
void __cdecl fcn_00528fd0(void);

void __cdecl fcn_005e3c40(void)
{
	unsigned char* p;

	p = fcn_004730c0(0, 0, g_1040494, g_1040490, g_67d67c, 0x1e, 1);
	while (!(*p & 4)) {
		fcn_005373e0(0, 0x24087);
	}
	if (g_774954 != 0) {
		fcn_0046b4f0();
		fcn_00473150(p);
		g_774670 = 6;
		return;
	}
	(*(Rect*)&g_1040480) = (*(Rect*)&g_6a3764);
	fcn_0046b4f0();
	fcn_005270c0(1);
	fcn_00528fd0();
	fcn_00533cf0(0);
	fcn_00473150(p);
	fcn_004730c0(0, 0, g_1040494, g_1040490, g_67d67c, 0x32, 0xa);
}
