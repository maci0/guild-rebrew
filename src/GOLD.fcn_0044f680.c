#include "Develop/Units/m_alloc/m_alloc.h"

int __cdecl fcn_004011d0(void* stream, void* dst);

/* ADDRESS: GOLD 0x0044f680 */
void __cdecl fcn_0044f680(void* stream, char* object)
{
    int* count;

    count = (int*)(object + 0x14);
    fcn_004011d0(stream, count);
    if (*count > 0 && *(void**)(object + 0x20) == 0) {
        *(int*)(object + 0x18) = 0;
        *(int*)(object + 0x1c) = 0;
        *(void**)(object + 0x20) = m_alloc(0xe0000, (char*)0x5fc918);
    }
}
