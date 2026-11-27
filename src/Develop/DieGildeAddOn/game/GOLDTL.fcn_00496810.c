#include "client_dialog_helpers.h"

int __cdecl abs(int);
int __cdecl ai_SelectBestMethod(int, int, int, Cmd*, Cmd*);
int __cdecl fcn_00502cd0(int, int, int, int, int);
int __cdecl gm_RandomMod(unsigned short);
float __cdecl gm_RandomFloat01(void);
int __cdecl gm_WalkEntityChain(unsigned short);
float __cdecl gm_CalcEntityFavor(unsigned int, unsigned int, unsigned int);
unsigned char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl ai_SelectRankedCandidates(unsigned short*, unsigned int, unsigned int*, float, float, unsigned short*);
int __cdecl amt_CollectOfficeCandidates(int, int, unsigned char**);
extern char* g_77261c;
extern float g_662910;
extern double g_662aa0;

/* ADDRESS: GOLDTL 0x00496810 */
int __cdecl ai_StartBestechung(int targetSlot, short* ent, int mode, Cmd* out1, Cmd* out2, int extra)
{
    Cmd c1;
    Cmd c2;
    unsigned char* list[6];
    unsigned char* e;
    int strength;
    int count;
    int best;
    int i;
    int r;
    int lower;
    int upper;
    int chosen;
    float best_value;
    float value;

    (void)extra;
    if (mode != 0) return 0;
    if (*(int*)((char*)ent + 0x170) == 0 && *((char*)ent + 2) != 3) {
        c1.kind = 0;
        c1.f1 = 0;
        c1.f2 = 0;
        c1.f5 = 0x3f28f5c3;
        c2.kind = 0;
        c2.f1 = 0;
        c2.f2 = 0;
        r = ai_SelectBestMethod(9, *(unsigned short*)ent, 1, &c1, &c2);
        goto sent;
    }
    if ((*(unsigned int*)((char*)ent + 0x1e8) & 0x400) != 0 &&
        (unsigned short)gm_RandomMod(8) != 0) return 0;
    if (*((char*)ent + 2) == 3) {
        if ((*((unsigned char*)ent + 0x1e8) & 2) == 0) return 0;
    } else if (fcn_00502cd0(*(int*)(*(char**)((char*)ent + 0x170) + 0x5d), 2, 6, 0, 0x14) == 0) {
        c1.kind = 2;
        c1.f1 = 0x14;
        c1.f2 = 1;
        c1.f5 = 0x3e6147ae;
        c2.kind = 4;
        c2.f1 = *(int*)(*(char**)((char*)ent + 0x170) + 1);
        c2.f2 = 1;
        r = ai_SelectBestMethod(9, *(unsigned short*)ent, 1, &c1, &c2);
        goto sent;
    }
    strength = (int)((float)gm_GetSeasonTreasury(ent, g_773d75) * 0.33f);
    if (out1->kind == 0) {
        if (*((unsigned char*)ent + 0x168) != 0) {
            best = -1;
            best_value = 100.0f;
            count = amt_CollectOfficeCandidates(*((unsigned char*)ent + 0x168), 6, list);
            if (count <= 0) return 0;
            for (i = 0; i < count; i++) {
                if (list[i] != (unsigned char*)g_77261c) {
                    value = gm_CalcEntityFavor(*(unsigned short*)ent, *(unsigned short*)list[i], 1);
                    if (value < best_value) {
                        best_value = value;
                        best = i;
                    }
                }
            }
            if (best < 0) return 0;
            e = list[best];
        } else {
            if ((*(unsigned int*)((char*)ent + 0x1cc) & 0x1c000) != 0) return 0;
            mode = 0x10000500;
            if (ai_SelectRankedCandidates((unsigned short*)ent, 1, (unsigned int*)&mode, 0.0f, (float)(unsigned short)gm_RandomMod(0x19) + g_662aa0, (unsigned short*)&targetSlot) == 0) return 0;
            e = (unsigned char*)0x7f4ca0 + *(unsigned short*)&targetSlot * 0x21c;
        }
        if (e == 0) return 0;
        out1->kind = 7;
        out1->f1 = *(int*)(e + 4);
        out1->f2 = 1;
        if ((float)abs(gm_WalkEntityChain(*(unsigned short*)ent) + gm_WalkEntityChain(*(unsigned short*)e)) * 0.0007843137f > 1600.0f) {
            value = (float)abs(gm_WalkEntityChain(*(unsigned short*)ent) + gm_WalkEntityChain(*(unsigned short*)e)) * 0.0007843137f;
        } else {
            value = 1600.0f;
        }
        lower = (int)value;
        if (lower > strength) return 0;
        upper = strength;
        if (strength >= lower + 320000) upper = lower + 320000;
        out2->kind = 0x12;
        out2->f1 = 0;
        chosen = (int)(gm_RandomFloat01() * (upper - lower) + lower);
        out2->f2 = chosen;
        out2->f4 = (int)((float)(unsigned int)chosen * 500.0f / (float)(gm_WalkEntityChain(*(unsigned short*)ent) + gm_WalkEntityChain(*(unsigned short*)e)));
        return 9;
    }
    if (out1->kind != 7) return 0;
    e = gm_LookupEntityRecordById(out1->f1);
    if (e == 0 || e == (unsigned char*)g_77261c) return 0;
    value = (float)strength * g_662910;
    if (!(value > 3200.0f)) value = 3200.0f;
    lower = (int)value;
    value = (float)strength * 0.15f;
    if (!(value < 160000.0f)) value = 160000.0f;
    out2->kind = 0x12;
    out2->f1 = 0;
    chosen = (int)(gm_RandomFloat01() * ((int)value - lower) + lower);
    out2->f2 = chosen;
    out2->f4 = (int)((float)(unsigned int)chosen * 500.0f / (float)(gm_WalkEntityChain(*(unsigned short*)ent) + gm_WalkEntityChain(*(unsigned short*)e)));
    return 9;

sent:
    if (r != 0) {
        *out1 = c1;
        *out2 = c2;
    }
    return r;
}
