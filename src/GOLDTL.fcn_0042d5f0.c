#include <string.h>

extern char g_149d120[][0x74];

void __cdecl fcn_0041ddd0(void* p);

// FUNCTION: GOLD 0x0042e2a0
// SIZE: 54
// FUNCTION: GOLDTL 0x42d5f0
// SIZE: 54
void __cdecl fcn_0042d5f0(void)
{
	int i;

	for (i = 0; i < 128; i++) {
		if (*(void**) (g_149d120[i] + 0x68) != 0) {
			fcn_0041ddd0(*(void**) (g_149d120[i] + 0x68));
			*(void**) (g_149d120[i] + 0x68) = 0;
			memset(g_149d120[i], 0, 0x74);
		}
	}
}
