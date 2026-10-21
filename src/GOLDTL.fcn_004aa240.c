#include <string.h>

typedef struct
{
    int type;
    int pad[0x86];
    int *ptr;
} SAVE_REC;

extern int __cdecl fcn_004fa5b0(int cmd, int obj, void *rec);
extern int __cdecl gm_RandomMod(int limit);
extern void *__cdecl fcn_005463a0(int a, int b, int c);
extern void *__cdecl fcn_005462a0(void);
extern void *__cdecl fcn_00508e40(int a);
extern int __cdecl fcn_004a92c0(int a0, int obj, void *rec, char *out, int a4);
extern int __cdecl fcn_004a93a0(int a0, int obj, void *rec, char *out, int a4);
extern int __cdecl fcn_004a9470(int a0, int obj, void *rec, char *out, int a4);
extern int __cdecl fcn_004a9540(int a0, int obj, void *rec, char *out, int a4);
extern int __cdecl fcn_004a9600(int a0, int obj, void *rec, char *out, int a4);

/* ADDRESS: GOLDTL 0x004aa240 */
unsigned int __cdecl fcn_004aa240(int a0, int a1, int a2, char *a3, int a4)
{
    int n;
    unsigned short r;
    int ids1[3];
    int ids2[3];
    SAVE_REC rec;
    int *src;
    unsigned int id;
    int ok;
    char *q;
    int cc;

    memset(&rec, 0, sizeof rec);
    cc = 0;
    rec.ptr = 0;
    if (*(int *)(a1 + 0x1c8) & 0x100)
    {
        q = (char *)fcn_005463a0(1, 0, 0x45);
        while (q)
        {
            if (*(int *)(q + 0xac) == *(int *)(a1 + 4))
            {
                rec.ptr = (int *)fcn_00508e40(*(int *)(q + 0xb0));
                break;
            }
            q = (char *)fcn_005462a0();
        }
    }
    if (*a3 == 0)
    {
        n = 0;
        rec.type = 1;
        for (src = (int *)0x67faa4; (int)src < (int)0x67fab0; src++)
        {
            if (fcn_004fa5b0(*src, a1, &rec) & 2)
                ids1[n++] = *src;
        }
        if (rec.ptr)
        {
            rec.type = 2;
            cc = 0;
            for (src = (int *)0x67faa4; (int)src < (int)0x67fab0; src++)
            {
                if (fcn_004fa5b0(*src, a1, &rec) & 2)
                    ids2[cc++] = *src;
            }
        }
        if (n != 0 && (cc == 0 || (r = (unsigned short)gm_RandomMod(2)) == 0))
        {
            rec.type = 1;
            r = (unsigned short)gm_RandomMod(n);
            id = (unsigned int)ids1[r];
            n = 3;
            ok = fcn_004fa5b0((int)id, a1, &rec) & 2;
        }
        else if (cc != 0)
        {
            rec.type = 2;
            r = (unsigned short)gm_RandomMod(cc);
            id = (unsigned int)ids2[r];
            n = 4;
            ok = fcn_004fa5b0((int)id, a1, &rec) & 2;
        }
        else
            return 0;
        if (!ok)
            return 0;
        *a3 = 0x10;
        *(int *)(a3 + 4) = (int)id;
        *(int *)(a3 + 8) = n;
    }
    else
    {
        if (*a3 != 0x10)
            return 0;
        id = (unsigned int)*(int *)(a3 + 4);
        rec.type = 1;
        if (fcn_004fa5b0((int)id, a1, &rec) & 2)
            *(int *)(a3 + 8) = 3;
        else
        {
            rec.type = 2;
            if (!(fcn_004fa5b0((int)id, a1, &rec) & 2))
                return 0;
            *(int *)(a3 + 8) = 4;
        }
    }
    switch (id)
    {
    case 0:
        return fcn_004a92c0(a0, a1, &rec, a3, a4);
    case 3:
        return fcn_004a93a0(a0, a1, &rec, a3, a4);
    case 4:
        return fcn_004a9470(a0, a1, &rec, a3, a4);
    case 7:
        return fcn_004a9540(a0, a1, &rec, a3, a4);
    case 8:
        return fcn_004a9600(a0, a1, &rec, a3, a4);
    }
    return 0;
}
