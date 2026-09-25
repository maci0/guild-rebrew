extern char* g_1015ec0[];

void __cdecl fcn_0047ce50(void* p);
void __cdecl fcn_0041ddd0(void* p);

// FUNCTION: GOLDTL 0x473150
// SIZE: 62
void __cdecl fcn_00473150(char* p)
{
	int i;

	for (i = 0; i < 32; i++) {
		if (g_1015ec0[i] == p) {
			g_1015ec0[i] = 0;
			if (*(void**) (p + 0x60) != 0) {
				fcn_0047ce50(*(void**) (p + 0x60));
			}
			fcn_0041ddd0(p);
			return;
		}
	}
}
