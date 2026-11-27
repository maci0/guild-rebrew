#include <string.h>

typedef struct
{
    int type;
    int pad[0x86];
    int *ptr;
} SAVE_REC;

extern int __cdecl gm_CheckPrivilege(int cmd, int obj, void *rec);
extern int __cdecl gm_RandomMod(int limit);
extern void *__cdecl he_StartHandlungSearch(int a, int b, int c);
extern void *__cdecl he_fn_Handlung(void);
extern void *__cdecl gm_LookupEntityRecordById(int a);
extern int __cdecl ai_PreparePrivBeleidigung(int a0, int obj, void *rec, char *out, int a4);
extern int __cdecl ai_PreparePriv0x03(int a0, int obj, void *rec, char *out, int a4);
extern int __cdecl fcn_004a9470(int a0, int obj, void *rec, char *out, int a4);
extern int __cdecl fcn_004a9540(int a0, int obj, void *rec, char *out, int a4);
extern int __cdecl ai_PreparePrivWerbung(int a0, int obj, void *rec, char *out, int a4);

/* ADDRESS: GOLDTL 0x004aa240 */
unsigned int __cdecl ai_SelectPrivTarget(int unused0, int entity, int unused2, char *request, int extraOut)
{
    int n;
    unsigned short r;
    struct { int cc; int ids1[3]; int ids2[3]; } s;
    SAVE_REC rec;
    int *src;
    unsigned int id;
    int ok;
    char *q;

    memset(&rec, 0, sizeof rec);
    s.cc = 0;
    rec.ptr = 0;
    if (*(int *)(entity + 0x1c8) & 0x100)
    {
        q = (char *)he_StartHandlungSearch(1, 0, 0x45);
        while (q)
        {
            if (*(int *)(q + 0xac) == *(int *)(entity + 4))
            {
                rec.ptr = (int *)gm_LookupEntityRecordById(*(int *)(q + 0xb0));
                break;
            }
            q = (char *)he_fn_Handlung();
        }
    }
    if (*request == 0)
    {
        n = 0;
        rec.type = 1;
        for (src = (int *)0x67faa4; (int)src < (int)0x67fab0; src++)
        {
            if (gm_CheckPrivilege(*src, entity, &rec) & 2)
                s.ids1[n++] = *src;
        }
        if (rec.ptr)
        {
            rec.type = 2;
            s.cc = 0;
            for (src = (int *)0x67faa4; (int)src < (int)0x67fab0; src++)
            {
                if (gm_CheckPrivilege(*src, entity, &rec) & 2)
                    s.ids2[s.cc++] = *src;
            }
        }
        if (n != 0 && (s.cc == 0 || (r = (unsigned short)gm_RandomMod(2)) == 0))
        {
            rec.type = 1;
            r = (unsigned short)gm_RandomMod(n);
            id = (unsigned int)s.ids1[r];
            n = 3;
            ok = gm_CheckPrivilege((int)id, entity, &rec) & 2;
        }
        else if (s.cc != 0)
        {
            rec.type = 2;
            r = (unsigned short)gm_RandomMod(s.cc);
            id = (unsigned int)s.ids2[r];
            n = 4;
            ok = gm_CheckPrivilege((int)id, entity, &rec) & 2;
        }
        else
            return 0;
        if (!ok)
            return 0;
        *request = 0x10;
        *(int *)(request + 4) = (int)id;
        *(int *)(request + 8) = n;
    }
    else
    {
        if (*request != 0x10)
            return 0;
        id = (unsigned int)*(int *)(request + 4);
        rec.type = 1;
        if (gm_CheckPrivilege((int)id, entity, &rec) & 2)
            *(int *)(request + 8) = 3;
        else
        {
            rec.type = 2;
            if (!(gm_CheckPrivilege((int)id, entity, &rec) & 2))
                return 0;
            *(int *)(request + 8) = 4;
        }
    }
    switch (id)
    {
    case 0:
        return ai_PreparePrivBeleidigung(unused0, entity, &rec, request, extraOut);
    case 3:
        return ai_PreparePriv0x03(unused0, entity, &rec, request, extraOut);
    case 4:
        return fcn_004a9470(unused0, entity, &rec, request, extraOut);
    case 7:
        return fcn_004a9540(unused0, entity, &rec, request, extraOut);
    case 8:
        return ai_PreparePrivWerbung(unused0, entity, &rec, request, extraOut);
    }
    return 0;
}
