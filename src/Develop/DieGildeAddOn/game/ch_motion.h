#ifndef CH_MOTION_H
#define CH_MOTION_H

/* Inferred names; declarations describe accessed fields, not storage owners. */
extern int ch_MorphFrameValue;
void __cdecl ch_PreloadModelMotions(char* model, int n, ...);
void __cdecl ch_FinishAni(char* obj);

/* Provisional game views; extern declarations allocate no storage. */
extern const float d3_ZeroVec4[4];
extern unsigned char ch_DefaultMirrorFlag;
extern int d3_ActiveScene;
extern char* evt_WaitingScriptTask;
extern char* evt_CurrentScript;
extern int evt_ActiveContextId;

void __cdecl ch_SetPosition(char* obj, float* position, int flag);
void __cdecl ch_UpdatePendingPositions(void);
void __cdecl ch_UpdateAttachedModelPosition(char* obj, unsigned char force);
void __cdecl ch_Updatelowpoly(char* obj);

int __cdecl ch_MoveCharacter2Universe(char* obj, void* universe);


/* Reconstructed model byte view and floating-point position contracts. */
int __cdecl ch_CreateMesh(char* model, char* resource, float* position);
char* __cdecl ch_CreateAtPosition(char* resource, float* position);
char* __cdecl cut_CreateCharacterAtPosition(char* resource, float* position);

/* Character camera adapters use a game-object byte view and float vectors. */
void __cdecl ch_GetCameraView(char* object, int view, float* position, float* rotation);
void __cdecl ch_SetCameraView(char* object, int view);
void __cdecl ch_AnimateCameraView(char* object, int view, int mode);

#endif
