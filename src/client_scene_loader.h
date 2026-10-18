#ifndef CLIENT_SCENE_LOADER_H
#define CLIENT_SCENE_LOADER_H

/* Inferred callback name; native calls pass three full-width integers. */
typedef void (__cdecl* SCENE_PROGRESS)(int stage, int done, int total);

#ifdef REBREW_GOLD
void __cdecl fcn_00461080(int selector, SCENE_PROGRESS progress);
char __cdecl fcn_0044be60(const char* filename, void* stream, SCENE_PROGRESS progress);
#else
/* Inferred context names; native callback reads match these five slots. */
typedef struct SCENE_PROGRESS_CONTEXT {
    SCENE_PROGRESS fn;
    int id;
    int total;
    int count;
    char skip;
} SCENE_PROGRESS_CONTEXT;

void __cdecl fcn_0045cfa0(SCENE_PROGRESS progress);
void __cdecl fcn_00439690(unsigned char a1, int a2, unsigned char a3,
    unsigned int a4, SCENE_PROGRESS progress);
void __cdecl fcn_0043ac00(int mask, int id, SCENE_PROGRESS progress);
char __cdecl fcn_0043aad0(char* object, SCENE_PROGRESS_CONTEXT* context);
char __cdecl fcn_00448360(const char* filename, void* stream, SCENE_PROGRESS progress);
#endif

void __cdecl fcn_0053f6a0(int mode, int done, int total);
int __cdecl fcn_005222a0(void* stream);
int __cdecl ecmd_LoadScene(char** filename);

#endif
