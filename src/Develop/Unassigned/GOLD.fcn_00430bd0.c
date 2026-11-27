#include <stdio.h>
#include <string.h>
#include "zlib.h"
#include "contrib/minizip/unzip.h"

int __cdecl fcn_004616e0(z_streamp, int);

/* ADDRESS: GOLD 0x00430bd0 */
unsigned int __cdecl vfs_ReadData(void* buffer, unsigned int size,
    unsigned int count, char* file)
{
    unsigned int bytes;
    unsigned int result;
    unsigned char flags;
    unsigned char memory;
    void* copySrc;
    char text[0x100];

    result = (unsigned int) -1;
    if (!file)
        goto done;
    flags = (unsigned char) file[0x13c];
    if (!(flags & 1) || (!*(void**) (file + 0x100) && !(flags & 0x20)))
        goto done;
    bytes = size * count;
    memory = (flags >> 5) & 1;
    if (memory && !(flags & 8) && *(unsigned int*) (file + 0x104) < bytes)
        bytes = *(unsigned int*) (file + 0x104);
    if (!bytes) {
        result = bytes;
        goto done;
    }
    if (!buffer)
        goto done;
    if (memory) {
        if (flags & 8) {
            *(void**) (file + 0x10c) = buffer;
            *(unsigned int*) (file + 0x110) = bytes;
            fcn_004616e0((z_streamp) (file + 0x100), 2);
            result = bytes - *(unsigned int*) (file + 0x110);
            goto done;
        }
        copySrc = *(void**) (file + 0x100);
        /* Reviewed original operand-homed copy core at 0x430c99..ba. */
        __asm {
            mov edi, buffer
            mov esi, copySrc
            mov ebx, bytes
            lea ecx, [edi+edi*2]
            and ecx, 3
            sub ebx, ecx
            jle short read_tail
            rep movsb
            mov ecx, ebx
            and ebx, 3
            shr ecx, 2
            rep movsd
        read_tail:
            add ecx, ebx
            rep movsb
        }
        result = bytes;
        *(char**) (file + 0x100) += bytes;
        {
            unsigned int avail;
            unsigned int consumed;
            avail = *(unsigned int*) (file + 0x104);
            consumed = *(unsigned int*) (file + 0x108);
            avail -= bytes;
            consumed += bytes;
            *(unsigned int*) (file + 0x104) = avail;
            *(unsigned int*) (file + 0x108) = consumed;
        }
        goto done;
    }
    if (flags & 0x10) {
        result = unzReadCurrentFile(*(unzFile*) (file + 0x100), buffer, bytes);
        if ((file[0x13c] & 4) && result >= 2) {
            file[0x13c] &= 0xfb;
            if (((unsigned char*) buffer)[0] == *(int*) 0x5f9004 &&
                ((unsigned char*) buffer)[1] == *(int*) 0x5f9008)
                sprintf(text, "vfs: gz-compressed file (\"%s\") in zip found!", file);
        }
        goto done;
    }
    if (flags & 8) {
        result = gzread(*(gzFile*) (file + 0x100), buffer, bytes);
        goto done;
    }
    result = fread(buffer, size, count, *(FILE**) (file + 0x100));
done:
    return result;
}
