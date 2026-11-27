#ifndef D3_D3D_H
#define D3_D3D_H

/* Native pointer/scalar views; complete allocation owners remain unresolved. */
extern void* d3d_Device;
extern int d3d_LastResult;

int __cdecl d3d_LogResultError(char* source, int line, char* expression);
void __cdecl d3d_EndScene(void);
void __cdecl d3_PrecacheAllSceneTextures(int flag);
void __cdecl d3_PrecacheObjectTextures(char* object);

#ifdef REBREW_GOLD
/* Attested name; accessed buffer view, complete allocation/owner unresolved. */
/* ADDRESS: GOLD 0x00fe7a20 */
extern char d3d_PrecacheBuffer[];
void __cdecl d3d_PrecacheTexture(void* t);
#endif

#endif
