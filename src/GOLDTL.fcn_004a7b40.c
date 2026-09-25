extern char* g_1007cd4;
extern unsigned char g_773d75;

void __cdecl fcn_0050b750(int amount, unsigned char k);
void __cdecl fcn_004c51a0(int a, int b, unsigned char k, int amount);

// FUNCTION: GOLD 0x004a7a20
// SIZE: 149
// FUNCTION: GOLDTL 0x4a7b40
// SIZE: 149
void __cdecl fcn_004a7b40(void)
{
	int i;

	for (i = 0; i < 3; i++) {
		if (*(int*) (g_1007cd4 + 0x2c + i * 0x34) < 0) {
			*(int*) (g_1007cd4 + 0xa0) += *(int*) (g_1007cd4 + 0xac);
			if (i == 0) {
				fcn_0050b750(*(int*) (g_1007cd4 + 0xac), g_773d75);
				fcn_004c51a0(-1, *(int*) (*(char**) (g_1007cd4 + 4) + 4), g_773d75, *(int*) (g_1007cd4 + 0xac));
			}
			*(int*) (g_1007cd4 + 0x20 + i * 0x34) += *(int*) (g_1007cd4 + 0xac);
		}
	}
}
