// FUNCTION: GOLDTL 0x43ac00
// SIZE: 123

// SIZE 0x14
typedef struct Ctx {
	int a;
	int b;
	int c;
	int d;
	char on;
} Ctx;

extern int g_67a370;

void __cdecl fcn_004379a0(int, int, int, void*, void*);
void __cdecl fcn_0043aad0(void);
void __cdecl fcn_0045cfa0(int);
void __cdecl fcn_00450a00(int);

void __cdecl fcn_0043ac00(int mask, int b, int a)
{
	Ctx s;

	s.on = 1;
	s.d = 0;
	s.c = 0;
	s.a = a;
	s.b = b;
	fcn_004379a0(g_67a370, 0, mask, fcn_0043aad0, &s);
	s.on = 0;
	fcn_004379a0(g_67a370, 0, mask, fcn_0043aad0, &s);
	fcn_0045cfa0(a);
	fcn_00450a00(1);
}
