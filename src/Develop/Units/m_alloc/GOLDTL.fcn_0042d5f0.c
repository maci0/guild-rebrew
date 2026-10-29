#include <string.h>

extern char g_149d120[][0x74];

void __cdecl m_FreeTracked(void* p);

/* ADDRESS: GOLDTL 0x0042d5f0 */
void __cdecl fcn_0042d5f0(void)
{
	int i;

	for (i = 0; i < 128; i++) {
		if (*(void**) (g_149d120[i] + 0x68) != 0) {
			m_FreeTracked(*(void**) (g_149d120[i] + 0x68));
			*(void**) (g_149d120[i] + 0x68) = 0;
			memset(g_149d120[i], 0, 0x74);
		}
	}
}
