#include <string.h>

typedef int (__stdcall* REG_SET_VALUE_FN)(int, int, int, int, char*, int);

extern REG_SET_VALUE_FN g_662008;


/* ADDRESS: GOLD 0x004104b0 */
/* ADDRESS: GOLDTL 0x00411520 */
void __cdecl io_WriteRegistryString(int key, int name, char* text)
{
	g_662008(key, name, 0, 1, text, strlen(text) + 1);
}
