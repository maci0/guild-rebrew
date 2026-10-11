/* Shared positional sound API. Header name is reconstructed, not attested. */
#ifndef CLIENT_SOUND_H
#define CLIENT_SOUND_H

#include "client_types.h"

/* Positional sound record, reconstructed from shared users.
 * Size 0x54 on the Win32 targets. The constructor copies 50 name bytes;
 * the array extent is inferred from that bound, with native pointer alignment.
 * +0x34 voice, +0x38 emitting object, +0x3c idle counter,
 * +0x40 volume, +0x44 playback control, +0x48 range,
 * +0x4c replay control, +0x50 voice retention control. */
typedef struct SOUND_SOURCE {
    char name[0x32];
    char* voice;
    char* objekt;
    int idleCounter;
    int volume;
    int playbackControl;
    float range;
    int replay;
    int keepVoice;
} SOUND_SOURCE;

extern int g_677680;
extern SOUND_SOURCE* g_6b5d08;
extern Chan_14cc460* g_772efc;
extern Chan_14cc460* g_772d1c;
extern Chan_14cc460* g_772d20;
extern Chan_14cc460* g_772d24;

/* Read-only eight-byte scale view; native storage owner is unresolved. */
extern const double g_662b40;

void __cdecl fcn_00426170(int* voice, int enabled);
SOUND_SOURCE* __cdecl fcn_00418dc0(void);
SOUND_SOURCE* __cdecl fcn_00418c80(char* voice, char* objekt, int volume, float range);
void __cdecl fcn_00418d70(SOUND_SOURCE* source);
void __cdecl fcn_00418fb0(SOUND_SOURCE* source);
void __cdecl fcn_004190d0(SOUND_SOURCE* source);

int __cdecl fcn_004193f0(char* obj, void* label, int mode, float amount);

void __cdecl PlayEntitySound(char* cmd);

#endif
