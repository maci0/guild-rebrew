extern int g_67a370;
extern char g_1041d6c;

char __cdecl fcn_004462b0(void* p, int arg);
void __cdecl fcn_004379a0(int list, int a, int mask, char(__cdecl* fn)(void*, int), int arg);

// FUNCTION: GOLDTL 0x4463b0
// SIZE: 49
char __cdecl fcn_004463b0(unsigned int n)
{
	g_1041d6c = 0;
	if (n < 7) {
		fcn_004379a0(g_67a370, 0, 0x1e, fcn_004462b0, n);
		return g_1041d6c;
	}
	return 0;
}
