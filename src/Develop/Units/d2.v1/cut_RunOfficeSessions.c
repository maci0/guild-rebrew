extern char *g_772500;
extern unsigned short g_774970;
/* Council session controller, native frame layout by slot. */
#include <stddef.h>

int __cdecl gm_LookupEntityRecordById(int);
int __cdecl amt_FindOfficeSlotsByKind(int, int, void *);
int __cdecl sb_LoadLocalizedSampleBankIfAllowed(char *, int);
int __cdecl msx_StartMusicIfAllowed(int);
void __cdecl cut_WaitSeconds(int, ...);
int __cdecl cm_WaitNetworkSyncBanner(int);
int __cdecl amt_GetOfficeGroupHumanFlags(int);
int __cdecl amt_ResolveOfficeApplications(int, int, void *);

int __cdecl d2_LoadForm(char *, int, int);
void __cdecl d2_SetFormVisibility(int, int);
void __cdecl d2_CenterForm(int, int);
void __cdecl cut_StartSceneCutscene(char *);
int __cdecl msx_StartAmbientTrack(char *, int);
int __cdecl gm_SelectEntityHeadSet(int);
int __cdecl fcn_0064d41a(char *, char *, ...);
int __cdecl evt_StartGfxScript(char *, char *);
int __cdecl fcn_0051af00(char *, char *, char *);
int __cdecl cut_WaitForScript(int);
int __cdecl amt_IsCandidateInOffice(int, char *);
int __cdecl fcn_004727a0(int, int);
int __cdecl d2_BuildPersonStatusDesc(void *);
int __cdecl d2_DrawPersonCard(int, int, int, int, int *, int);
void __cdecl d2_UpdateVoteTallyIcons(int, int, int);
int __cdecl d3snd_QueueSoundIfAllowed(int, ...);
int __cdecl io_AppendText(char *, ...);
unsigned int __cdecl cut_RandMod(unsigned int, ...);
int __cdecl d2_ClearWindowChildren(int, int);
int __cdecl cut_RunTurnRound(unsigned int *, void *);
int __cdecl amt_IsNextOfficeStep(void *, int);
int __cdecl amt_SendOfficeCommand(unsigned char, unsigned char *, unsigned char *, int, int);
int __cdecl cm_GetCommandStatus(int);
int __cdecl cm_StepCommandQueue(void);
int __cdecl cm_RequestCopyEntityData(int, int, int, int);
int __cdecl cut_FadeToBlack(void);
int __cdecl cut_WaitForScriptExit(int);
void __cdecl cut_CleanupCutscene(void);
void __cdecl d2_DestroyForm(int);
void __cdecl d2_AddCouncilSeatMarker(int, void *);


int __cdecl amt_SyncAllOfficeSlots(void);
int __cdecl cut_UnloadSampleBank(int);
void __cdecl msx_StopAmbientTrack(int);
int __cdecl fcn_004e4eb0(void);
void __cdecl d2_DispatchTutorialInput(int, int, int, int);


/* ADDRESS: GOLDTL 0x004da690 */
void __cdecl cut_RunOfficeSessions(unsigned int *a0)
{
    int s00;
    int s04;
    int s08;
    int s0C;
    int s10;
    int s14;
    int s18;
    int s1C;
    int s20;
    int rs20;
    int s24;
    int s28;
    int s2C;
    int s30;
    int s34;
    int s38;
    int s3C;
    int s40;
    int s44;
    int v1[3];
    int s58;
    int s5C;
    int s60;
    int v2[4];
    int s78;
    int s7C;
    int acc;
    int jc;
    int s80;
    int s88;
    int s8C;
    int s90;
    int s94;
    int sC0;
    int sC4;
    int sC8;
    int sCC;
    int sD4;
    int sDC;
    int sEC;
    int sF0;
    int sF8;
    int sFC;
    int s100;
    int s104;
    int s108;
    int s10C;
    int s110;
    /* Declared before the string tables: the native body emits these six
       stores scattered into the fill stalls of the sitzung copies. */
    int order[6] = { 6, 5, 4, 3, 2, 1 };
    char sitzung[6][0x30] = {
        "Sitzung_Wohnsitz.ed3",
        "Sitzung_Kirche.ed3",
        "Sitzung_Rat.ed3",
        "Sitzung_Diebe.ed3",
        "Sitzung_Wache.ed3",
        "Sitzung_zunft.ed3",
    };
    char flug[6][0x20] = {
        "sitzungen_flug_wohnsitz.esc",
        "sitzungen_flug_kirche.esc",
        "sitzungen_flug_rat.esc",
        "sitzungen_flug_diebe.esc",
        "sitzungen_flug_wache.esc",
        "sitzungen_flug_zunft.esc",
    };
    char mid[0x4f8];
    char a0c[0x114];
    struct {
        int sel[4];
        int s84[6];
        /* native 0x9c: second-pass packet struct (12 bytes) */
        struct {
            int s9C;
            unsigned char sA0;
            int sA4;
        } blkD;
        int s98[4];
    } blkA;
    struct {
        int sD0[6];
        int sF4[8];
    } blkB;
    struct {
        int sD8;      /* native 0xf4 */
        int padHole;  /* native 0xf8, never stored: an unwritten struct
                         member keeps the hole a dead local would lose */
        int sE0;      /* native 0xfc */
        int sE4;      /* native 0x100 */
        int sE8;      /* native 0x104 */
    } blkC;
    int n, k, i, numSel, s4C, s50;

    memcpy(a0c, a0, 0x114);
    s2C = 0;
    s34 = sb_LoadLocalizedSampleBankIfAllowed((char *)0x68c214, 0);
    s38 = sb_LoadLocalizedSampleBankIfAllowed((char *)0x68c204, 0);
    msx_StartMusicIfAllowed(0);

    n = 0;
    s44 = 0;
    if (0u < (unsigned int)*(unsigned char *)((char *)a0 + 0x30)) {
        do {
            k = gm_LookupEntityRecordById(*(int *)((char *)a0 + 0x34 + n * 4));
            if (k) {
                blkB.sF4[s44] = k;
                s44 += 1;
            }
            n += 1;
        } while (n < (int)*(unsigned char *)((char *)a0 + 0x30));
    }
    k = s44;
    i = k;
    while (i < 8) {
        blkB.sF4[i] = 0;
        i += 1;
    }

    s30 = 0;
    do {
    s20 = order[s30];
    s28 = amt_FindOfficeSlotsByKind(s20, 6, (char *)&mid[0x38]);
    s0C = 0;
    k = 0;
    n = 0;
    if (s28 > 0) {
        do {
            int rr = gm_LookupEntityRecordById(*(int *)((char *)&mid[0x3c] + n * 0x18));
            if (rr) {
                if (!*(char *)(rr + 0x1b1)) {
                    blkB.sD0[k] = n;
                    blkA.s84[k] = rr;
                    k += 1;
                }
            }
            n += 1;
        } while (n < s28);
        s0C = k;
    }

    cm_WaitNetworkSyncBanner(0x6b5c60);
    if (amt_GetOfficeGroupHumanFlags(s20) == 0) {
        unsigned short v = g_774970;
        if (*(int *)((char *)a0 + 0xc) == *(int *)(0x7f4ca4 + (unsigned int)v * 0x21c)) {
            amt_ResolveOfficeApplications(s20, s28, (char *)&mid[0x38]);
        }
    } else {
    if (s28 < 6)
        for (i = s28; i < 6; i++)
            blkA.s84[i] = 0;
    if (s0C > 0) {
        for (i = 0; i < s0C; i++) {
            int id = *(int *)((char *)blkA.s84[i] + 4);
            *(int *)((char *)a0 + 0x34 + i * 4) = id;
            *(int *)(0x9b0ad4 + i * 0x35c) = id;
            *(int *)(0x9b0b60 + i * 0x35c) = 0;
            *(int *)(0x9b0ac8 + i * 0x35c) = 0;
            *(int *)(0x9b0acc + i * 0x35c) = 1;
        }
    }

    s4C = s0C;
    if (s44 > 0) {
        s50 = 0x9b0e24 + s0C * 0x35c;
        for (n = 0; n < s44; n++) {
            int *pp = (int *)0x9b0e30;
            int j = 0;
            s5C = *(int *)(blkB.sF4[n] + 4);
            while (j < s0C && *pp != s5C) {
                j += 1;
                pp += 0x35c / 4;
            }
            if (j < s0C)
                continue;
            {
                int *pd = (int *)s50;
                *(int *)((char *)a0 + 0x34 + s4C * 4) = s5C;
                pd[3] = s5C;
                pd[0] = 0;
                pd[1] = 1;
                *(int *)((char *)pd + 0x98) = 1;
                s50 = (int)(pd + 0x35c / 4);
                s4C += 1;
            }
        }
    }
    *(unsigned char *)((char *)a0 + 0x30) = (unsigned char)s4C;
    if (s4C < 0x10) {
        int *pa = (int *)((char *)a0 + 0x34) + s4C;
        int *pt = (int *)(0x9b0e30 + s4C * 0x35c);
        int *ptEnd = (int *)0x9b43f0;
        do {
            *pa = -1;
            *pt = -1;
            pt += 0x35c / 4;
            pa += 1;
        } while (pt < ptEnd);
    }
    /* native 0x4dac46: scene handle, per-entity text packets */
    cm_WaitNetworkSyncBanner(0x6b5c60);
    s14 = d2_LoadForm((char *)0x68c1ec, 0, 0);
    d2_SetFormVisibility(s14, 0);
    d2_CenterForm(s14, 3);
    s1C = 0;
    if (s28 > 0) {
        for (n = 0; n < s28; n++) {
            if (*((unsigned char *)&mid[0x48] + n * 0x18) == 2)
                s1C += 1;
        }
    }
    s3C = 0;
    if (s1C != 0) {
        cut_StartSceneCutscene(sitzung[s30]);
        if (s2C == 0)
            s2C = msx_StartAmbientTrack((char *)0x68c1d0, 0x40);
        for (i = 0; i < s44; i++) {
            s04 = gm_SelectEntityHeadSet((int)*(unsigned short *)blkA.s84[i]);
            if (s04 != 0)
                fcn_0064d41a((char *)&mid[0x2a8], (char *)0x68c1c8,
                             blkB.sD0[i], (char *)(s04 + 4));
            else
                fcn_0064d41a((char *)&mid[0x2a8], (char *)0x68c1b0,
                             blkB.sD0[i]);
            evt_StartGfxScript((char *)0x68c184, (char *)&mid[0x2a8]);
        }
        for (i = 0; i < s44; i++) {
            fcn_0064d41a((char *)&mid[0x2a8], "%i", blkB.sD0[i]);
            evt_StartGfxScript((char *)0x68c158, (char *)&mid[0x2a8]);
        }
        fcn_0051af00((char *)&mid[0x2a8], (char *)0x68c140, flug[s30]);
        cut_WaitForScript(evt_StartGfxScript((char *)0x6b5c60, (char *)&mid[0x2a8]));
        s3C = 1;
        cm_WaitNetworkSyncBanner(0x6b5c60);
    }
    s40 = 0;

    /* native 0x4dade7..0x4db5f5: per-row scene pass */
    if (s28 > 0) {
        s00 = (int)(char *)&mid[0x3c];
        do {
            if (s1C == 0)
                break;
            v1[0] = 0;
            v1[1] = 0;
            v1[2] = 0;
            if (amt_IsCandidateInOffice(s20, (char *)(s00 - 4)) != 0) {
                i = 0;
                k = 0;
                while (i < s44) {
                    if (((char *)blkA.s84[i])[0x166] != 0)
                        k += 1;
                    i += 1;
                }
                s5C = d2_LoadForm((char *)0x68c124, 0, 0);
                d2_CenterForm(s5C, 3);
                s60 = d2_LoadForm((char *)0x68c104, 0, 0);
                d2_CenterForm(s60, 3);
                s10 = gm_LookupEntityRecordById(*(int *)s00);
                s18 = gm_LookupEntityRecordById(*(int *)(s00 + 0x10));
                fcn_004727a0(s60, 1);
                *(int *)((char *)&mid + 0x38) = s10;
                *(int *)((char *)&mid + 0x4c) = 0;
                *(int *)((char *)&mid + 0x68) = 0;
                d2_BuildPersonStatusDesc((char *)&mid + 0x38);
                d2_DrawPersonCard(0x28, 0, *(int *)0x772514, 0x54,
                             (int *)((char *)&mid + 0x38), 1);
                fcn_004727a0(s60, 2);
                d2_UpdateVoteTallyIcons(*(int *)0x772514, 1, 0);
                d3snd_QueueSoundIfAllowed(-8, s34, 0x68c0f0, s20 - 1, 0x32);
                d2_SetFormVisibility((int)a0, 1);
                fcn_004727a0((int)a0, 0);
                io_AppendText((char *)0x6811b0);
                io_AppendText((char *)0x12c4);
                io_AppendText((char *)0x12c5, (char *)s20 + 0x12a9, (char *)s20 + 0x12bb,
                              *(unsigned short *)s18, *(unsigned short *)s10);
                cut_WaitSeconds(0x9c4);
                fcn_004727a0(s5C, 0);
                d2_ClearWindowChildren(*(int *)0x772514, 1);
                if (k > 0) {
                    int *lane;
                    s08 = (0x320 - *(short *)(g_772500 + 0x1ebd8) * k) / (k + 1);
                    i = 0;
                    n = 0;
                    acc = s08;
                    lane = (int *)((char *)&mid + 0x3a8);
                    while (n < s0C) {
                        if (((char *)blkA.s84[n])[0x166] != 0) {
                            lane[0] = blkA.s84[n];
                            lane[5] = 0;
                            lane[12] = 0;
                            d2_BuildPersonStatusDesc((char *)lane);
                            d2_DrawPersonCard(*(short *)(g_772500 + 0x1ebd8) * i + acc, 0,
                                         *(int *)0x772514, 0x54, lane, 0);
                            acc += s08;
                            i += 1;
                        }
                        n += 1;
                        lane = (int *)((char *)lane + 0x38);
                    }
                }
                cut_WaitSeconds(0x9c4);
                sDC = *(unsigned char *)(s00 - 4);
                blkC.sD8 = 1;
                blkC.sE0 = *(unsigned char *)(s00 + 4);
                blkC.sE4 = *(int *)s00;
                blkC.sE8 = *(int *)(s00 + 0x10);
                d2_SetFormVisibility(s38, 0);
                cut_RunTurnRound(a0, (void *)&blkC);
                cut_WaitSeconds(0x3e8);
                d2_SetFormVisibility(s38, 1);
                if (s0C > 0) {
                    i = 0;
                    do {
                        s80 = 0x9b0eb4 + i * 0x35c;
                        if (*(int *)s80 < 3) {
                            s58 = gm_LookupEntityRecordById(*(int *)(s80 - 0x84));
                            v1[*(int *)s80] += 1;
                            fcn_004727a0(s14, 0);
                            *(int *)(*(int *)0x1015ea0 + *(int *)((char *)&mid + 0x3ac + i * 0x38) * 0x2f4 + 0x3c) = 1;
                            io_AppendText((char *)0x6811b0);
                            io_AppendText((char *)0x12c7, *(unsigned short *)s58);
                            cut_WaitSeconds(0x3e8);
                            fcn_004727a0(s14, 0);
                            switch (*(int *)s80) {
                            case 0:
                                d3snd_QueueSoundIfAllowed(*(unsigned short *)s58, s34, 0x68c0e0,
                                             (int)cut_RandMod(4), 0x64);
                                io_AppendText((char *)0x12c8);
                                if (*(int *)(s80 + 4) == 1)
                                    io_AppendText((char *)((int)cut_RandMod(2, *(unsigned short *)s18) + 0x12cb));
                                else if (*(int *)(s80 + 4) == 2)
                                    io_AppendText((char *)((int)cut_RandMod(2, *(unsigned short *)s18) + 0x12cf));
                                fcn_004727a0(s60, 2);
                                d2_UpdateVoteTallyIcons(*(int *)0x772514, 0, 0);
                                break;
                            case 1:
                                d3snd_QueueSoundIfAllowed(*(unsigned short *)s58, s34, 0x68c0d0,
                                             (int)cut_RandMod(4), 0x64);
                                io_AppendText((char *)0x12ca);
                                if (*(int *)(s80 + 4) == 1)
                                    io_AppendText((char *)((int)cut_RandMod(2, *(unsigned short *)s18,
                                                                             *(unsigned short *)s10) + 0x12cd));
                                else if (*(int *)(s80 + 4) == 2)
                                    io_AppendText((char *)((int)cut_RandMod(2, *(unsigned short *)s10) + 0x12d1));
                                fcn_004727a0(s60, 2);
                                d2_UpdateVoteTallyIcons(*(int *)0x772514, 0, 1);
                                break;
                            default:
                                d3snd_QueueSoundIfAllowed(*(unsigned short *)s58, s34, 0x68c0b8,
                                             (int)cut_RandMod(4), 0x64);
                                io_AppendText((char *)0x12c9);
                                fcn_004727a0(s60, 2);
                                d2_UpdateVoteTallyIcons(*(int *)0x772514, 0, 2);
                                break;
                            }
                            cut_WaitSeconds(0xfa0);
                            *(int *)(*(int *)0x1015ea0 + *(int *)((char *)&mid + 0x3ac + i * 0x38) * 0x2f4 + 0x3c) = 0;
                            cut_WaitSeconds(0x3e8);
                        }
                        i += 1;
                    } while (i < s0C);
                }
                /* native 0x4db332..0x4db5c5: vote result text and packet pass */
                if (v1[0] > v1[1]) {
                    d3snd_QueueSoundIfAllowed(-8, s60, 0x68c098, (int)cut_RandMod(3), 0x64);
                    fcn_004727a0(s14, 0);
                    io_AppendText((char *)0x6811b0);
                    io_AppendText((char *)0x12d6, (char *)v1[0], (char *)v1[1],
                                  *(unsigned short *)s10);
                    cut_WaitSeconds(0xfa0);
                    if (a0[3] == *(int *)(0x7f4ca4 +
                                          (unsigned int)g_774970 * 0x21c)) {
                        int s70;
                        jc = 0x9b0e30;
                        n = s0C;
                        do {
                            if (*(int *)jc != *(int *)(s10 + 4))
                                cm_RequestCopyEntityData(*(int *)jc, *(int *)(s10 + 4),
                                             *(int *)(jc + 0x84) == 0 ? -0x28 :
                                             (*(int *)(jc + 0x84) == 1 ? 0xa : -0x14), 1);
                            jc += 0x35c;
                        } while (--n);
                        s70 = amt_SendOfficeCommand(*(unsigned char *)(s00 - 4), 0, 0, 3, 0xff);
                        if (cm_GetCommandStatus(s70) == 0) {
                            do {
                                cm_StepCommandQueue();
                            } while (cm_GetCommandStatus(s70) == 0);
                        }
                    }
                } else {
                    int s70;
                    s70 = gm_LookupEntityRecordById(*(int *)s00);
                    d3snd_QueueSoundIfAllowed(-8, s60, 0x68c074, (int)cut_RandMod(3), 0x64);
                    fcn_004727a0(s14, 0);
                    io_AppendText((char *)0x6811b0);
                    io_AppendText((char *)0x12d7, (char *)v1[0], (char *)v1[1],
                                  *(unsigned short *)s10, *(unsigned short *)s10);
                    cut_WaitSeconds(0xfa0);
                    if (a0[3] == *(int *)(0x7f4ca4 +
                                          (unsigned int)g_774970 * 0x21c)) {
                        if (s0C > 0) {
                            n = s0C;
                            jc = 0x9b0e30;
                            do {
                                if (*(int *)jc != *(int *)(s10 + 4))
                                    cm_RequestCopyEntityData(*(int *)jc, *(int *)(s10 + 4),
                                                 *(int *)(jc + 0x84) == 0 ? -0x28 :
                                                 (*(int *)(jc + 0x84) == 1 ? 0xa : 5), 1);
                                jc += 0x35c;
                                n -= 1;
                            } while (n != 0);
                        }
                        if (s70)
                            s24 = amt_SendOfficeCommand(*(unsigned char *)(s00 - 4), 0,
                                               (unsigned char *)s70, 1, 0xff);
                        else
                            s24 = amt_SendOfficeCommand(*(unsigned char *)(s00 - 4), 0, 0, 4, 0xff);
                        if (cm_GetCommandStatus(s24) == 0) {
                            do {
                                cm_StepCommandQueue();
                            } while (cm_GetCommandStatus(s24) == 0);
                        }
                    }
                }
                fcn_004727a0(s14, 0);
                d2_SetFormVisibility(s14, 0);
                io_AppendText((char *)0x6811b0);
                d2_DestroyForm(s60);
                d2_DestroyForm(s5C);
                cut_WaitSeconds(0x3e8);
                cm_WaitNetworkSyncBanner(0x6b5c60);
            }
            s40 += 1;
            s00 += 0x18;
        } while (s40 < s28);
    }
    /* native 0x4db5f5..0x4dc199: second packet pass */
    s1C = 0;
    if (s28 > 0) {
        i = 0;
        while (i < s28) {
            if (*(unsigned char *)((char *)&mid[0x48] + i * 0x18) == 3 &&
                *(int *)((char *)&mid[0x44] + i * 0x18) != 0)
                s1C += 1;
            i += 1;
        }
    }
    if (s1C != 0 && s3C == 0) {
            cut_StartSceneCutscene(sitzung[s30]);
            if (s2C == 0)
                s2C = msx_StartAmbientTrack((char *)0x68c1d0, 0x40);
            for (i = 0; i < s44; i++) {
                s04 = gm_SelectEntityHeadSet((int)*(unsigned short *)blkA.s84[i]);
                if (s04 != 0)
                    fcn_0064d41a((char *)&mid[0x1a8], (char *)0x68c1c8,
                                 blkB.sD0[i], (char *)(s04 + 4));
                else
                    fcn_0064d41a((char *)&mid[0x1a8], (char *)0x68c1b0, blkB.sD0[i]);
                evt_StartGfxScript((char *)0x68c184, (char *)&mid[0x1a8]);
            }
            for (i = 0; i < s44; i++) {
                fcn_0064d41a((char *)&mid[0x1a8], "%i", blkB.sD0[i]);
                evt_StartGfxScript((char *)0x68c158, (char *)&mid[0x1a8]);
            }
            fcn_0051af00((char *)&mid[0x1a8], (char *)0x68c140, flug[s30]);
            cut_WaitForScript(evt_StartGfxScript((char *)0x6b5c60, (char *)&mid[0x1a8]));
            cm_WaitNetworkSyncBanner(0x6b5c60);
            s3C = 1;
    }
    if (s28 > 0) {
        s40 = 0;
        s00 = (int)(char *)&mid[0x40];
        while (s40 < s28) {
            v2[0] = 0;
            v2[1] = 0;
            v2[2] = 0;
            v2[3] = 0;
            if (s1C != 0 && *(unsigned char *)(s00 + 8) == 3 &&
                *(int *)(s00 + 4) != 0) {
                s1C -= 1;
                blkA.blkD.s9C = 2;
                blkA.blkD.sA0 = *(unsigned char *)(s00 - 8);
                blkA.blkD.sA4 = *(unsigned char *)s00;
                i = 0;
                rs20 = 0;
                while (i < s44) {
                    if (amt_IsNextOfficeStep((void *)blkA.s84[i], blkA.blkD.sA4) != 0 &&
                        ((char *)blkA.s84[i])[0x1b1] == 0)
                        rs20 += 1;
                    i += 1;
                }
                s14 = d2_LoadForm((char *)0x68c124, 0, 0);
                d2_CenterForm(s14, 3);
                s50 = d2_LoadForm((char *)0x68c058, 0, 0);
                d2_CenterForm(s50, 2);
                fcn_004727a0(s50, 0);
                {
                int *lane;
                int s80;
                lane = (int *)((char *)&mid + 0xc8);
                i = 0;
                s80 = 0x7f4ca0;
                do {
                    if (i >= *(int *)(s14 + 4) || i >= 4)
                        break;
                    if (*(unsigned char *)(s80 + 0x168) == *(unsigned char *)s00) {
                        blkA.sel[i] = s80;
                        fcn_004727a0(s14, i + 1);
                        *lane = s80;
                        lane[5] = 0;
                        lane[11] = 0;
                        lane[12] = 0;
                        d2_BuildPersonStatusDesc((char *)lane);
                        d2_DrawPersonCard((0xa0 - *(short *)(g_772500 + 0x1ebd8)) / 2,
                                     0, *(int *)0x772514, 0x54,
                                     lane, 1);
                        blkA.s98[i] = *(int *)(s80 + 4);
                        i += 1;
                        lane = (int *)((char *)lane + 0x38);
                    }
                    s80 += 0x21c;
                } while (s80 < 0x85a0a0);
                }
                numSel = i;
                if (numSel != 0) {
                    if (numSel < 4) {
                        n = numSel;
                        while (n < 4) {
                            blkA.s98[n] = -1;
                            blkA.sel[n] = 0;
                            n += 1;
                        }
                    }
                    d3snd_QueueSoundIfAllowed(-8, s38, 0x68c050, s20 - 1, 0x64);
                    d3snd_QueueSoundIfAllowed(-8, s38, 0x68c044, numSel - 1, 0x1f4);
                    d2_SetFormVisibility(s14, 1);
                    fcn_004727a0(s14, 0);
                    io_AppendText((char *)0x6811b0);
                    io_AppendText((char *)0x12d8);
                    io_AppendText((char *)0x12d9, s20 + 0x12a9, s20 + 0x12bb,
                                  *(unsigned char *)s00 + 0x253);
                    i = 0;
                    while (i < numSel) {
                        io_AppendText((char *)0x12db,
                                      *(unsigned short *)(blkA.sel[i]),
                                      *(unsigned short *)(blkA.sel[i]));
                        i += 1;
                    }
                    cut_WaitSeconds(0x9c4);
                    fcn_004727a0(s38, 0);
                    d2_ClearWindowChildren(*(int *)0x772514, 1);
                    if (rs20 > 0) {
                        s08 = (0x320 - *(short *)(g_772500 + 0x1ebd8) * rs20) / (rs20 + 1);
                        if (s0C > 0) {
                            i = 0;
                            acc = s08;
                            do {
                                if (amt_IsNextOfficeStep((void *)blkA.s84[i], blkA.blkD.sA4) != 0) {
                                    *(int *)((char *)&mid + 0x3a8 + i * 0x38) = blkA.s84[i];
                                    *(int *)((char *)&mid + 0x3bc + i * 0x38) = 0;
                                    *(int *)((char *)&mid + 0x3d8 + i * 0x38) = 0;
                                    d2_BuildPersonStatusDesc((char *)&mid + 0x3a8 + i * 0x38);
                                    d2_DrawPersonCard(*(short *)(g_772500 + 0x1ebd8) * i + acc,
                                                 0, *(int *)0x772514, 0x54,
                                                 (int *)((char *)&mid + 0x3a8 + i * 0x38), 0);
                                    acc += s08;
                                }
                                i += 1;
                            } while (i < s0C);
                        }
                    }
                    cut_WaitSeconds(0x9c4);
                }
                if (numSel == 1) {
                    d3snd_QueueSoundIfAllowed(-8, s38, 0x68c038, 0, 0x64);
                    *(int *)(*(int *)0x1015ea0 + *(int *)((char *)&mid + 0xcc) * 0x2f4 + 0x3c) = numSel;
                    fcn_004727a0(s14, 0);
                    io_AppendText((char *)0x6811b0);
                    io_AppendText((char *)0x12e0, *(unsigned short *)blkA.sel[0],
                                  *(unsigned char *)s00 + 0x253);
                    cut_WaitSeconds(0xfa0);
                    if (a0[3] == *(int *)(0x7f4ca4 + (unsigned int)g_774970 * 0x21c)) {
                        s5C = amt_SendOfficeCommand(*(unsigned char *)(s00 - 8), 0, (unsigned char *)blkA.sel[0], numSel, 0xff);
                        if (cm_GetCommandStatus(s5C) == 0) {
                            do {
                                cm_StepCommandQueue();
                            } while (cm_GetCommandStatus(s5C) == 0);
                        }
                    }
                } else if (rs20 == 0) {
                    int s68, s70;
                    /* native 0x4dbbed: count == 0, single picked row */
                    s68 = (int)cut_RandMod((unsigned int)numSel);
                    d3snd_QueueSoundIfAllowed(-8, s38, 0x68c038, 1, 0x64);
                    fcn_004727a0(s14, 0);
                    io_AppendText((char *)0x6811b0);
                    io_AppendText((char *)0x12e1);
                    cut_WaitSeconds(0x3e8);
                    s58 = blkA.sel[s68];
                    s70 = *(int *)((char *)&mid + 0xcc + s68 * 0x38);
                    *(int *)(*(int *)0x1015ea0 + s70 * 0x2f4 + 0x3c) = 1;
                    io_AppendText((char *)0x12e2, *(unsigned short *)s58);
                    cut_WaitSeconds(0xfa0);
                    if (a0[3] == *(int *)(0x7f4ca4 +
                                          (unsigned int)g_774970 * 0x21c)) {
                        s70 = amt_SendOfficeCommand(*(unsigned char *)(s00 - 8), 0, (unsigned char *)s58, 1, 0xff);
                        if (cm_GetCommandStatus(s70) == 0) {
                            do {
                                cm_StepCommandQueue();
                            } while (cm_GetCommandStatus(s70) == 0);
                        }
                    }
                } else {
                    /* native 0x4dbce1: count > 1, scan the 0x9b0eb4 packets */
                    d2_SetFormVisibility(s14, 0);
                    cut_RunTurnRound(a0, (void *)&blkA.blkD);
                    cut_WaitSeconds(0x3e8);
                    d2_SetFormVisibility(s14, 1);
                    if (s0C > 0) {
                        int s4C, curId;
                        s4C = 0;
                        s5C = 0x9b0eb4;
                        s60 = (int)((char *)&mid + 0x3ac);
                        while (s4C < s0C) {
                            curId = *(int *)s5C;
                            if (curId != -1 && numSel > 0) {
                                int *pq;
                                jc = 0;
                                do {
                                    if (blkA.s98[jc] == curId) {
                                        *(int *)(*(int *)0x1015ea0 + *(int *)s60 * 0x2f4 + 0x3c) = 1;
                                        fcn_004727a0(s14, 0);
                                        io_AppendText((char *)0x6811b0);
                                        io_AppendText((char *)0x12de,
                                                      *(unsigned short *)blkA.s84[s4C]);
                                        v2[jc] += 1;
                                        cut_WaitSeconds(0x3e8);
                                        pq = (int *)((char *)&mid + 0xcc + jc * 0x38);
                                        *(int *)(*(int *)0x1015ea0 + *pq * 0x2f4 + 0x3c) = 1;
                                        fcn_004727a0(s50, jc + 1);
                                        d2_AddCouncilSeatMarker(jc + 1,
                                                     (void *)((char *)&mid + 0xc8 + jc * 0x38));
                                        fcn_004727a0(s14, 0);
                                        io_AppendText((char *)0x12df,
                                                      *(unsigned short *)blkA.sel[jc]);
                                        cut_WaitSeconds(0xfa0);
                                        *(int *)(*(int *)0x1015ea0 + *(int *)s60 * 0x2f4 + 0x3c) = 0;
                                        *(int *)(*(int *)0x1015ea0 + *pq * 0x2f4 + 0x3c) = 0;
                                        break;
                                    }
                                    jc += 1;
                                } while (jc < numSel);
                            }
                            s4C += 1;
                            s5C += 0x35c;
                            s60 += 0x38;
                        }
                    }
                    {
                    int s68, s6C, s70, s78;
                    /* native 0x4dbeab: pick the least-used variant */
                    s68 = -1;
                    s6C = -1;
                    s70 = 0;
                    i = 0;
                    while (i < numSel) {
                        s78 = v2[i];
                        if (s78 > s68) {
                            s70 = 0;
                            s68 = s78;
                            s6C = i;
                        } else if (s78 == s68) {
                            s70 = 1;
                        }
                        i += 1;
                    }
                    if (s70 == 0) {
                        if (s6C != -1) {
                            *(int *)(*(int *)0x1015ea0 +
                                     *(int *)((char *)&mid + 0xcc + s6C * 0x38) * 0x2f4 + 0x3c) = 1;
                            d3snd_QueueSoundIfAllowed(-8, s38, 0x68c038, 3, 0x64);
                            fcn_004727a0(s14, 0);
                            io_AppendText((char *)0x6811b0);
                            io_AppendText((char *)0x12e5,
                                          *(unsigned short *)blkA.sel[s6C],
                                          *(unsigned char *)s00 + 0x253);
                            cut_WaitSeconds(0xfa0);
                            if (a0[3] == *(int *)(0x7f4ca4 +
                                                  (unsigned int)g_774970 * 0x21c)) {
                                s78 = amt_SendOfficeCommand(*(unsigned char *)(s00 - 8), 0,
                                                   (unsigned char *)blkA.sel[s6C], 1, 0xff);
                                if (cm_GetCommandStatus(s78) == 0) {
                                    do {
                                        cm_StepCommandQueue();
                                    } while (cm_GetCommandStatus(s78) == 0);
                                }
                            }
                        }
                    } else if (s6C != -1) {
                        /* native 0x4dbfd5: tie, walk forward modulo numSel */
                        s78 = (int)cut_RandMod((unsigned int)numSel);
                        i = numSel;
                        do {
                            if (v2[s78] == s68) {
                                s6C = s78;
                                break;
                            }
                            i -= 1;
                            s78 += 1;
                            s78 %= numSel;
                        } while (i != 0);
                        {
                            d3snd_QueueSoundIfAllowed(-8, s38, 0x68c038, 2, 0x64);
                            fcn_004727a0(s14, 0);
                            io_AppendText((char *)0x6811b0);
                            io_AppendText((char *)0x12e3);
                            cut_WaitSeconds(0x3e8);
                            *(int *)(*(int *)0x1015ea0 +
                                     *(int *)((char *)&mid + 0xcc + s6C * 0x38) * 0x2f4 + 0x3c) = 1;
                            io_AppendText((char *)0x12e4,
                                          *(unsigned short *)blkA.sel[s6C]);
                            cut_WaitSeconds(0xfa0);
                            if (a0[3] == *(int *)(0x7f4ca4 +
                                                  (unsigned int)g_774970 * 0x21c)) {
                                s78 = amt_SendOfficeCommand(*(unsigned char *)(s00 - 8), 0,
                                                   (unsigned char *)blkA.sel[s6C], 1, 0xff);
                                if (cm_GetCommandStatus(s78) == 0) {
                                    do {
                                        cm_StepCommandQueue();
                                    } while (cm_GetCommandStatus(s78) == 0);
                                }
                            }
                        }
                    }
                    }
                    fcn_004727a0(s14, 0);
                    io_AppendText((char *)0x6811b0);
                    d2_SetFormVisibility(s14, 0);
                    d2_DestroyForm(s14);
                    d2_DestroyForm(s50);
                    cut_WaitSeconds(0x3e8);
                    cm_WaitNetworkSyncBanner(0x6b5c60);
                }
            }
            s40 += 1;
            s00 += 0x18;
        }
    }
    if (s3C != 0) {
        cut_FadeToBlack();
        cut_WaitSeconds(0x3e8);
        cut_WaitForScriptExit(evt_StartGfxScript((char *)0x6b5c60, (char *)0x68c010));
        cut_CleanupCutscene();
    }
    d2_DestroyForm(s14);
    }
    s30 += 1;
    } while (s30 < 6);
    /* native 0x4dc199..0x4dc221: epilogue */
    if (a0[3] == *(int *)(0x7f4ca4 + (unsigned int)g_774970 * 0x21c))
        amt_SyncAllOfficeSlots();
    cut_UnloadSampleBank(s34);
    cut_UnloadSampleBank(s38);
    if (s2C != 0)
        msx_StopAmbientTrack(s2C);
    fcn_004e4eb0();
    memcpy(a0, a0c, 0x114);
    d2_DispatchTutorialInput(0x30, 0, 0, 0);











}
