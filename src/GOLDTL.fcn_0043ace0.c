extern int g_67a370;

char __cdecl fcn_0043ac80(char* a, char on);
void __cdecl fcn_004379a0(int list, int a, int mask, char(__cdecl* fn)(char*, char), int arg);
void __cdecl fcn_00450a00(int a);

// FUNCTION: GOLDTL 0x43ace0
// SIZE: 47
void __cdecl fcn_0043ace0(unsigned char a)
{
	fcn_004379a0(g_67a370, 0, 6, fcn_0043ac80, a);
	fcn_00450a00(1);
}
