#include <stdio.h>
#include "Develop/Units/m_alloc/m_alloc.h"

extern int g_6b7d70;
extern int g_6b7d74;
extern int g_6b7d7c;
extern int g_6b7fac;
extern int __cdecl fcn_00422910(int need);

typedef struct
{
    unsigned int offset;
    char name[0x32];
    unsigned char type;
    unsigned char pad37;
    void *block;
    int mem;
} SB_LOAD;

/* ADDRESS: GOLDTL 0x00422ad0 */
int __cdecl sb_LoadEntry(char *a0, SB_LOAD *a1)
{
    FILE *f;
    unsigned char hdr[12];
    void *blk;
    unsigned char *data;
    int size;
    int count;
    int i;
    int sum;

    if (g_6b7d7c == 0)
        return 0;
    if (a1->block != 0 || a0 == 0)
        return -1;
    f = fopen(a0 + 0x32, (char *)0x6750e8);
    if (f == 0)
        return -1;
    if (fseek(f, a1->offset, 0) != 0)
    {
        fclose(f);
        return -1;
    }
    if (a1->type == 1)
    {
        if (fread(hdr, 0xc, 1, f) != 1)
        {
            fclose(f);
            a1->block = 0;
            return -1;
        }
        count = *(int *)(hdr + 4);
        if (g_6b7d70 - g_6b7d74 < count + 0xc)
            fcn_00422910(count + 0xc);
        blk = m_alloc(count + 0xc, (char *)0x678e94);
        if (blk == 0)
        {
            sprintf((char *)0x14cbae0, (char *)0x678e68, a1->name);
            fclose(f);
            a1->block = 0;
            return 0;
        }
        *(unsigned char *)blk = hdr[0];
        *(int *)((char *)blk + 4) = count;
        *(void **)((char *)blk + 8) = (char *)blk + 0xc;
        if (fread((char *)blk + 0xc, count, 1, f) != 1)
        {
            m_FreeTracked(blk);
            a1->block = 0;
            fclose(f);
            return -1;
        }
        a1->mem = g_6b7fac * 13;
        g_6b7d74 += count + 0xc;
        a1->block = blk;
        fclose(f);
        return 0;
    }
    if (a1->type != 2)
    {
        fclose(f);
        return -1;
    }
    if (fread(hdr, 0xc, 1, f) != 1)
    {
        fclose(f);
        return -1;
    }
    size = *(int *)(hdr + 8);
    if (g_6b7d70 - g_6b7d74 < size + 0xc)
        fcn_00422910(size + 0xc);
    blk = m_alloc(size + 0xc, (char *)0x678e94);
    if (blk == 0)
    {
        fclose(f);
        a1->block = 0;
        return -1;
    }
    *(int *)blk = *(int *)hdr;
    *(void **)((char *)blk + 4) = (char *)blk + 0xc;
    *(int *)((char *)blk + 8) = size;
    if (fread((char *)blk + 0xc, size, 1, f) != 1)
    {
        m_FreeTracked(blk);
        a1->block = 0;
        fclose(f);
        return -1;
    }
    data = *(unsigned char **)((char *)blk + 4);
    count = *(int *)blk;
    sum = 0;
    for (i = 0; i < count; i++)
    {
        *(int *)(data + i * 0xc + 8) = (int)data + count * 0xc + sum;
        sum += *(int *)(data + i * 0xc + 4);
    }
    g_6b7d74 += size + 0xc;
    a1->mem = g_6b7fac * 13;
    sprintf((char *)0x14cbae0, (char *)0x678e38, a1->name, g_6b7d74);
    a1->block = blk;
    fclose(f);
    return 0;
}
