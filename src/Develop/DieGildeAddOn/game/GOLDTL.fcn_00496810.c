#include "client_dialog_helpers.h"

int __cdecl fcn_00495400(int, int, int, Cmd*, Cmd*);
int __cdecl fcn_00502cd0(int, int, int, int, int);
int __cdecl gm_RandomMod(unsigned short);
double __cdecl gm_RandomFloat01(void);
int __cdecl gm_WalkEntityChain(unsigned short);
float __cdecl fcn_0050f980(unsigned int, unsigned int, unsigned int);
unsigned char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl fcn_004a5340(unsigned short*, unsigned int, unsigned int*, float, float, unsigned short*);
int __cdecl fcn_004e9310(int, int, unsigned char**);
extern char* g_77261c;

/* ADDRESS: GOLDTL 0x00496810 */
int __cdecl fcn_00496810(int a1, short* ent, int mode, Cmd* out1, Cmd* out2, int extra)
{
    Cmd c1;
    Cmd c2;
    unsigned char* list[6];
    unsigned char* e;
    unsigned int mask;
    unsigned int magnitude;
    unsigned short picked;
    int strength;
    int count;
    int best;
    int i;
    int r;
    int sum;
    int lower;
    int upper;
    int chosen;
    float best_value;
    float value;

    (void)a1;
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
        goto send;
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
        goto send;
    }
    strength = (int)((float)fcn_0050d320(ent, g_773d75) * 0.33f);
    if (out1->kind == 0) {
        if (*((unsigned char*)ent + 0x168) != 0) {
            count = fcn_004e9310(*((unsigned char*)ent + 0x168), 6, list);
            if (count <= 0) return 0;
            best = -1;
            best_value = 100.0f;
            for (i = 0; i < count; i++) {
                if (list[i] != (unsigned char*)g_77261c) {
                    value = fcn_0050f980(*(unsigned short*)ent, *(unsigned short*)list[i], 1);
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
            mask = 0x10000500;
            i = (unsigned short)gm_RandomMod(0x19);
            if (fcn_004a5340((unsigned short*)ent, 1, &mask, 0.0f, (float)i + 10.0, &picked) == 0) return 0;
            e = (unsigned char*)0x7f4ca0 + picked * 0x21c;
        }
        if (e == 0) return 0;
        out1->kind = 7;
        out1->f1 = *(int*)(e + 4);
        out1->f2 = 1;
        sum = gm_WalkEntityChain(*(unsigned short*)ent);
        sum += gm_WalkEntityChain(*(unsigned short*)e);
        magnitude = (sum ^ (sum >> 31)) - (sum >> 31);
        if ((float)(int)magnitude * 0.0007843137f > 1600.0f) {
            sum = gm_WalkEntityChain(*(unsigned short*)ent);
            sum += gm_WalkEntityChain(*(unsigned short*)e);
            magnitude = (sum ^ (sum >> 31)) - (sum >> 31);
            value = (float)(int)magnitude * 0.0007843137f;
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
        value = (float)(unsigned int)chosen * 500.0f;
        sum = gm_WalkEntityChain(*(unsigned short*)ent);
        sum += gm_WalkEntityChain(*(unsigned short*)e);
        out2->f4 = (int)(value / (float)sum);
        return 9;
    }
    if (out1->kind != 7) return 0;
    e = gm_LookupEntityRecordById(out1->f1);
    if (e == 0 || e == (unsigned char*)g_77261c) return 0;
    value = (float)strength * 0.01f;
    if (!(value > 3200.0f)) value = 3200.0f;
    lower = (int)value;
    value = (float)strength * 0.15f;
    if (!(value < 160000.0f)) value = 160000.0f;
    out2->kind = 0x12;
    out2->f1 = 0;
    chosen = (int)(gm_RandomFloat01() * ((int)value - lower) + lower);
    out2->f2 = chosen;
    value = (float)(unsigned int)chosen * 500.0f;
    sum = gm_WalkEntityChain(*(unsigned short*)ent);
    sum += gm_WalkEntityChain(*(unsigned short*)e);
    out2->f4 = (int)(value / (float)sum);
    return 9;

send:
    r = fcn_00495400(9, *(unsigned short*)ent, 1, &c1, &c2);
    if (r == 0) return 0;
    *out1 = c1;
    *out2 = c2;
    return r;
}
