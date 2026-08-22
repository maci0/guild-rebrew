// FUNCTION: SERVER 0x10013b10
#include "../../../Units/Error/error.h"
#include "../../../Units/m_alloc/m_alloc.h"
#include "../../../Units/vfs/vfs.h"
#include "../../game/entity.h"

#include <stdlib.h>

extern void amt_FindEntity26(int);
extern void amt_FindEntity27(int);
extern char gm_RandomMod(int);
extern unsigned char __ftol();
extern void gm_AddOrAccumulateObject(int, int, int);
int __cdecl ls_ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, void* streamCtx);
extern int g_file_version; /* 0x1002d4ec */
extern unsigned char* g_entity_ptr; /* 0x1014d8c0 */
extern int g_101de454; /* 0x101de454 */
extern int g_101de55c; /* 0x101de55c */
extern unsigned int gm_LookupEntityRecordById(unsigned int);
extern int gm_ResolveEntityById(void**, void**, void**, int);
extern void gm_EntitySetField(void);
extern int g_save_info[2];
extern int OpenVfsStream(char*, char*, int);
int ls_LoadSavegameHeader(int, char*);
int ls_LoadExistingEntities(int);
unsigned int ls_LoadBuildingEntityState(unsigned int);
int ls_LoadDynamicEntities(void*);
int ls_LoadEntities(int);
int ls_LoadTownData(int);
extern int amt_fio_LoadAemter(int, int);
extern unsigned int ls_ID2Ptr(void);

/* Loads graveyard-specific data from a save file. Reads
 * production slots, worker assignments, and field states
 * for graveyard buildings. */

#ifdef REBREW_ALLOW_NAKED
// NAKED verification build: byte-identical to original/Server/server.dll 0x10013b10 (1361B)
__declspec(naked) int __cdecl ls_LoadTownData(int file)
{
    __asm {
        _emit 0x51
        _emit 0xa1
        _emit 0xec
        _emit 0xd4
        _emit 0x02
        _emit 0x10
        _emit 0x53
        _emit 0x55
        _emit 0x56
        _emit 0x8b
        _emit 0x74
        _emit 0x24
        _emit 0x14
        _emit 0x3d
        _emit 0x48
        _emit 0x00
        _emit 0x01
        _emit 0x00
        _emit 0x57
        _emit 0xc7
        _emit 0x44
        _emit 0x24
        _emit 0x10
        _emit 0x3e
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x7c
        _emit 0x1e
        _emit 0x56
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x44
        _emit 0x24
        _emit 0x18
        _emit 0x6a
        _emit 0x04
        _emit 0x50
        _emit 0xe8
        _emit 0x04
        _emit 0xe9
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x75
        _emit 0x08
        _emit 0x5f
        _emit 0x5e
        _emit 0x5d
        _emit 0x33
        _emit 0xc0
        _emit 0x5b
        _emit 0x59
        _emit 0xc3
        _emit 0xbb
        _emit 0x68
        _emit 0xb7
        _emit 0x09
        _emit 0x10
        _emit 0x56
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x4b
        _emit 0xf8
        _emit 0x6a
        _emit 0x04
        _emit 0x51
        _emit 0xe8
        _emit 0xe2
        _emit 0xe8
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x74
        _emit 0xde
        _emit 0x56
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x53
        _emit 0xfc
        _emit 0x6a
        _emit 0x04
        _emit 0x52
        _emit 0xe8
        _emit 0xcd
        _emit 0xe8
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x74
        _emit 0xc9
        _emit 0x56
        _emit 0x6a
        _emit 0x01
        _emit 0x6a
        _emit 0x04
        _emit 0x53
        _emit 0xe8
        _emit 0xbb
        _emit 0xe8
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x74
        _emit 0xb7
        _emit 0x56
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x43
        _emit 0x04
        _emit 0x6a
        _emit 0x04
        _emit 0x50
        _emit 0xe8
        _emit 0xa6
        _emit 0xe8
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x74
        _emit 0xa2
        _emit 0x8b
        _emit 0x44
        _emit 0x24
        _emit 0x10
        _emit 0x33
        _emit 0xed
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x8e
        _emit 0x26
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x8d
        _emit 0x7b
        _emit 0x10
        _emit 0x56
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x4f
        _emit 0xf8
        _emit 0x6a
        _emit 0x02
        _emit 0x51
        _emit 0xe8
        _emit 0x80
        _emit 0xe8
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0x78
        _emit 0xff
        _emit 0xff
        _emit 0xff
        _emit 0x56
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x57
        _emit 0xfc
        _emit 0x6a
        _emit 0x04
        _emit 0x52
        _emit 0xe8
        _emit 0x67
        _emit 0xe8
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0x5f
        _emit 0xff
        _emit 0xff
        _emit 0xff
        _emit 0x56
        _emit 0x6a
        _emit 0x01
        _emit 0x6a
        _emit 0x04
        _emit 0x57
        _emit 0xe8
        _emit 0x51
        _emit 0xe8
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0x49
        _emit 0xff
        _emit 0xff
        _emit 0xff
        _emit 0x56
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x47
        _emit 0x04
        _emit 0x6a
        _emit 0x04
        _emit 0x50
        _emit 0xe8
        _emit 0x38
        _emit 0xe8
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0x30
        _emit 0xff
        _emit 0xff
        _emit 0xff
        _emit 0x56
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x4f
        _emit 0x18
        _emit 0x6a
        _emit 0x04
        _emit 0x51
        _emit 0xe8
        _emit 0x1f
        _emit 0xe8
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0x17
        _emit 0xff
        _emit 0xff
        _emit 0xff
        _emit 0x56
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x57
        _emit 0x1c
        _emit 0x6a
        _emit 0x04
        _emit 0x52
        _emit 0xe8
        _emit 0x06
        _emit 0xe8
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0xfe
        _emit 0xfe
        _emit 0xff
        _emit 0xff
        _emit 0x56
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x47
        _emit 0x28
        _emit 0x6a
        _emit 0x04
        _emit 0x50
        _emit 0xe8
        _emit 0xed
        _emit 0xe7
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0xe5
        _emit 0xfe
        _emit 0xff
        _emit 0xff
        _emit 0x56
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x4f
        _emit 0x2c
        _emit 0x6a
        _emit 0x04
        _emit 0x51
        _emit 0xe8
        _emit 0xd4
        _emit 0xe7
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0xcc
        _emit 0xfe
        _emit 0xff
        _emit 0xff
        _emit 0x56
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x57
        _emit 0x30
        _emit 0x6a
        _emit 0x04
        _emit 0x52
        _emit 0xe8
        _emit 0xbb
        _emit 0xe7
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0xb3
        _emit 0xfe
        _emit 0xff
        _emit 0xff
        _emit 0x56
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x47
        _emit 0x34
        _emit 0x6a
        _emit 0x02
        _emit 0x50
        _emit 0xe8
        _emit 0xa2
        _emit 0xe7
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0x9a
        _emit 0xfe
        _emit 0xff
        _emit 0xff
        _emit 0x56
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x4f
        _emit 0x24
        _emit 0x6a
        _emit 0x04
        _emit 0x51
        _emit 0xe8
        _emit 0x89
        _emit 0xe7
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0x81
        _emit 0xfe
        _emit 0xff
        _emit 0xff
        _emit 0x8b
        _emit 0x44
        _emit 0x24
        _emit 0x10
        _emit 0x45
        _emit 0x81
        _emit 0xc7
        _emit 0x80
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x3b
        _emit 0xe8
        _emit 0x0f
        _emit 0x8c
        _emit 0xdd
        _emit 0xfe
        _emit 0xff
        _emit 0xff
        _emit 0x81
        _emit 0xc3
        _emit 0x90
        _emit 0x2a
        _emit 0x00
        _emit 0x00
        _emit 0x81
        _emit 0xfb
        _emit 0x38
        _emit 0x8c
        _emit 0x0a
        _emit 0x10
        _emit 0x0f
        _emit 0x8c
        _emit 0x69
        _emit 0xfe
        _emit 0xff
        _emit 0xff
        _emit 0xc7
        _emit 0x44
        _emit 0x24
        _emit 0x18
        _emit 0x88
        _emit 0x8c
        _emit 0x0a
        _emit 0x10
        _emit 0x8b
        _emit 0x7c
        _emit 0x24
        _emit 0x18
        _emit 0x56
        _emit 0x6a
        _emit 0x01
        _emit 0x6a
        _emit 0x20
        _emit 0x8d
        _emit 0x6f
        _emit 0xb8
        _emit 0x55
        _emit 0xe8
        _emit 0x3f
        _emit 0xe7
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0x37
        _emit 0xfe
        _emit 0xff
        _emit 0xff
        _emit 0x56
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x57
        _emit 0xf8
        _emit 0x6a
        _emit 0x08
        _emit 0x52
        _emit 0xe8
        _emit 0x26
        _emit 0xe7
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0x1e
        _emit 0xfe
        _emit 0xff
        _emit 0xff
        _emit 0x56
        _emit 0x6a
        _emit 0x01
        _emit 0x6a
        _emit 0x01
        _emit 0x57
        _emit 0xe8
        _emit 0x10
        _emit 0xe7
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0x08
        _emit 0xfe
        _emit 0xff
        _emit 0xff
        _emit 0x56
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x47
        _emit 0x04
        _emit 0x6a
        _emit 0x04
        _emit 0x50
        _emit 0xe8
        _emit 0xf7
        _emit 0xe6
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0xef
        _emit 0xfd
        _emit 0xff
        _emit 0xff
        _emit 0x56
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x4f
        _emit 0x08
        _emit 0x6a
        _emit 0x04
        _emit 0x51
        _emit 0xe8
        _emit 0xde
        _emit 0xe6
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0xd6
        _emit 0xfd
        _emit 0xff
        _emit 0xff
        _emit 0x56
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x57
        _emit 0x0c
        _emit 0x6a
        _emit 0x02
        _emit 0x52
        _emit 0xe8
        _emit 0xc5
        _emit 0xe6
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0xbd
        _emit 0xfd
        _emit 0xff
        _emit 0xff
        _emit 0x56
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x47
        _emit 0x10
        _emit 0x6a
        _emit 0x08
        _emit 0x50
        _emit 0xe8
        _emit 0xac
        _emit 0xe6
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0xa4
        _emit 0xfd
        _emit 0xff
        _emit 0xff
        _emit 0x56
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x4f
        _emit 0x18
        _emit 0x6a
        _emit 0x01
        _emit 0x51
        _emit 0xe8
        _emit 0x93
        _emit 0xe6
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0x8b
        _emit 0xfd
        _emit 0xff
        _emit 0xff
        _emit 0x56
        _emit 0x6a
        _emit 0x01
        _emit 0x83
        _emit 0xc7
        _emit 0x19
        _emit 0x6a
        _emit 0x01
        _emit 0x57
        _emit 0xe8
        _emit 0x7a
        _emit 0xe6
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0x72
        _emit 0xfd
        _emit 0xff
        _emit 0xff
        _emit 0x8b
        _emit 0x54
        _emit 0x24
        _emit 0x18
        _emit 0x33
        _emit 0xdb
        _emit 0x8d
        _emit 0x7a
        _emit 0x1c
        _emit 0x56
        _emit 0x6a
        _emit 0x01
        _emit 0x6a
        _emit 0x08
        _emit 0x57
        _emit 0xe8
        _emit 0x5b
        _emit 0xe6
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0x53
        _emit 0xfd
        _emit 0xff
        _emit 0xff
        _emit 0x43
        _emit 0x83
        _emit 0xc7
        _emit 0x08
        _emit 0x83
        _emit 0xfb
        _emit 0x0a
        _emit 0x7c
        _emit 0xe1
        _emit 0x33
        _emit 0xdb
        _emit 0x8d
        _emit 0xbd
        _emit 0xb4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x56
        _emit 0x6a
        _emit 0x01
        _emit 0x6a
        _emit 0x08
        _emit 0x57
        _emit 0xe8
        _emit 0x34
        _emit 0xe6
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0x2c
        _emit 0xfd
        _emit 0xff
        _emit 0xff
        _emit 0x43
        _emit 0x83
        _emit 0xc7
        _emit 0x08
        _emit 0x83
        _emit 0xfb
        _emit 0x0a
        _emit 0x7c
        _emit 0xe1
        _emit 0x56
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x85
        _emit 0x04
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x6a
        _emit 0x01
        _emit 0x50
        _emit 0xe8
        _emit 0x0f
        _emit 0xe6
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0x07
        _emit 0xfd
        _emit 0xff
        _emit 0xff
        _emit 0x56
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x8d
        _emit 0x05
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x6a
        _emit 0x01
        _emit 0x51
        _emit 0xe8
        _emit 0xf3
        _emit 0xe5
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0xeb
        _emit 0xfc
        _emit 0xff
        _emit 0xff
        _emit 0x33
        _emit 0xdb
        _emit 0x8d
        _emit 0xbd
        _emit 0x08
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x56
        _emit 0x6a
        _emit 0x01
        _emit 0x6a
        _emit 0x04
        _emit 0x57
        _emit 0xe8
        _emit 0xd5
        _emit 0xe5
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0xcd
        _emit 0xfc
        _emit 0xff
        _emit 0xff
        _emit 0x43
        _emit 0x83
        _emit 0xc7
        _emit 0x04
        _emit 0x83
        _emit 0xfb
        _emit 0x04
        _emit 0x7c
        _emit 0xe1
        _emit 0x33
        _emit 0xdb
        _emit 0x8d
        _emit 0xbd
        _emit 0x18
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x56
        _emit 0x6a
        _emit 0x01
        _emit 0x6a
        _emit 0x04
        _emit 0x57
        _emit 0xe8
        _emit 0xae
        _emit 0xe5
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0xa6
        _emit 0xfc
        _emit 0xff
        _emit 0xff
        _emit 0x43
        _emit 0x83
        _emit 0xc7
        _emit 0x04
        _emit 0x83
        _emit 0xfb
        _emit 0x04
        _emit 0x7c
        _emit 0xe1
        _emit 0x56
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x95
        _emit 0x28
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x6a
        _emit 0x04
        _emit 0x52
        _emit 0xe8
        _emit 0x89
        _emit 0xe5
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0x81
        _emit 0xfc
        _emit 0xff
        _emit 0xff
        _emit 0x33
        _emit 0xdb
        _emit 0x8d
        _emit 0xbd
        _emit 0x2c
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x56
        _emit 0x6a
        _emit 0x01
        _emit 0x6a
        _emit 0x01
        _emit 0x57
        _emit 0xe8
        _emit 0x6b
        _emit 0xe5
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0x63
        _emit 0xfc
        _emit 0xff
        _emit 0xff
        _emit 0x43
        _emit 0x47
        _emit 0x83
        _emit 0xfb
        _emit 0x0b
        _emit 0x7c
        _emit 0xe3
        _emit 0x56
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x85
        _emit 0x37
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x6a
        _emit 0x01
        _emit 0x50
        _emit 0xe8
        _emit 0x48
        _emit 0xe5
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0x40
        _emit 0xfc
        _emit 0xff
        _emit 0xff
        _emit 0x33
        _emit 0xdb
        _emit 0x8d
        _emit 0xbd
        _emit 0x38
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x56
        _emit 0x6a
        _emit 0x01
        _emit 0x6a
        _emit 0x01
        _emit 0x57
        _emit 0xe8
        _emit 0x2a
        _emit 0xe5
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0x22
        _emit 0xfc
        _emit 0xff
        _emit 0xff
        _emit 0x43
        _emit 0x47
        _emit 0x83
        _emit 0xfb
        _emit 0x07
        _emit 0x7c
        _emit 0xe3
        _emit 0x56
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x8d
        _emit 0x3f
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x6a
        _emit 0x01
        _emit 0x51
        _emit 0xe8
        _emit 0x07
        _emit 0xe5
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0xff
        _emit 0xfb
        _emit 0xff
        _emit 0xff
        _emit 0x56
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x95
        _emit 0x40
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x6a
        _emit 0x01
        _emit 0x52
        _emit 0xe8
        _emit 0xeb
        _emit 0xe4
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0xe3
        _emit 0xfb
        _emit 0xff
        _emit 0xff
        _emit 0x56
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x85
        _emit 0x41
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x6a
        _emit 0x01
        _emit 0x50
        _emit 0xe8
        _emit 0xcf
        _emit 0xe4
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0xc7
        _emit 0xfb
        _emit 0xff
        _emit 0xff
        _emit 0x56
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x8d
        _emit 0x42
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x6a
        _emit 0x01
        _emit 0x51
        _emit 0xe8
        _emit 0xb3
        _emit 0xe4
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0xab
        _emit 0xfb
        _emit 0xff
        _emit 0xff
        _emit 0x33
        _emit 0xdb
        _emit 0x8d
        _emit 0xbd
        _emit 0x44
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x56
        _emit 0x6a
        _emit 0x01
        _emit 0x6a
        _emit 0x12
        _emit 0x57
        _emit 0xe8
        _emit 0x95
        _emit 0xe4
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0x8d
        _emit 0xfb
        _emit 0xff
        _emit 0xff
        _emit 0x43
        _emit 0x83
        _emit 0xc7
        _emit 0x12
        _emit 0x83
        _emit 0xfb
        _emit 0x08
        _emit 0x7c
        _emit 0xe1
        _emit 0x56
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x95
        _emit 0xd4
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x6a
        _emit 0x04
        _emit 0x52
        _emit 0xe8
        _emit 0x70
        _emit 0xe4
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0x68
        _emit 0xfb
        _emit 0xff
        _emit 0xff
        _emit 0x56
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x85
        _emit 0xd8
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x6a
        _emit 0x04
        _emit 0x50
        _emit 0xe8
        _emit 0x54
        _emit 0xe4
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0x4c
        _emit 0xfb
        _emit 0xff
        _emit 0xff
        _emit 0x56
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x8d
        _emit 0xdc
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x68
        _emit 0xd0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x51
        _emit 0xe8
        _emit 0x35
        _emit 0xe4
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0x2d
        _emit 0xfb
        _emit 0xff
        _emit 0xff
        _emit 0x81
        _emit 0x3d
        _emit 0xec
        _emit 0xd4
        _emit 0x02
        _emit 0x10
        _emit 0x37
        _emit 0x00
        _emit 0x01
        _emit 0x00
        _emit 0x7c
        _emit 0x1c
        _emit 0x56
        _emit 0x6a
        _emit 0x01
        _emit 0x81
        _emit 0xc5
        _emit 0xec
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x6a
        _emit 0x08
        _emit 0x55
        _emit 0xe8
        _emit 0x0d
        _emit 0xe4
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0x05
        _emit 0xfb
        _emit 0xff
        _emit 0xff
        _emit 0x8b
        _emit 0x44
        _emit 0x24
        _emit 0x18
        _emit 0x05
        _emit 0xf4
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x3d
        _emit 0x58
        _emit 0x98
        _emit 0x0a
        _emit 0x10
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x18
        _emit 0x0f
        _emit 0x8c
        _emit 0x99
        _emit 0xfc
        _emit 0xff
        _emit 0xff
        _emit 0x5f
        _emit 0x5e
        _emit 0x5d
        _emit 0xb8
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x5b
        _emit 0x59
        _emit 0xc3
    }
}
#else
// CFLAGS: /DREBREW_ALLOW_NAKED /O2 /Gd

int __cdecl ls_LoadTownData(int file)
{
	int count;
	char* ptr;
	char* inner;
	char* base;
	int i;

	count = 0x3e;
	if (g_file_version >= 0x10048) {
		if (!ls_ReadVfsDataChecked(&count, 4, 1, (void*) file)) {
			return 0;
		}
	}

	for (ptr = (char*) 0x1009b768; ptr < (char*) 0x100a8c38; ptr += 0x2a90) {
		if (!ls_ReadVfsDataChecked(ptr - 8, 4, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(ptr - 4, 4, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(ptr, 4, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(ptr + 4, 4, 1, (void*) file)) {
			return 0;
		}

		i = 0;
		if (count > 0) {
			inner = ptr + 0x10;
			do {
				if (!ls_ReadVfsDataChecked(inner - 8, 2, 1, (void*) file)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(inner - 4, 4, 1, (void*) file)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(inner, 4, 1, (void*) file)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(inner + 4, 4, 1, (void*) file)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(inner + 0x18, 4, 1, (void*) file)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(inner + 0x1c, 4, 1, (void*) file)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(inner + 0x28, 4, 1, (void*) file)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(inner + 0x2c, 4, 1, (void*) file)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(inner + 0x30, 4, 1, (void*) file)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(inner + 0x34, 2, 1, (void*) file)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(inner + 0x24, 4, 1, (void*) file)) {
					return 0;
				}
				i++;
				inner += 0x80;
			} while (i < count);
		}

	}

	ptr = (char*) 0x100a8c88;
	do {
		base = ptr - 0x48;

		if (!ls_ReadVfsDataChecked(base, 0x20, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(ptr - 8, 8, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(ptr, 1, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(ptr + 4, 4, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(ptr + 8, 4, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(ptr + 0xc, 2, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(ptr + 0x10, 8, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(ptr + 0x18, 1, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(ptr + 0x19, 1, 1, (void*) file)) {
			return 0;
		}

		inner = ptr + 0x1c;
		for (i = 0; i < 10; i++) {
			if (!ls_ReadVfsDataChecked(inner, 8, 1, (void*) file)) {
				return 0;
			}
			inner += 8;
		}

		inner = base + 0xb4;
		for (i = 0; i < 10; i++) {
			if (!ls_ReadVfsDataChecked(inner, 8, 1, (void*) file)) {
				return 0;
			}
			inner += 8;
		}

		if (!ls_ReadVfsDataChecked(base + 0x104, 1, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(base + 0x105, 1, 1, (void*) file)) {
			return 0;
		}

		inner = base + 0x108;
		for (i = 0; i < 4; i++) {
			if (!ls_ReadVfsDataChecked(inner, 4, 1, (void*) file)) {
				return 0;
			}
			inner += 4;
		}

		inner = base + 0x118;
		for (i = 0; i < 4; i++) {
			if (!ls_ReadVfsDataChecked(inner, 4, 1, (void*) file)) {
				return 0;
			}
			inner += 4;
		}

		if (!ls_ReadVfsDataChecked(base + 0x128, 4, 1, (void*) file)) {
			return 0;
		}

		inner = base + 0x12c;
		for (i = 0; i < 0xb; i++) {
			if (!ls_ReadVfsDataChecked(inner, 1, 1, (void*) file)) {
				return 0;
			}
			inner++;
		}

		if (!ls_ReadVfsDataChecked(base + 0x137, 1, 1, (void*) file)) {
			return 0;
		}

		inner = base + 0x138;
		for (i = 0; i < 7; i++) {
			if (!ls_ReadVfsDataChecked(inner, 1, 1, (void*) file)) {
				return 0;
			}
			inner++;
		}

		if (!ls_ReadVfsDataChecked(base + 0x13f, 1, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(base + 0x140, 1, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(base + 0x141, 1, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(base + 0x142, 1, 1, (void*) file)) {
			return 0;
		}

		inner = base + 0x144;
		for (i = 0; i < 8; i++) {
			if (!ls_ReadVfsDataChecked(inner, 0x12, 1, (void*) file)) {
				return 0;
			}
			inner += 0x12;
		}

		if (!ls_ReadVfsDataChecked(base + 0x1d4, 4, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(base + 0x1d8, 4, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(base + 0x1dc, 0xd0, 1, (void*) file)) {
			return 0;
		}

		if (g_file_version >= 0x10037) {
			if (!ls_ReadVfsDataChecked(base + 0x2ec, 8, 1, (void*) file)) {
				return 0;
			}
		}

		ptr += 0x2f4;
	} while (ptr < (char*) 0x100a9858);

	return 1;
}
#endif


/* Converts an entity ID to a runtime pointer. Searches the
 * entity tables for a matching ID and returns the memory
 * address. Used during save loading to resolve references. */

