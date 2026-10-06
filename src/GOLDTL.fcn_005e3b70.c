// FUNCTION: GOLDTL 0x005e3b70

extern int g_7e46ac;
extern int g_1040490;
extern int g_1040494;
extern int g_1040480;
extern int g_1040484;
extern int g_1040488;
extern int g_104048c;
extern char g_67d67c[];

unsigned char* __cdecl fcn_004730c0(int, int, int, int, char*, int, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00533cf0(int);
void __cdecl fcn_0046b4f0(void);
void __cdecl fcn_00469e30(int);
void __cdecl fcn_00473150(unsigned char*);
void __cdecl fcn_005270c0(int);

void __cdecl fcn_005e3b70(void)
{
	int flags;
	unsigned char* p;

	flags = (g_7e46ac & ~0x2000) | 0x100000;
	p = fcn_004730c0(0, 0, g_1040494, g_1040490, g_67d67c, 0x1e, 1);
	while (!(*p & 4)) {
		fcn_005373e0(0, flags);
	}
	g_1040488 = 0;
	g_1040480 = g_1040494;
	g_1040484 = 0;
	g_104048c = g_1040490;
	g_7e46ac = 0x24087;
	fcn_00533cf0(1);
	fcn_0046b4f0();
	fcn_00469e30(0x794);
	fcn_00473150(p);
	fcn_005270c0(0);
	fcn_004730c0(0, 0, g_1040494, g_1040490, g_67d67c, 0x32, 0xa);
}
