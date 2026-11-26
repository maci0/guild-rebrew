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

extern Chan_14cc460 msx_Tracks[10];
extern Chan_14cc460 msx_NullTrack;
extern char msx_TrackPath[];
extern int msx_TrackDriver;
extern int msx_AmbientDriver;
extern CRITICAL_SECTION msx_TrackLock;

void __cdecl fcn_0042b040(int handle, void* position);
void __cdecl fcn_0042ad90(int handle, int mode);
void __cdecl msx_CloseStream(int handle);

void __cdecl msx_SetTrackVolume(Chan_14cc460* track, int mode);

void __cdecl msx_StartTrackFade(Chan_14cc460* hTrack, int mode);
void __cdecl msx_StopTrack(Chan_14cc460* hTrack, int fade);
void __cdecl msx_StopAmbientTrack(Chan_14cc460* hTrack);
Chan_14cc460* __cdecl msx_StartAmbientTrack(const char* name, int mode);

int __cdecl msx_StartTrackInternal(Chan_14cc460* track, int restart);
Chan_14cc460* __cdecl msx_StartTrack(const char* name, int mode);
Chan_14cc460* __cdecl msx_FindActiveTrack(void);

void __cdecl SetTrackPath(const char* path);

Chan_14cc460* __cdecl FindTrackByName(const char* name);
Chan_14cc460* __cdecl FindFreeTrack(void);

#endif
