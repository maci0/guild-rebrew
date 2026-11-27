#include <string.h>

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x004d8b30 */
void __cdecl cut_ResetCharacterSlots(void)
{
	memset((void*) 0x92ca80, 0, 0x40);
}
#else
/* ADDRESS: GOLDTL 0x004da190 */
void __cdecl cut_ResetCharacterSlots(void)
{
	memset((void*) 0x9b0dc0, 0, 0x40);
}
#endif
