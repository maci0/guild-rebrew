extern char* g_6b8014;
// FUNCTION: GOLDTL 0x0052d7c0
// SIZE: 93

void __cdecl fcn_0052d7c0(int* src)
{
	if (g_6b8014 != 0 && src != 0) {
		*(int*) (g_6b8014 + 0x4c) = src[0];
		*(int*) (g_6b8014 + 0x50) = src[1];
		*(int*) (g_6b8014 + 0x54) = src[2];
		*(int*) (g_6b8014 + 0x84) = src[4];
		*(int*) (g_6b8014 + 0x88) = src[5];
		*(int*) (g_6b8014 + 0x8c) = src[6];
	}
}
