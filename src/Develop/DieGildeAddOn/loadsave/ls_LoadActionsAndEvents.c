extern int he_LastEventSlot, g_7749d8, g_7dc424;
void __cdecl he_FreeAllActions(void);
int __cdecl ls_ReadVfsDataChecked(void *, int, int, void *);
#include "Develop/Units/m_alloc/m_alloc.h"
extern int ls_SaveVersion;

/* ADDRESS: GOLDTL 0x00524b50 */
/* ADDRESS: GOLDDE 0x0050de20 */
int __cdecl ls_LoadActionsAndEvents(unsigned char *S)
{
    unsigned char *rec, *p;
    int cnt, c2, i, j;

    he_FreeAllActions();
    if (!ls_ReadVfsDataChecked(&cnt, 4, 1, S))
        return 0;
    if (!ls_ReadVfsDataChecked(&c2, 4, 1, S))
        return 0;
    he_LastEventSlot = 0;
    g_7749d8 = 0;
    g_7dc424 = 0;
    i = 0;
    if (cnt > 0) {
        do {
            rec = (unsigned char *)0x77e980 + i * 0x14c;
            if (!ls_ReadVfsDataChecked(rec + 0x00, 1, 1, S))
                return 0;
            if (!ls_ReadVfsDataChecked(rec + 0x04, 4, 1, S))
                return 0;
            if (!ls_ReadVfsDataChecked(rec + 0x08, 2, 1, S))
                return 0;
            if (!ls_ReadVfsDataChecked(rec + 0x0c, 4, 1, S))
                return 0;
            if (!ls_ReadVfsDataChecked(rec + 0x10, 4, 1, S))
                return 0;
            if (!ls_ReadVfsDataChecked(rec + 0x14, 0x30, 1, S))
                return 0;
            if (!ls_ReadVfsDataChecked(rec + 0x44, 0x0e, 1, S))
                return 0;
            if (!ls_ReadVfsDataChecked(rec + 0x52, 0x0e, 1, S))
                return 0;
            if (!ls_ReadVfsDataChecked(rec + 0x60, 0x0e, 1, S))
                return 0;
            if (!ls_ReadVfsDataChecked(rec + 0x70, 4, 1, S))
                return 0;
            if (!ls_ReadVfsDataChecked(rec + 0x78, 1, 1, S))
                return 0;
            if (ls_SaveVersion >= 0x1002f) {
                for (j = 0; j < 8; j++)
                    if (!ls_ReadVfsDataChecked(rec + 0x8c + 4 * j, 4, 1, S))
                        return 0;
            }
            *(int *)(rec + 0x7c) = 0;
            *(int *)(rec + 0x80) = 0;
            if (!ls_ReadVfsDataChecked(rec + 0x80, 4, 1, S))
                return 0;
            if (*(int *)(rec + 0x80) != 0) {
                p = (unsigned char *)m_alloc(0x400, (char*)0x68af74);
                *(unsigned char **)(rec + 0x7c) = p;
                if (!ls_ReadVfsDataChecked(p, *(int *)(rec + 0x80), 1, S))
                    return 0;
            }
            if (*(unsigned char *)(rec + 0x00) == 0x0c) {
                if (!ls_ReadVfsDataChecked(rec + 0xac, c2, 1, S))
                    return 0;
                *(unsigned char **)(rec + 0xbc) =
                    (unsigned char *)m_alloc(0x58, (char*)0x6a24b4);
            } else if (*(unsigned char *)(rec + 0x00) == 0x0d) {
                if (!ls_ReadVfsDataChecked(rec + 0xac, c2, 1, S))
                    return 0;
                *(int *)(rec + 0xbc) = -1;
                if (*(int *)(rec + 0x70) == 6)
                    *(unsigned char *)(rec + 0xd0) = 0;
            } else {
                if (!ls_ReadVfsDataChecked(rec + 0xac, c2, 1, S))
                    return 0;
            }
            if (*(unsigned char *)(rec + 0x78) & 8) {
                *(unsigned char **)(0x7d1980 + 4 * g_7749d8) = rec;
                g_7749d8 += 1;
            }
            i = g_7dc424 + 1;
            g_7dc424 = i;
        } while (i < cnt);
    }
    he_LastEventSlot = i;
    if (!ls_ReadVfsDataChecked(&cnt, 4, 1, S))
        return 0;
    if (cnt > 0) {
        for (i = 0; i < cnt; i++) {
            rec = (unsigned char *)0x7d2020 + i * 0xa4;
            *(int *)rec = 0;
            if (!ls_ReadVfsDataChecked(rec + 0x00, 4, 1, S))
                return 0;
            if (!ls_ReadVfsDataChecked(rec + 0x04, 1, 1, S))
                return 0;
            if (!ls_ReadVfsDataChecked(rec + 0x08, 4, 1, S))
                return 0;
            if (!ls_ReadVfsDataChecked(rec + 0x0c, 4, 1, S))
                return 0;
            if (!ls_ReadVfsDataChecked(rec + 0x10, 4, 1, S))
                return 0;
            if (!ls_ReadVfsDataChecked(rec + 0x14, 0x0e, 1, S))
                return 0;
            if (!ls_ReadVfsDataChecked(rec + 0x22, 0x80, 1, S))
                return 0;
        }
    }
    if (!ls_ReadVfsDataChecked(&cnt, 4, 1, S))
        return 0;
    if (cnt > 0) {
        for (i = 0; i < cnt; i++) {
            rec = (unsigned char *)0x7dcae4 + i * 0x50;
            if (!ls_ReadVfsDataChecked(rec - 4, 1, 1, S))
                return 0;
            if (!ls_ReadVfsDataChecked(rec + 0x00, 4, 1, S))
                return 0;
            if (!ls_ReadVfsDataChecked(rec + 0x04, 4, 1, S))
                return 0;
            if (!ls_ReadVfsDataChecked(rec + 0x08, 4, 1, S))
                return 0;
            if (!ls_ReadVfsDataChecked(rec + 0x0c, 0x40, 1, S))
                return 0;
        }
    }
    return 1;
}
