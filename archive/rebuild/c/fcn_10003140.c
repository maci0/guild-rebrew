#ifdef _MSC_VER
#include <windows.h>
#else
#include <stddef.h>

#ifndef __declspec
#define __declspec(x)
#endif

#ifndef __cdecl
#define __cdecl
#endif

#ifndef NULL
#define NULL ((void *)0)
#endif
#endif

/*
 * fcn_10003140 target metadata
 * VA start: 0x10003140
 * VA end:   0x10003161
 * Size:     33 bytes
 *
 * Original disassembly:
 * 0x10003140: 8b 44 24 04          mov    eax, [esp+0x4]
 * 0x10003144: 8b 4c 24 08          mov    ecx, [esp+0x8]
 * 0x10003148: 3b 48 04             cmp    ecx, [eax+0x4]
 * 0x1000314b: 73 11                jae    0x1000315e
 * 0x1000314d: 83 c0 10             add    eax, 0x10
 * 0x10003150: 85 c9                test   ecx, ecx
 * 0x10003152: 76 0c                jbe    0x10003160
 * 0x10003154: 8b 10                mov    edx, [eax]
 * 0x10003156: 49                   dec    ecx
 * 0x10003157: 8d 44 10 04          lea    eax, [eax+edx+0x4]
 * 0x1000315b: 75 f7                jne    0x10003154
 * 0x1000315d: c3                   ret
 * 0x1000315e: 33 c0                xor    eax, eax
 * 0x10003160: c3                   ret
 */

/*
 * Interpreted structure:
 * - (base + 0x04): unsigned entry count
 * - entries start at (base + 0x10)
 * - each entry begins with a 4-byte length field L, and the next entry begins at (entry + 4 + L)
 */

// FUNCTION: SERVER 0x10003140
void * __cdecl fcn_10003140(void *base, unsigned int index)
{
    unsigned char *p;
    unsigned char *result;
    unsigned int count;

    p = (unsigned char *)base;
    count = *(unsigned int *)(p + 4);

    if (index < count) {
        p += 0x10;
        result = p;

        if (index <= 0) {
            goto ret_result;
        }

        do {
            unsigned int len = *(unsigned int *)p;
            index--;
            p += (len + 4);
        } while (index != 0);

        return p;
    }

    result = NULL;

ret_result:
    return result;
}
