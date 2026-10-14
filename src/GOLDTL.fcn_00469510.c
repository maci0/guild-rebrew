/* ADDRESS: GOLDTL 0x0102cbc0 */
extern char g_102cbc0[];
/* ADDRESS: GOLD 0x00fa5aa0 */
extern char g_102cbc0[];



#include <string.h>

#pragma intrinsic(memcpy, memset)

void __cdecl fcn_00469510(int i)
{
	memset((void*) (g_102cbc0 + i * 140), 0, 0x8c);
}
