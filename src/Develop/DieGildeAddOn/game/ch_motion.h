#ifndef CH_MOTION_H
#define CH_MOTION_H

/* Inferred names; declarations describe accessed fields, not storage owners. */
extern int ch_MorphFrameValue;
void __cdecl ch_PreloadModelMotions(char* model, int n, ...);
void __cdecl ch_FinishAni(char* obj);

/* Provisional game views; extern declarations allocate no storage. */
extern float g_662d70[4];
extern unsigned char g_6752a4;
extern int g_67a370;
extern char* g_6b7ebc;
extern char* g_6b7e98;
extern int g_6791c8;

void __cdecl ch_SetPosition(char* obj, float* position, int flag);
void __cdecl ch_UpdatePendingPositions(void);
void __cdecl ch_UpdateAttachedModelPosition(char* obj, unsigned char force);
void __cdecl ch_Updatelowpoly(char* obj);

int __cdecl ch_MoveCharacter2Universe(char* obj, void* universe);
int __cdecl TakeObjectScript(char** ch, char** ani, int* kind, char** dummy,
    unsigned char* level, char** func);

/* Reconstructed model byte view and floating-point position contracts. */
int __cdecl ch_CreateMesh(char* model, char* resource, float* position);
char* __cdecl fcn_00403b90(char* resource, float* position);
char* __cdecl fcn_004e4a80(char* resource, float* position);

#endif
