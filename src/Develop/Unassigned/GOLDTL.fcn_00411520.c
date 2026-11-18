#include <string.h>

typedef int (__stdcall* fcn_00411520_fn)(int, int, int, int, char*, int);

extern fcn_00411520_fn g_662008;


/* ADDRESS: GOLD 0x004104b0 */
/* ADDRESS: GOLDTL 0x00411520 */
void __cdecl fcn_00411520(int a1, int a2, char* text)
{
	g_662008(a1, a2, 0, 1, text, strlen(text) + 1);
}
