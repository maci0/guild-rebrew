#ifndef CLIENT_SCENE_LOADER_H
#define CLIENT_SCENE_LOADER_H

/* Inferred callback name; native calls pass three full-width integers. */
typedef void (__cdecl* SCENE_PROGRESS)(int stage, int done, int total);

#ifdef REBREW_GOLD
void __cdecl d3_ReloadAllTextures(int selector, SCENE_PROGRESS progress);
char __cdecl d3_LoadSceneStream(const char* filename, void* stream, SCENE_PROGRESS progress);
#else
/* Inferred context names; native callback reads match these five slots. */
typedef struct SCENE_PROGRESS_CONTEXT {
    SCENE_PROGRESS fn;
    int id;
    int total;
    int count;
    char skip;
} SCENE_PROGRESS_CONTEXT;

void __cdecl d3_ReloadSceneTextureSurfaces(SCENE_PROGRESS progress);
void __cdecl d3_ConfigureSceneRenderQuality(unsigned char a1, int a2, unsigned char a3,
    unsigned int a4, SCENE_PROGRESS progress);
void __cdecl d3_ReloadSceneResources(int mask, int id, SCENE_PROGRESS progress);
char __cdecl d3_ReloadObjectResourcesCallback(char* object, SCENE_PROGRESS_CONTEXT* context);
char __cdecl d3_LoadScene(const char* filename, void* stream, SCENE_PROGRESS progress);
#endif

void __cdecl d2_UpdateSceneLoadProgress(int mode, int done, int total);
int __cdecl d3_LoadSceneAndTerrain(void* stream);
int __cdecl ecmd_LoadScene(char** filename);

#endif
