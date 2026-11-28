#include <stdio.h>
#include "Develop/Units/m_alloc/m_alloc.h"
#include "Develop/DieGildeAddOn/game/game_data.h"

extern int g_0063319c;
extern int g_006333cc;
extern int g_6b7d70;
extern int sb_WaveDriver;
extern volatile int gm_GameTicks;
extern int __cdecl sb_EnsureSampleMemory(int need);

typedef struct {
	unsigned int offset;
	char name[0x32];
	unsigned char type;
	unsigned char pad37;
	void* block;
	int mem;
} SB_LOAD_STATE;

typedef struct
{
    unsigned int offset;
    char name[0x32];
    unsigned char type;
    unsigned char pad37;
    void *block;
    int mem;
} SB_LOAD;

#if defined(REBREW_GOLD)
/* DATA TODO: 0x633190 (sample mem limit), 0x633194 (MemUsed), 0x1460920 (log buffer) */
/* ADDRESS: GOLD 0x00426660 */
int __cdecl sb_LoadEntry(char* a0, SB_LOAD_STATE* loadState)
{
	FILE* f;
	unsigned char hdr[12];
	unsigned char hdr2[12];
	void* blk;
	int rc;
	int size;
	int count;
	int i;
	int sum;

	sum = 0;
	blk = 0;
	rc = 0;
	if (g_0063319c == 0)
		return 0;
	if (loadState->block == 0 && a0 != 0) {
		f = fopen(a0 + 0x32, "rb");
		if (f != 0) {
			if (fseek(f, loadState->offset, 0) == 0) {
				if (loadState->type == 1) {
					if (fread(hdr, 0xc, 1, f) == 1) {
						count = *(int*) (hdr + 4);
						if (*(int*) 0x633190 - *(int*) 0x633194 < count + 0xc)
							sb_EnsureSampleMemory(count + 0xc);
						blk = m_alloc(count + 0xc, "sb_LoadEntry");
						if (blk != 0) {
							*(unsigned char*) blk = hdr[0];
							*(int*) ((char*) blk + 4) = count;
							*(void**) ((char*) blk + 8) = (char*) blk + 0xc;
							if (fread((char*) blk + 0xc, count, 1, f) == 1) {
								loadState->mem = g_006333cc * 13;
								*(int*) 0x633194 += count + 0xc;
								loadState->block = blk;
								fclose(f);
								return rc;
							}
							m_FreeTracked(blk);
							blk = 0;
							rc = -1;
						} else {
							sprintf((char*) 0x1460920, "sb_LoadEntry: m_alloc schlug fehl f\xfcr %s", loadState->name);
						}
					} else {
						rc = -1;
					}
					loadState->block = blk;
					fclose(f);
					return rc;
				}
				if (loadState->type == 2 && fread(hdr2, 0xc, 1, f) == 1) {
					size = *(int*) (hdr2 + 8);
					if (*(int*) 0x633190 - *(int*) 0x633194 < size + 0xc)
						rc = sb_EnsureSampleMemory(size + 0xc);
					blk = m_alloc(size + 0xc, "sb_LoadEntry");
					if (blk != 0) {
						*(int*) blk = *(int*) hdr2;
						*(int*) ((char*) blk + 8) = size;
						*(void**) ((char*) blk + 4) = (char*) blk + 0xc;
						if (fread((char*) blk + 0xc, size, 1, f) == 1) {
							for (i = 0; i < *(int*) blk; i++) {
								*(int*) (*(char**) ((char*) blk + 4) + i * 0xc + 8) =
									*(int*) ((char*) blk + 4) + *(int*) blk * 0xc + sum;
								sum += *(int*) (*(char**) ((char*) blk + 4) + i * 0xc + 4);
							}
							*(int*) 0x633194 += size + 0xc;
							loadState->mem = g_006333cc * 13;
							sprintf((char*) 0x1460920, "Variation %s loaded ! MemUsed is now %d bytes.", loadState->name, *(int*) 0x633194);
							loadState->block = blk;
							fclose(f);
							return rc;
						}
						m_FreeTracked(blk);
						blk = 0;
					}
					rc = -1;
					loadState->block = blk;
					fclose(f);
					return rc;
				}
			}
			rc = -1;
			fclose(f);
			return rc;
		}
	}
	rc = -1;
	return rc;
}
#else
/* ADDRESS: GOLDTL 0x00422ad0 */
/* ADDRESS: GOLDDE 0x0041f950 */
int __cdecl sb_LoadEntry(char *a0, SB_LOAD *loadState)
{
    FILE *f;
    unsigned char hdr[12];
    unsigned char hdr2[12];
    void *blk;
    int rc;
    int size;
    int count;
    int i;
    int sum;
    unsigned int mem_first;
    unsigned int mem_second;

    rc = 0;
    if (sb_WaveDriver == 0)
        return 0;
    if (loadState->block != 0 || a0 == 0)
        return -1;
    f = fopen(a0 + 0x32, (char *)0x6750e8);
    if (f == 0)
        return -1;
    if (fseek(f, loadState->offset, 0) != 0)
    {
        fclose(f);
        return -1;
    }
    if (loadState->type == 1)
    {
        if (fread(hdr, 0xc, 1, f) != 1)
        {
            fclose(f);
            loadState->block = 0;
            return -1;
        }
        count = *(int *)(hdr + 4);
        if (g_6b7d70 - MemUsed < count + 0xc)
            sb_EnsureSampleMemory(count + 0xc);
        blk = m_alloc(count + 0xc, (char *)0x678e94);
        if (blk == 0)
        {
            sprintf((char *)0x14cbae0, (char *)0x678e68, loadState->name);
            fclose(f);
            loadState->block = 0;
            return 0;
        }
        *(unsigned char *)blk = hdr[0];
        *(int *)((char *)blk + 4) = count;
        *(void **)((char *)blk + 8) = (char *)blk + 0xc;
        if (fread((char *)blk + 0xc, count, 1, f) != 1)
        {
            m_FreeTracked(blk);
            loadState->block = 0;
            fclose(f);
            return -1;
        }
        mem_first = gm_GameTicks;
        mem_second = gm_GameTicks;
        loadState->mem = (mem_first * 2 + mem_second) * 4 + gm_GameTicks;
        MemUsed += count + 0xc;
        loadState->block = blk;
        fclose(f);
        return 0;
    }
    if (loadState->type != 2)
    {
        fclose(f);
        return -1;
    }
    if (fread(hdr2, 0xc, 1, f) != 1)
    {
        fclose(f);
        return -1;
    }
    size = *(int *)(hdr2 + 8);
    if (g_6b7d70 - MemUsed < size + 0xc)
        rc = sb_EnsureSampleMemory(size + 0xc);
    blk = m_alloc(size + 0xc, (char *)0x678e94);
    if (blk == 0)
    {
        fclose(f);
        loadState->block = 0;
        return -1;
    }
    *(int *)((char *)blk + 8) = size;
    *(int *)blk = *(int *)hdr2;
    *(void **)((char *)blk + 4) = (char *)blk + 0xc;
    if (fread((char *)blk + 0xc, size, 1, f) != 1)
    {
        m_FreeTracked(blk);
        loadState->block = 0;
        fclose(f);
        return -1;
    }
    sum = 0;
    for (i = 0; i < *(int *)blk; i++)
    {
        *(int *)(*(char **)((char *)blk + 4) + i * 0xc + 8) =
            *(int *)((char *)blk + 4) + *(int *)blk * 0xc + sum;
        sum += *(int *)(*(char **)((char *)blk + 4) + i * 0xc + 4);
    }
    MemUsed += size + 0xc;
    mem_first = gm_GameTicks;
    mem_second = gm_GameTicks;
    loadState->mem = (mem_first * 2 + mem_second) * 4 + gm_GameTicks;
    sprintf((char *)0x14cbae0, (char *)0x678e38, loadState->name, MemUsed);
    loadState->block = blk;
    fclose(f);
    return rc;
}
#endif
