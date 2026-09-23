extern int g_6b8014;
// FUNCTION: GOLDTL 0x4056a0
// SIZE: 66

void __cdecl fcn_004055a0(int, int, void*, void*);
void __cdecl fcn_00438cb0(int, void*);
void __cdecl fcn_00438b40(int, void*);

void __cdecl fcn_004056a0(int a1, int a2)
{
	char a[0xc];
	char b[0x10];

	fcn_004055a0(a1, a2, b, a);
	fcn_00438cb0(g_6b8014, a);
	fcn_00438b40(g_6b8014, b);
}
