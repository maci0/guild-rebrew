extern int g_67a370;
extern int g_6b89c0;
extern int g_6b8300;

char __cdecl fcn_00438a80(void* p, int arg);
void __cdecl fcn_004379a0(int list, int a, int mask, char(__cdecl* fn)(void*, int), int arg);
void __cdecl fcn_00459710(int a, int b);

// FUNCTION: GOLDTL 0x438af0
// SIZE: 74
void __cdecl fcn_00438af0(unsigned char a)
{
	fcn_004379a0(g_67a370, 0, 0x1ff, fcn_00438a80, a);
	if (g_6b89c0 != 0) {
		fcn_00459710(g_6b89c0, 0);
	}
	if (((char*)g_6b8300) != 0) {
		((char*)g_6b8300)[0x8036] |= 1;
	}
}
