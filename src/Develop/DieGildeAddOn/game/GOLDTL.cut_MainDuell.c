/* cut_MainDuell — duel cutscene driver: creates the two duelant entities from
   the 0x21c-byte entity snapshots, builds the intro dialog pages and scores the
   duel. */
typedef struct {
    int  id;                /* +0x000  entity id (low word used) */
    int  idx;               /* +0x004  lookup key for fcn_004e6a70 */
    char pad8[0x1c];
    int  acc;               /* +0x024  accumulated duel score */
    char pad28[0x15c];
    int  entity;            /* +0x184  created entity object */
    char pad188[0x94];
} Snap;                     /* 0x21c */

typedef struct {
    int v[6];
} Chunk24;

extern int g_772f3c;
extern unsigned char g_772f58;
extern unsigned char g_772f59;
extern unsigned char g_772f5a;
extern unsigned char g_772f5b;
extern unsigned char g_772f5c;
extern unsigned char g_772f5d;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_68bfc0;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern int g_9afde0;
extern int g_9afde4;

unsigned short __cdecl gm_RandomMod(int a);
char* __cdecl gm_LookupEntityRecordById(int id);
void __cdecl fcn_004e04f0(char* a0);
void __cdecl fcn_004e4f10(void* event);
void __cdecl fcn_004e4730(char* name);
void __cdecl fcn_004dfef0(int v);
void __cdecl d3_UpdateSeasonTextures(void);
int __cdecl gm_GetSeason(int* p);
int __cdecl fcn_00445f50(unsigned int a0, float t, float scale, int a3);
char __cdecl fcn_004463f0(unsigned int a, unsigned int b, float t);
void __cdecl fcn_004cfe00(void);
void __cdecl msx_StartMusicIfAllowed(char* s);
void* __cdecl sb_LoadSampleBank(char* name, int init);
int __cdecl sb_LoadLocalizedSampleBank(char* name, int x);
int __cdecl fcn_004e4470(char* name);
int __cdecl fcn_004fe2e0(char* a0, int a1, int* a2, int* a3, int a4, int* a5);
void __cdecl ch_SetBodyAttachment(char* e, int mode, char* name);
int __cdecl d2_SetForm(int k, int i);
void __cdecl io_AppendText(int a, ...);
int __cdecl fcn_0064d41a(char* out, char* fmt, ...);
int __cdecl fcn_004e4b20(int a, int b, char* c, int d);
int __cdecl sb_CheckVoicePlaying(int* a);
void __cdecl cut_WaitTicks(int dur);
char* __cdecl fcn_00445600(int o, int flags, int ptr, char* name);
void __cdecl ch_QueueWalkToDummy(char* owner, char* text);
char* __cdecl ch_CreateAction(char* e, int kind, int p);
char* __cdecl ch_CreateQueuedAction(char* e, int a, int b, int c, int d);
int __cdecl d3snd_PlaySoundEffect(int a, int b, int c, int d);
void __cdecl cm_RequestCopyEntityData(int a, int b, int c, int d);
void __cdecl cut_RunTurnRound(unsigned int* a0, int a1);
int __cdecl fcn_004e6a70(int a1);
int __cdecl fcn_004de610(int v);
float __cdecl gm_GetEntityHealthRatio(char* p);
float __cdecl fcn_004ff210(int a, int b);
int __cdecl cut_RandMod(int n);
void __cdecl cut_PlayDuelIntroMove(char* a, char* b, char* c);
int __cdecl srv_GetEntityOfficeSlot(char* ent, int* role, int* slot);
int __cdecl amt_SendOfficeCommand(int id, int ea, int eb, int x1, int x2);
void __cdecl io_FormatTextBuffer(char* out, int id, int a, int b);
int __cdecl he_PostEntityMessage(int id, int arg, char* t1, int flags, int value, char* t2);
int __cdecl fcn_004e4aa0(int a);
void __cdecl fcn_004e4610(int a);
void __cdecl fcn_004e45c0(int a);
void __cdecl cut_CleanupCutscene(void);
void __cdecl fcn_004e48b0(void);
void __cdecl fcn_004230e0(char* p);
void __cdecl fcn_004cfe20(void);
void __cdecl ReportClientMessage(char* msg);
int __cdecl msx_RestoreMusicIfAllowed(void);

/* ADDRESS: GOLDTL 0x004e0620 */
void __cdecl cut_MainDuell(char* a0)
{
    int keepB;
    int bank;
    char* other;
    int event;
    int keepA;
    int snd;
    char scene[6][0x20] = {
        { "duell.ed3" }, { "duell.ed3" }, { "duell.ed3" },
        { "duell.ed3" }, { "duell.ed3" }, { "duell.ed3" }
    };
    int outS[6];
    Snap sA;
    Snap sB;
    int outR[6];
    char buf1[0xc8];
    char buf2[0x400];
    char* e1;
    char* e2;
    char* p;
    char* e;
    char* q;
    int sel;
    int sel0;
    int lvl;
    int i;
    int j;
    int n;
    int t;

    keepA = 0;
    keepB = 0;
    sel0 = gm_RandomMod(3) - 5;
    other = 0;
    e1 = gm_LookupEntityRecordById(*(int*) (a0 + 0x34));
    e2 = gm_LookupEntityRecordById(*(int*) (a0 + 0x38));
    if (e1 == 0 || e2 == 0)
        goto fail;
    if (g_772f3c != 0) {
        fcn_004e04f0(a0);
        return;
    }
    fcn_004e4f10(a0);
    lvl = (signed char) a0[0x7c];
    fcn_004e4730(scene[lvl]);
    fcn_004dfef0(0xa);
    d3_UpdateSeasonTextures();
    sel = gm_GetSeason((int*) 0x7f4c00);
    if (sel == 3)
        sel = 0;
    else if (sel == 0 || sel == 2)
        sel = 1;
    else if (sel == 1)
        sel = 2;
    fcn_00445f50(sel, 0.0f, 1.0f, 1);
    fcn_004463f0(0, 1, 0.0f);
    fcn_004cfe00();
    if (sel == 0)
        msx_StartMusicIfAllowed((char*) 0x68ce24);
    else if (sel == 1)
        msx_StartMusicIfAllowed((char*) 0x68bd2c);
    else
        msx_StartMusicIfAllowed((char*) 0x68bd14);

    snd = (int) sb_LoadSampleBank((char*) 0x68ce14, 0);
    bank = sb_LoadLocalizedSampleBank((char*) 0x68ce08, 0);
    event = fcn_004e4470((char*) 0x68cde8);

    e1 = gm_LookupEntityRecordById(*(int*) (a0 + 0x34));
    e2 = gm_LookupEntityRecordById(*(int*) (a0 + 0x38));
    sB = *(Snap*) e1;
    sA = *(Snap*) e2;
    g_9afde4 = (int) &sB;
    g_9afde0 = (int) &sA;
    g_772f58 = 0;
    g_772f59 = 0;
    fcn_004fe2e0((char*) &sB, d3_CurrentContextIndex, 0, 0, 0, (int*) 0x68cdd0);
    fcn_004fe2e0((char*) &sA, d3_CurrentContextIndex, 0, 0, 0, (int*) 0x68cdb8);
    if (sB.entity != 0 && sA.entity != 0) {
    ch_SetBodyAttachment((char*) sB.entity, 2, (char*) 0x68cdac);
    *(unsigned char*) (sB.entity + 0x240) = 4;
    ch_SetBodyAttachment((char*) sA.entity, 2, (char*) 0x68cdac);
    *(unsigned char*) (sA.entity + 0x240) = 4;

    i = 0;
    lvl = lvl * 3 + 0x10cb;
    do {
        d2_SetForm(g_68bfc0, 0);
        io_AppendText(0x6811b0);
        io_AppendText(lvl + i);
        fcn_0064d41a(buf1, (char*) 0x68cd94, i);
        p = (char*) fcn_004e4b20(-7, 0, buf1, -1);
        if (p != 0) {
            while (sb_CheckVoicePlaying((int*) p) != 0)
                cut_WaitTicks(2);
        }
        i++;
    } while (i < 3);

    ch_QueueWalkToDummy((char*) sB.entity, fcn_00445600(0, 0x100, 0, (char*) 0x68cd80));
    ch_CreateAction((char*) sB.entity, 0x35, fcn_00445600(0, 0x100, 0, (char*) 0x68cd68));
    ch_QueueWalkToDummy((char*) sA.entity, fcn_00445600(0, 0x100, 0, (char*) 0x68cd54));
    ch_CreateAction((char*) sA.entity, 0x35, fcn_00445600(0, 0x100, 0, (char*) 0x68cd3c));

    d2_SetForm(g_68bfc0, 0);
    io_AppendText(0x6811b0);
    io_AppendText(0x10dd);
    cut_WaitTicks(4);
    io_AppendText(0x6811b0);
    d3snd_PlaySoundEffect(-7, 0, (int) 0x68cd18, -1);

    cut_RunTurnRound((unsigned int*) a0, 0);
    e = (char*) fcn_004e6a70(sB.idx);
    if (*(unsigned char*) (e + 0x94) == 1)
        p = fcn_00445600(0, 0x100, 0, (char*) 0x68cd00);
    else
        p = fcn_00445600(0, 0x100, 0, (char*) 0x68cd68);
    ch_QueueWalkToDummy((char*) sB.entity, p);
    ch_CreateAction((char*) sB.entity, 0x35, *(int*) (sA.entity + 0x34));
    if (*(unsigned char*) (e + 0x94) == 1) {
        t = fcn_004de610(6);
        d2_SetForm(g_68bfc0, 0);
        io_AppendText(t + 0x10df);
        io_AppendText(0x68b300);
        d3snd_PlaySoundEffect(sel0, bank, (int) 0x68cce4, t);
        p = ch_CreateQueuedAction((char*) sB.entity, 0x4dff50, 6, 0x2e, 1);
        *(int*) (p + 0x180) = (int) &sB;
        *(int*) (p + 0x17c) = (int) &sA;
        *(Chunk24*) (p + 0xf0) = *(Chunk24*) 0x68cc34;
        keepA = 1;
    }

    e = (char*) fcn_004e6a70(sA.idx);
    if (*(unsigned char*) (e + 0x94) == 1)
        p = fcn_00445600(0, 0x100, 0, (char*) 0x68cccc);
    else
        p = fcn_00445600(0, 0x100, 0, (char*) 0x68cd3c);
    ch_QueueWalkToDummy((char*) sA.entity, p);
    ch_CreateAction((char*) sA.entity, 0x35, *(int*) (sB.entity + 0x34));
    if (*(unsigned char*) (e + 0x94) == 1) {
        t = fcn_004de610(6);
        d2_SetForm(g_68bfc0, 0);
        io_AppendText(t + 0x10df);
        d3snd_PlaySoundEffect(sel0, bank, (int) 0x68cce4, t);
        p = ch_CreateQueuedAction((char*) sA.entity, 0x4dff50, 6, 0x2e, 1);
        *(int*) (p + 0x180) = (int) &sA;
        *(int*) (p + 0x17c) = (int) &sB;
        *(Chunk24*) (p + 0xf0) = *(Chunk24*) 0x68cc34;
        keepB = 1;
    }

    cut_WaitTicks(6);
    j = 0;
    g_772f44 = 0;
    while (j < 3) {
        if (g_772f44 != 0)
            break;
        cut_RunTurnRound((unsigned int*) a0, (int) a0);
        e = (char*) fcn_004e6a70(sA.idx);
        g_772f5a = 0;
        g_772f5b = 0;
        g_772f5c = 0;
        g_772f5d = 0;
        if (*(unsigned char*) (e + 0x94) == 2 || *(unsigned char*) (e + 0x94) == 3) {
            cut_PlayDuelIntroMove((char*) &sA, (char*) &sB, (char*) 0x68ccc4);
            cut_PlayDuelIntroMove((char*) &sB, (char*) &sA, (char*) 0x68ccc8);
        } else {
            cut_PlayDuelIntroMove((char*) &sB, (char*) &sA, (char*) 0x68ccc8);
            cut_PlayDuelIntroMove((char*) &sA, (char*) &sB, (char*) 0x68ccc4);
        }
        if ((g_772f5a != 0 || g_772f5c != 0) && (g_772f5b != 0 || g_772f5d != 0)) {
            t = cut_RandMod(9);
            d2_SetForm(g_68bfc0, 0);
            io_AppendText(t + 0x1113);
            d3snd_PlaySoundEffect(-5, 0, (int) 0x68ccac, t);
            cut_WaitTicks(5);
        }
        d2_SetForm(g_68bfc0, 0);
        io_AppendText(0x6811b0);
        j++;
    }
    if (g_772f44 != 0) {
        if (gm_GetEntityHealthRatio((char*) &sB) > gm_GetEntityHealthRatio((char*) &sA))
            p = (char*) &sA;
        else {
            other = p = (char*) &sB;
        }
        d2_SetForm(g_68bfc0, 0);
        io_AppendText(0x6811b0);
        n = *(unsigned short*) p;
        io_AppendText(0x111d, n, n);
        cut_WaitTicks(5);
    } else {
        d2_SetForm(g_68bfc0, 0);
        io_AppendText(0x6811b0);
        io_AppendText(0x111c);
        p = other;
    }

    d2_SetForm(g_68bfc0, 0);
    io_AppendText(0x6811b0);
    if (keepA == 0) {
        if (g_772f58 != 0) {
            io_AppendText(0x111e, sB.id & 0xffff);
            fcn_004ff210(sB.id, (int) ((g_772f58 & 0xff) * 5.0));
            sB.acc = (int) ((g_772f58 & 0xff) * 5.0 + sB.acc);
        } else {
            io_AppendText(0x111f, sB.id & 0xffff, sB.id & 0xffff);
        }
    } else {
        if (g_772f58 != 0)
            io_AppendText(0x1120, sB.id & 0xffff);
        else
            io_AppendText(0x1121, sB.id & 0xffff);
    }
    cut_WaitTicks(4);

    d2_SetForm(g_68bfc0, 0);
    io_AppendText(0x6811b0);
    if (keepB == 0) {
        if (g_772f59 != 0) {
            io_AppendText(0x111e, sA.id & 0xffff);
            fcn_004ff210(sA.id, (int) ((g_772f59 & 0xff) * 5.0));
            sA.acc = (int) ((g_772f59 & 0xff) * 5.0 + sA.acc);
        } else {
            io_AppendText(0x111f, sA.id & 0xffff, sA.id & 0xffff);
        }
    } else {
        if (g_772f59 != 0)
            io_AppendText(0x1120, sA.id & 0xffff);
        else
            io_AppendText(0x1121, sA.id & 0xffff);
    }
    cut_WaitTicks(4);

    d2_SetForm(g_68bfc0, 0);
    io_AppendText(0x6811b0);
    if (p != 0) {
        if (*(unsigned char*) (p + 0x166) != 0) {
            io_AppendText(0x1123 + *(unsigned char*) (p + 9), *(unsigned short*) p);
            d3snd_PlaySoundEffect(-8, 0, (int) 0x68cc9c, *(unsigned char*) (p + 9) + 1);
            if (srv_GetEntityOfficeSlot(p, outR, outS) != 0) {
                if (*(int*) (a0 + 0xc) == *(int*) (0x7f4ca4 + (g_774970 & 0xffff) * 0x21c)) {
                    amt_SendOfficeCommand(outS[0], 0, 0, 4, 0xff);
                    q = (char*) 0x7f4ca2;
                    do {
                        if (*q == 6 || *q == 7) {
                            io_FormatTextBuffer(buf2, 0x10c7, *(unsigned short*) p,
                                (*(unsigned char*) (p + 9) != 0) + 0x10c8);
                            he_PostEntityMessage(*(int*) (q + 2), -1, buf2, 0, 0x5fe,
                                (char*) 0x6b5c60);
                        }
                        q += 0x21c;
                    } while ((int) q < 0x85a0a2);
                }
            }
        }
    } else {
        io_AppendText(0x1122, sB.id & 0xffff, sA.id & 0xffff);
        d3snd_PlaySoundEffect(-8, 0, (int) 0x68cc9c, 0);
    }

    cut_WaitTicks(5);
    if (*(int*) (0x7f4ca4 + (g_774970 & 0xffff) * 0x21c) == *(int*) (a0 + 0xc)) {
        cm_RequestCopyEntityData(sB.idx, sA.idx, 0xf, 1);
        cm_RequestCopyEntityData(sA.idx, sB.idx, 0xf, 1);
    }
    fcn_004e48b0();
    fcn_004e4aa0(sB.entity);
    sB.entity = 0;
    fcn_004e4aa0(sA.entity);
    sA.entity = 0;
    fcn_004e4610(event);
    fcn_004e45c0(event);
    cut_CleanupCutscene();
    fcn_004230e0((char*) bank);
    fcn_004230e0((char*) snd);
    fcn_004cfe20();
    msx_RestoreMusicIfAllowed(); return;
    }
    ReportClientMessage((char*) 0x68cc70);
fail:
    return;
}
