#include <string.h>

typedef int (__stdcall* REG_SET_VALUE_FN)(int, int, int, int, char*, int);

extern REG_SET_VALUE_FN imp_RegSetValueExA;


/* ADDRESS: GOLD 0x004104b0 */
/* ADDRESS: GOLDTL 0x00411520 */
/* ADDRESS: GOLDDE 0x004101c0 */
void __cdecl io_WriteRegistryString(int key, int name, char* text)
{
	imp_RegSetValueExA(key, name, 0, 1, text, strlen(text) + 1);
}
