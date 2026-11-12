#include <windows.h>
#include "Develop/Units/m_alloc/m_alloc.h"

/* ADDRESS: GOLD 0x0045ef50 */
void __cdecl fcn_0045ef50(char* object)
{
    if (!object)
        return;
    if (object == *(char**)0x633df8)
        OutputDebugStringA("d3sm_Destroy(shadow)\n");
    else
        OutputDebugStringA("d3sm_Destroy\n");
    if (*(void**)(object + 0x24)) {
        m_FreeTracked(*(void**)(object + 0x24));
        *(void**)(object + 0x24) = 0;
    }
    if (*(void**)(object + 0x28)) {
        m_FreeTracked(*(void**)(object + 0x28));
        *(void**)(object + 0x28) = 0;
    }
    m_FreeTracked(object);
}
