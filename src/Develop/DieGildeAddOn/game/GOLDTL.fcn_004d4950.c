#include <string.h>
#include "game_data.h"
#include "client_packet_builder.h"
#include "Develop/DieGildeAddOn/game/game_data.h"

char* __cdecl gm_GetEquippedCombatGear(char*);
int __cdecl d3sm_GetObjectSuperMap(char*);
float __cdecl gm_CalcEntityFlatDistance(char*, unsigned int);
unsigned short* __cdecl gm_FindEntityActiveItem(char*);
void __cdecl cm_BeginPacketFieldDelta(char*, int);
void __cdecl cm_AppendPacketFieldValue(int, int, int, int*);
void __cdecl cm_RequestChangeAttribute(void);
unsigned int __cdecl cut_RandMod(unsigned int);
void __cdecl d3_ScheduleActionTimer(char*, int, int);
int __cdecl d3snd_QueueSound(int, int, char*, int, int);
void* __cdecl sb_PlayVoice(char*, char*, int, int, int, int, int);
int __cdecl fcn_004d4790(char*);
int* __cdecl d3_SpawnBlutEffect(int, int, int, int, int, int);
#include "Develop/DieGildeAddOn/game/ch_queue.h"
char* __cdecl ch_NewAnimationAction(int, char*, int, float);
int __cdecl io_FormatTextBuffer(void*, ...);
void __cdecl fcn_00533a40(char*);

/* Message-dialog handler: look up the topic text and the current page, pick
   the reply text by message kind, then lay out the portrait, the speaker and
   the page counter. */
/* ADDRESS: GOLDTL 0x004d4950 */
void __cdecl gm_ResolveDuelHit(int ctx)
{
    char* v3;
    unsigned short* v4;
    int* v7;
    char* v9;
    int v5;
    int v22;
    char animations[2][0x20] = { "kampf/arm_greifen", "kampf/bauch_greifen" };
    char message[0x100];
    int v8;
    int r;

    v3 = *(char**) (ctx + 0x180);
    v4 = *(unsigned short**) (ctx + 0x17c);
    v22 = *(int*) (ctx + 0x184);
    v5 = 1;
    v9 = gm_GetEquippedCombatGear((char*) v4);
    v7 = (int*) gm_GetEquippedCombatGear(v3);
    d3sm_GetObjectSuperMap((char*) *(int*) ((char*) v4 + 0x184));
    if (!v7 ||
        *(float*) ((char*) v7 + 0xc) <
            gm_CalcEntityFlatDistance(v3,
                         *(unsigned int*) (*(int*) ((char*) v4 + 0x184) + 0x34))) {
        v22 = 0;
        v5 = 0;
    }
    if (*(int*)((char*)g_772f24 + 4) == g_68b79c &&
        (v7[0x16] == 1 || v7[0x16] == 2)) {
        v8 = (int) gm_FindEntityActiveItem(v3);
        if (v8) {
            int v11;
            v11 = -1;
            cm_BeginPacketFieldDelta((char*) v8, *(int*) (v8 + 2));
            cm_AppendPacketFieldValue(4, 1, (v8 - (int)g_aed32c) + 0x20, &v11);
            cm_RequestChangeAttribute();
        }
    }
    if (v22) {
        r = cut_RandMod(10);
        if ((int) g_772e9c == *(int*) ((char*) v4 + 0x16c)) {
            d3_ScheduleActionTimer((char*) v4, v22, 1);
        } else {
            d3_ScheduleActionTimer((char*) v4, v22, 2);
        }
        if (r > 8) {
            if (*(int*) (ctx + 0x188) != *(int*) ((int)g_772e9c + 4)) {
                d3snd_QueueSound(*v4, *(int*) 0x772ef4, (char*) 0x68be54, -1, 500);
            } else {
                d3snd_QueueSound(*v4, *(int*) 0x772ef8, (char*) 0x68be54, -1, 500);
            }
        } else if (r > 5) {
            sb_PlayVoice((char*) 0, (char*) 0x68bde4, 1, 0x3f, 0x7f, 0, 0);
        }
    }
    if (!*(char*) ((char*) v4 + 8)) {
        return;
    }
    if (!*(char*) (v3 + 8)) {
        return;
    }
    if (!v5) {
        return;
    }
    if (*v7 == 0x156 || *v7 == 0x158) {
        if (v22) {
            sb_PlayVoice(0, (char*) 0x68be40, 1, 0x3f, 0x7f, 0, 0);
        } else {
            sb_PlayVoice(*(char**) 0x772ed0, (char*) 0x68be34, 1, 0x3f, 0x7f, 0, 0);
        }
    } else if (*v7 == 0x154 || *v7 == 0x16e || *v7 == 0x172) {
        if (v22) {
            sb_PlayVoice(0, (char*) 0x68be40, 1, 0x3f, 0x7f, 0, 0);
        } else {
            sb_PlayVoice(*(char**) 0x772ec8, (char*) 0x68be34, 1, 0x3f, 0x7f, 0, 0);
        }
    } else if (*v7 == 0x15e) {
        sb_PlayVoice(*(char**) 0x772ecc, (char*) 0x68be48, 1, 0x3f, 0x7f, 0, 0);
    } else {
        if (*v7 == 0x160) {
            if (!v22) goto draw;
        } else if (*v7) {
            goto draw;
        }
        sb_PlayVoice(0, (char*) 0x68be40, 1, 0x3f, 0x7f, 0, 0);
    }
draw:
    if (fcn_004d4790((char*) v4)) {
        return;
    }
    if (v22) {
        d3_SpawnBlutEffect(*(unsigned int*) (*(int*) ((char*) v4 + 0x184) + 0x34),
                     0x40, 0x3e800000, 0x3dcccccd, 0x3e0f5c29, 0x425c0000);
        v8 = *(int*) (*(int*)((char*)v4 + 0x184) + 0x128);
        if (!v8 || *(char*) (v8 + 9) == ';') {
            ch_CancelActionQueue((char*) *(int*) ((char*) v4 + 0x184));
            ch_NewAnimationAction(*(unsigned int*) ((char*) v4 + 0x184),
                         animations[cut_RandMod(2)], 1, 1.4f);
        }
        if (*v7 == 0x16e) {
            *(char*) ((char*) v4 + 8) = 4;
            io_FormatTextBuffer(message, 0x1188, *(unsigned int*) (v9 + 0x54), *v4);
            fcn_00533a40(message);
            return;
        }
    } else {
        v8 = *(int*) (*(int*)((char*)v4 + 0x184) + 0x128);
        if (!v8 || *(char*) (v8 + 9) == ';') {
            ch_CancelActionQueue((char*) *(int*) ((char*) v4 + 0x184));
            if (*v7 != 0x15e && *v7 != 0x160) {
                ch_NewAnimationAction(*(unsigned int*) ((char*) v4 + 0x184),
                             (char*) 0x68be20, 1, 1.4f);
                return;
            }
            ch_NewAnimationAction(*(unsigned int*) ((char*) v4 + 0x184),
                         (char*) 0x68be08, 1, 1.4f);
            return;
        }
    }
}
