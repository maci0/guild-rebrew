#ifndef MSX_H
#define MSX_H

#include <windows.h>
#include <stddef.h>
#include "../../../client_types.h"

typedef char MSX_TRACK_SIZE_CHECK[(sizeof(Chan_14cc460) == 0x128) ? 1 : -1];
typedef char MSX_LOCK_SIZE_CHECK[(sizeof(CRITICAL_SECTION) == 24) ? 1 : -1];

typedef char MSX_OFFSET_BAMBIENT[(offsetof(Chan_14cc460, bAmbient) == 0x106) ? 1 : -1];
typedef char MSX_OFFSET_F110[(offsetof(Chan_14cc460, f110) == 0x110) ? 1 : -1];
typedef char MSX_OFFSET_F114[(offsetof(Chan_14cc460, f114) == 0x114) ? 1 : -1];
typedef char MSX_OFFSET_F118[(offsetof(Chan_14cc460, f118) == 0x118) ? 1 : -1];
typedef char MSX_OFFSET_F11C[(offsetof(Chan_14cc460, f11c) == 0x11c) ? 1 : -1];
typedef char MSX_OFFSET_F120[(offsetof(Chan_14cc460, f120) == 0x120) ? 1 : -1];
typedef char MSX_OFFSET_NEXT[(offsetof(Chan_14cc460, next) == 0x124) ? 1 : -1];

extern Chan_14cc460 g_6b71b0[10];
extern Chan_14cc460 g_14cc460;
extern char g_14cc360[];
extern int g_6b71a4;
extern int g_6b71a8;
extern CRITICAL_SECTION g_14cc5a0;

void __cdecl fcn_0042b040(int handle, void* position);
void __cdecl fcn_0042ad90(int handle, int mode);
void __cdecl fcn_0042ac40(int handle);

void __cdecl fcn_0041fc10(Chan_14cc460* track, int mode);

void __cdecl fcn_00420700(Chan_14cc460* hTrack, int mode);
void __cdecl fcn_00420120(Chan_14cc460* hTrack, int fade);
void __cdecl fcn_00420840(Chan_14cc460* hTrack);
Chan_14cc460* __cdecl fcn_00420780(const char* name, int mode);

int __cdecl fcn_0041fe10(Chan_14cc460* track, int restart);
Chan_14cc460* __cdecl fcn_0041fd70(const char* name, int mode);
Chan_14cc460* __cdecl fcn_00420650(void);

void __cdecl SetTrackPath(const char* path);

Chan_14cc460* __cdecl FindTrackByName(const char* name);
Chan_14cc460* __cdecl FindFreeTrack(void);

#endif
