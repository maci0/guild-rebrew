


// SIZE 0x6
typedef struct {
	char c[6];
} Name6;

// SIZE 0x5
typedef struct {
	char c[5];
} Name5;

extern char g_7e23e0[];
extern unsigned char g_7e23e1;
extern unsigned char g_7e23e2;
extern char g_7e23e3;
extern int g_7e23e4;
extern char g_7e23e8;
extern char g_7e23e9;
extern char g_7e23ea[];
extern char g_7e240a[];
extern Name5 g_7e2430;
extern int g_7e2468;
extern char* g_14b4fa8;
extern char* g_14b4fac;
extern char g_6a3db4[];

char* __cdecl strcpy(char*, const char*);
#pragma intrinsic(strcpy)
int __cdecl fcn_004fdec0(char*);
Name6 __cdecl fcn_00506d50(int);

void __cdecl fcn_00584530(void)
{
	Name6 r;

	(*(unsigned char*)g_7e23e0) = 0x4b;
	g_7e23e1 = 0x18;
	(*(unsigned char*)&g_7e23e3) = 0x33;
	g_7e23e2 = 0x10;
	g_7e23e4 = 0x59a;
	(*(unsigned char*)&g_7e23e8) = 0;
	(*(unsigned char*)&g_7e23e9) = 0;
	g_7e2468 = fcn_004fdec0(g_6a3db4) + 0x639;
	strcpy(g_7e23ea, g_14b4fa8);
	strcpy(g_7e240a, g_14b4fac);
	r = fcn_00506d50((*(unsigned char*)&g_7e23e3));
	g_7e2430 = *(Name5*) &r;
}
