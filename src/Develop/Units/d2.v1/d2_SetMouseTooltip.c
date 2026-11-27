#include <string.h>

extern char g_f8aae0[];

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x00478860 */
void __cdecl d2_SetMouseTooltip(char* text)
{
	strcpy(g_f8aae0, text);
}
#else
/* ADDRESS: GOLDTL 0x00475220 */
void __cdecl d2_SetMouseTooltip(char* text)
{
	strcpy((char*) 0x100f8c0, text);
}
#endif
