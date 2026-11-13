extern unsigned char* g_entity_ptr;
extern char* g_entity_type_table;
#include "Develop/DieGildeAddOn/game/entity.h"
int __cdecl gm_CheckStatLevel(int, int);
int __cdecl gm_RandomMod(unsigned short);
unsigned short* __cdecl fcn_00502cd0(int, int, ...);
int __cdecl fcn_00510400(char*);
int __cdecl fcn_004e99c0(int);
int __cdecl fcn_004a58d0(char*, int, char**, int, float, unsigned short*);
int __cdecl fcn_004a61d0(char*, int, char*, float, float, int, unsigned short*);
typedef struct GOLD_ACTION_PROTO { unsigned char kind; unsigned char unknown01[0x24c]; } GOLD_ACTION_PROTO;

/* ADDRESS: GOLD 0x4ab3e0 */
int __cdecl fcn_004ab3e0_gold(int action, char* actor, int busy, char* first, char* second)
{
    unsigned char* entry;
    unsigned char* best;
    char* target;
    char* candidate;
    char* selected[4];
    unsigned short ids[4];
    unsigned short target_id;
    int level;
    int score;
    int best_score;
    int total;
    int count;
    int chosen;
    int i;
    level = gm_CheckStatLevel(*(unsigned short*) actor, 0xe);
    ids[0] = ids[1] = ids[2] = ids[3] = 0xffff;
    best = 0;
    best_score = 0;
    candidate = 0;
    selected[0] = selected[1] = selected[2] = selected[3] = 0;
    if ((actor[0x1cc] & 8) || *(int*) (actor + 0x194) < 5 ||
        (action != 0x44 && action != 0) || busy || !level || actor[2] == 3) return 0;
    entry = g_entity_ptr;
    for (i = 0x100; i != 0; i--, entry += 0xa9) {
        if (*entry && *(unsigned short*) (entry + 0x27) == *(unsigned short*) actor &&
            ((GOLD_ACTION_PROTO*) g_entity_type_table)[*entry].kind == 0x1f &&
            fcn_00502cd0(*(int*) (entry + 0x5d), 2, 6, 0, 0x27c)) {
            if (!best) {
                best = entry;
                best_score = fcn_00510400((char*) entry);
            } else {
                score = fcn_00510400((char*) entry);
                if (score > best_score) { best = entry; best_score = score; }
            }
        }
    }
    if (!best || !best_score) return 0;
    candidate = (char*) 0xf00500;
    if (!fcn_004a58d0(actor, 1, &candidate, 0,
            (float) (gm_RandomMod(0x20) & 0xffff) + 25.0f, &target_id)) return 0;
    target = (char*) g_slot_table + target_id * 0x21c;
    total = fcn_004e99c0((unsigned char) target[0x166]) / 3 + 2;
    if (total + 2 > *(int*) (actor + 0x194)) return 0;
    count = fcn_004a61d0(actor, 4, candidate, 25.0f, 75.0f, best_score, ids);
    if (!count) return 0;
    chosen = 0;
    for (i = 0; i < count; i++) {
        level = fcn_004e99c0((unsigned char) ((char*) g_slot_table)[ids[i] * 0x21c + 0x166]) / 3 + 2 + total;
        if (level >= *(int*) (actor + 0x194)) {
            selected[chosen++] = (char*) g_slot_table + ids[i] * 0x21c;
            total = level;
        }
    }
    if (!chosen) return 0;
    *(int*) (first + 4) = *(int*) (target + 4);
    *(int*) (first + 0xc) = *(int*) (selected[0] + 4);
    if (chosen >= 2) *(int*) (first + 8) = *(int*) (selected[1] + 4);
    if (chosen >= 3) *(int*) (second + 0xc) = *(int*) (selected[2] + 4);
    if (chosen >= 4) *(int*) (second + 8) = *(int*) (selected[3] + 4);
    *(int*) (first + 0x10) = total;
    *first = 7;
    return 0x44;
}
