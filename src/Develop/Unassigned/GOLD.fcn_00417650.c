#include "client_sound.h"
#include "Develop/Units/m_alloc/m_alloc.h"

/* ADDRESS: GOLD 0x00417650 */
int __cdecl fcn_00417650(int count)
{
    if (g_6b5d08 != 0)
        goto fail;
    if (count != 0)
        g_677680 = count;
    g_6b5d08 = (SOUND_SOURCE*) m_alloc(g_677680 * sizeof(SOUND_SOURCE), "d3snd_Init");
    if (g_6b5d08 == 0)
        goto fail;
    count = g_677680 * sizeof(SOUND_SOURCE);
    __asm {
        mov edi, g_6b5d08
        mov ebx, count
        xor eax, eax
        lea ecx, [edi+edi*2]
        and ecx, 3
        sub ebx, ecx
        jle short L1
        rep stosb
        mov ecx, ebx
        and ebx, 3
        shr ecx, 2
        rep stosd
    L1:
        add ecx, ebx
        rep stosb
    }
    return 0;
fail:
    return -1;
}
