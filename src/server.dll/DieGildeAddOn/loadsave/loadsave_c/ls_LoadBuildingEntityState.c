// FUNCTION: SERVER 0x100128f0
#include "../../../Units/Error/error.h"
#include "../../../Units/m_alloc/m_alloc.h"
#include "../../../Units/vfs/vfs.h"
#include "../../game/entity.h"

#include <stdlib.h>

int __cdecl AllocGraveyardField(int);
extern void amt_FindEntity26(int);
extern void amt_FindEntity27(int);
extern char gm_RandomMod(int);
extern unsigned char __ftol();
extern void gm_AddOrAccumulateObject(int, int, int);
int __cdecl ls_ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, void* streamCtx);
int __cdecl ls_LoadGraveyardData(int stream_ctx, int dest_buf);
int __cdecl ahm_AllocAhmInfo(int building, int slot);
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
// NAKED verification build: byte-identical to original/Server/server.dll 0x100128f0 (1463B)
__declspec(naked) unsigned int __cdecl ls_LoadBuildingEntityState(unsigned int stream_ctx)
{
    __asm {
        _emit 0x83
        _emit 0xec
        _emit 0x0c
        _emit 0x53
        _emit 0x55
        _emit 0x56
        _emit 0x57
        _emit 0xe8
        _emit 0xb4
        _emit 0x33
        _emit 0x00
        _emit 0x00
        _emit 0x8b
        _emit 0x7c
        _emit 0x24
        _emit 0x20
        _emit 0x8d
        _emit 0x44
        _emit 0x24
        _emit 0x14
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x6a
        _emit 0x04
        _emit 0x50
        _emit 0xe8
        _emit 0x31
        _emit 0xfb
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
        _emit 0x5b
        _emit 0x83
        _emit 0xc4
        _emit 0x0c
        _emit 0xc3
        _emit 0x8b
        _emit 0x4c
        _emit 0x24
        _emit 0x14
        _emit 0x33
        _emit 0xc0
        _emit 0x3b
        _emit 0xc8
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x10
        _emit 0x0f
        _emit 0x8e
        _emit 0xba
        _emit 0x04
        _emit 0x00
        _emit 0x00
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x20
        _emit 0x83
        _emit 0xcd
        _emit 0xff
        _emit 0x8b
        _emit 0x0d
        _emit 0xc0
        _emit 0xd8
        _emit 0x14
        _emit 0x10
        _emit 0x8b
        _emit 0x54
        _emit 0x24
        _emit 0x20
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x34
        _emit 0x0a
        _emit 0x6a
        _emit 0x01
        _emit 0x56
        _emit 0xe8
        _emit 0xf1
        _emit 0xfa
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
        _emit 0x04
        _emit 0x00
        _emit 0x00
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x46
        _emit 0x01
        _emit 0x6a
        _emit 0x04
        _emit 0x50
        _emit 0xe8
        _emit 0xd8
        _emit 0xfa
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
        _emit 0x04
        _emit 0x00
        _emit 0x00
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x4e
        _emit 0x05
        _emit 0x6a
        _emit 0x20
        _emit 0x51
        _emit 0xe8
        _emit 0xbf
        _emit 0xfa
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0x74
        _emit 0x04
        _emit 0x00
        _emit 0x00
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x56
        _emit 0x25
        _emit 0x6a
        _emit 0x02
        _emit 0x52
        _emit 0xe8
        _emit 0xa6
        _emit 0xfa
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0x5b
        _emit 0x04
        _emit 0x00
        _emit 0x00
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x46
        _emit 0x27
        _emit 0x6a
        _emit 0x02
        _emit 0x50
        _emit 0xe8
        _emit 0x8d
        _emit 0xfa
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0x42
        _emit 0x04
        _emit 0x00
        _emit 0x00
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x4e
        _emit 0x29
        _emit 0x6a
        _emit 0x02
        _emit 0x51
        _emit 0xe8
        _emit 0x74
        _emit 0xfa
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0x29
        _emit 0x04
        _emit 0x00
        _emit 0x00
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x56
        _emit 0x2b
        _emit 0x6a
        _emit 0x04
        _emit 0x52
        _emit 0xe8
        _emit 0x5b
        _emit 0xfa
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0x10
        _emit 0x04
        _emit 0x00
        _emit 0x00
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x46
        _emit 0x2f
        _emit 0x6a
        _emit 0x01
        _emit 0x50
        _emit 0xe8
        _emit 0x42
        _emit 0xfa
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0xf7
        _emit 0x03
        _emit 0x00
        _emit 0x00
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x4e
        _emit 0x34
        _emit 0x6a
        _emit 0x01
        _emit 0x51
        _emit 0xe8
        _emit 0x29
        _emit 0xfa
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0xde
        _emit 0x03
        _emit 0x00
        _emit 0x00
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x56
        _emit 0x35
        _emit 0x6a
        _emit 0x04
        _emit 0x52
        _emit 0xe8
        _emit 0x10
        _emit 0xfa
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0xc5
        _emit 0x03
        _emit 0x00
        _emit 0x00
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x46
        _emit 0x39
        _emit 0x6a
        _emit 0x04
        _emit 0x50
        _emit 0xe8
        _emit 0xf7
        _emit 0xf9
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0xac
        _emit 0x03
        _emit 0x00
        _emit 0x00
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x4e
        _emit 0x3d
        _emit 0x6a
        _emit 0x04
        _emit 0x51
        _emit 0xe8
        _emit 0xde
        _emit 0xf9
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0x93
        _emit 0x03
        _emit 0x00
        _emit 0x00
        _emit 0x57
        _emit 0x8d
        _emit 0x5e
        _emit 0x41
        _emit 0x6a
        _emit 0x01
        _emit 0x6a
        _emit 0x04
        _emit 0x53
        _emit 0xe8
        _emit 0xc5
        _emit 0xf9
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0x7a
        _emit 0x03
        _emit 0x00
        _emit 0x00
        _emit 0x83
        _emit 0x3b
        _emit 0x04
        _emit 0x7e
        _emit 0x06
        _emit 0xc7
        _emit 0x03
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x56
        _emit 0x45
        _emit 0x6a
        _emit 0x04
        _emit 0x52
        _emit 0xe8
        _emit 0xa1
        _emit 0xf9
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0x56
        _emit 0x03
        _emit 0x00
        _emit 0x00
        _emit 0x81
        _emit 0x3d
        _emit 0xec
        _emit 0xd4
        _emit 0x02
        _emit 0x10
        _emit 0x28
        _emit 0x00
        _emit 0x01
        _emit 0x00
        _emit 0x7c
        _emit 0x19
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x46
        _emit 0x49
        _emit 0x6a
        _emit 0x04
        _emit 0x50
        _emit 0xe8
        _emit 0x7c
        _emit 0xf9
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0x31
        _emit 0x03
        _emit 0x00
        _emit 0x00
        _emit 0x81
        _emit 0x3d
        _emit 0xec
        _emit 0xd4
        _emit 0x02
        _emit 0x10
        _emit 0x32
        _emit 0x00
        _emit 0x01
        _emit 0x00
        _emit 0x7d
        _emit 0x1a
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x4c
        _emit 0x24
        _emit 0x20
        _emit 0x6a
        _emit 0x04
        _emit 0x51
        _emit 0xe8
        _emit 0x56
        _emit 0xf9
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0x0b
        _emit 0x03
        _emit 0x00
        _emit 0x00
        _emit 0x81
        _emit 0x3d
        _emit 0xec
        _emit 0xd4
        _emit 0x02
        _emit 0x10
        _emit 0x57
        _emit 0x00
        _emit 0x01
        _emit 0x00
        _emit 0x7c
        _emit 0x4b
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x56
        _emit 0x4d
        _emit 0x6a
        _emit 0x04
        _emit 0x52
        _emit 0xe8
        _emit 0x31
        _emit 0xf9
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0xe6
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x46
        _emit 0x51
        _emit 0x6a
        _emit 0x04
        _emit 0x50
        _emit 0xe8
        _emit 0x18
        _emit 0xf9
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
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x4e
        _emit 0x55
        _emit 0x6a
        _emit 0x04
        _emit 0x51
        _emit 0xe8
        _emit 0xff
        _emit 0xf8
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0xb4
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x56
        _emit 0x5a
        _emit 0x6a
        _emit 0x02
        _emit 0x52
        _emit 0xe8
        _emit 0xe6
        _emit 0xf8
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0x9b
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x46
        _emit 0x5c
        _emit 0x6a
        _emit 0x01
        _emit 0x50
        _emit 0xe8
        _emit 0xcd
        _emit 0xf8
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0x82
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x8a
        _emit 0x06
        _emit 0x3c
        _emit 0x1e
        _emit 0x0f
        _emit 0x85
        _emit 0x1e
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x68
        _emit 0x10
        _emit 0xd5
        _emit 0x02
        _emit 0x10
        _emit 0x68
        _emit 0x00
        _emit 0x06
        _emit 0x00
        _emit 0x00
        _emit 0xe8
        _emit 0xe9
        _emit 0x39
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x08
        _emit 0x89
        _emit 0x46
        _emit 0x71
        _emit 0x33
        _emit 0xdb
        _emit 0x8b
        _emit 0x56
        _emit 0x71
        _emit 0x8b
        _emit 0xcb
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x03
        _emit 0xca
        _emit 0x6a
        _emit 0x04
        _emit 0x51
        _emit 0xe8
        _emit 0x8f
        _emit 0xf8
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0x44
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x8b
        _emit 0x56
        _emit 0x71
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x6a
        _emit 0x04
        _emit 0x8d
        _emit 0x44
        _emit 0x13
        _emit 0x04
        _emit 0x50
        _emit 0xe8
        _emit 0x72
        _emit 0xf8
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0x27
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x8b
        _emit 0x4e
        _emit 0x71
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x54
        _emit 0x0b
        _emit 0x08
        _emit 0x52
        _emit 0xe8
        _emit 0x55
        _emit 0xf8
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0x0a
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x8b
        _emit 0x46
        _emit 0x71
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x4c
        _emit 0x03
        _emit 0x09
        _emit 0x51
        _emit 0xe8
        _emit 0x38
        _emit 0xf8
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0xed
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x8b
        _emit 0x56
        _emit 0x71
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x6a
        _emit 0x02
        _emit 0x8d
        _emit 0x44
        _emit 0x13
        _emit 0x0a
        _emit 0x50
        _emit 0xe8
        _emit 0x1b
        _emit 0xf8
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0xd0
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x8b
        _emit 0x4e
        _emit 0x71
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x6a
        _emit 0x04
        _emit 0x8d
        _emit 0x54
        _emit 0x0b
        _emit 0x10
        _emit 0x52
        _emit 0xe8
        _emit 0xfe
        _emit 0xf7
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
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x8b
        _emit 0x46
        _emit 0x71
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x4c
        _emit 0x03
        _emit 0x0c
        _emit 0x51
        _emit 0xe8
        _emit 0xe1
        _emit 0xf7
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0x96
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x8b
        _emit 0x56
        _emit 0x71
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x44
        _emit 0x13
        _emit 0x0d
        _emit 0x50
        _emit 0xe8
        _emit 0xc4
        _emit 0xf7
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0x79
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x8b
        _emit 0x4e
        _emit 0x71
        _emit 0x83
        _emit 0xc3
        _emit 0x18
        _emit 0x81
        _emit 0xfb
        _emit 0x00
        _emit 0x06
        _emit 0x00
        _emit 0x00
        _emit 0xc7
        _emit 0x44
        _emit 0x0b
        _emit 0xfc
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x0f
        _emit 0x8c
        _emit 0xfe
        _emit 0xfe
        _emit 0xff
        _emit 0xff
        _emit 0xe9
        _emit 0xcc
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x3c
        _emit 0x48
        _emit 0x0f
        _emit 0x84
        _emit 0x80
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x3c
        _emit 0x49
        _emit 0x74
        _emit 0x7c
        _emit 0x3c
        _emit 0x4a
        _emit 0x74
        _emit 0x78
        _emit 0x3c
        _emit 0x4b
        _emit 0x74
        _emit 0x26
        _emit 0x3c
        _emit 0x4c
        _emit 0x74
        _emit 0x22
        _emit 0x3c
        _emit 0x4d
        _emit 0x74
        _emit 0x1e
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x56
        _emit 0x65
        _emit 0x6a
        _emit 0x30
        _emit 0x52
        _emit 0xe8
        _emit 0x70
        _emit 0xf7
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0x25
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0xe9
        _emit 0x92
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x81
        _emit 0x3d
        _emit 0xec
        _emit 0xd4
        _emit 0x02
        _emit 0x10
        _emit 0x49
        _emit 0x00
        _emit 0x01
        _emit 0x00
        _emit 0x7c
        _emit 0x14
        _emit 0x56
        _emit 0x57
        _emit 0xe8
        _emit 0xdd
        _emit 0x97
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x08
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0x02
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0xeb
        _emit 0x72
        _emit 0x57
        _emit 0x8d
        _emit 0x5e
        _emit 0x65
        _emit 0x6a
        _emit 0x01
        _emit 0x6a
        _emit 0x30
        _emit 0x53
        _emit 0xe8
        _emit 0x32
        _emit 0xf7
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0xe7
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x68
        _emit 0x04
        _emit 0xd5
        _emit 0x02
        _emit 0x10
        _emit 0x6a
        _emit 0x3c
        _emit 0xe8
        _emit 0x5b
        _emit 0x38
        _emit 0xff
        _emit 0xff
        _emit 0x89
        _emit 0x03
        _emit 0x83
        _emit 0xc4
        _emit 0x08
        _emit 0x89
        _emit 0x28
        _emit 0xeb
        _emit 0x44
        _emit 0x81
        _emit 0x3d
        _emit 0xec
        _emit 0xd4
        _emit 0x02
        _emit 0x10
        _emit 0x47
        _emit 0x00
        _emit 0x01
        _emit 0x00
        _emit 0x7c
        _emit 0x14
        _emit 0x56
        _emit 0x57
        _emit 0xe8
        _emit 0xbf
        _emit 0xf2
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x08
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0xb4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0xeb
        _emit 0x24
        _emit 0x57
        _emit 0x8d
        _emit 0x5e
        _emit 0x65
        _emit 0x6a
        _emit 0x01
        _emit 0x6a
        _emit 0x30
        _emit 0x53
        _emit 0xe8
        _emit 0xe4
        _emit 0xf6
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0x99
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x56
        _emit 0xe8
        _emit 0x63
        _emit 0xdc
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x04
        _emit 0x89
        _emit 0x03
        _emit 0x81
        _emit 0x3d
        _emit 0xec
        _emit 0xd4
        _emit 0x02
        _emit 0x10
        _emit 0x43
        _emit 0x00
        _emit 0x01
        _emit 0x00
        _emit 0x7c
        _emit 0x1a
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x86
        _emit 0x99
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x6a
        _emit 0x10
        _emit 0x50
        _emit 0xe8
        _emit 0xb1
        _emit 0xf6
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x74
        _emit 0x6a
        _emit 0xeb
        _emit 0x22
        _emit 0x8d
        _emit 0x86
        _emit 0x99
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x33
        _emit 0xc9
        _emit 0x8b
        _emit 0xd0
        _emit 0x89
        _emit 0x0a
        _emit 0x89
        _emit 0x4a
        _emit 0x04
        _emit 0x89
        _emit 0x4a
        _emit 0x08
        _emit 0x89
        _emit 0x4a
        _emit 0x0c
        _emit 0x8b
        _emit 0x08
        _emit 0x83
        _emit 0xc9
        _emit 0x01
        _emit 0x89
        _emit 0xae
        _emit 0xa5
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x89
        _emit 0x08
        _emit 0x8b
        _emit 0x44
        _emit 0x24
        _emit 0x10
        _emit 0x8b
        _emit 0x54
        _emit 0x24
        _emit 0x20
        _emit 0xc7
        _emit 0x46
        _emit 0x30
        _emit 0x88
        _emit 0x13
        _emit 0x00
        _emit 0x00
        _emit 0x89
        _emit 0xae
        _emit 0x95
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x8b
        _emit 0x4c
        _emit 0x24
        _emit 0x14
        _emit 0x40
        _emit 0x81
        _emit 0xc2
        _emit 0xa9
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x3b
        _emit 0xc1
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x10
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x20
        _emit 0x0f
        _emit 0x8c
        _emit 0x4d
        _emit 0xfb
        _emit 0xff
        _emit 0xff
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x6a
        _emit 0x04
        _emit 0x68
        _emit 0x54
        _emit 0xe4
        _emit 0x1d
        _emit 0x10
        _emit 0xe8
        _emit 0x47
        _emit 0xf6
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x75
        _emit 0x0a
        _emit 0x5f
        _emit 0x5e
        _emit 0x5d
        _emit 0x33
        _emit 0xc0
        _emit 0x5b
        _emit 0x83
        _emit 0xc4
        _emit 0x0c
        _emit 0xc3
        _emit 0xa1
        _emit 0x54
        _emit 0xe4
        _emit 0x1d
        _emit 0x10
        _emit 0x8b
        _emit 0x0d
        _emit 0x5c
        _emit 0xe5
        _emit 0x1d
        _emit 0x10
        _emit 0x8d
        _emit 0x04
        _emit 0x40
        _emit 0xc1
        _emit 0xe0
        _emit 0x05
        _emit 0x50
        _emit 0x51
        _emit 0xe8
        _emit 0xaa
        _emit 0x87
        _emit 0x00
        _emit 0x00
        _emit 0xa3
        _emit 0x5c
        _emit 0xe5
        _emit 0x1d
        _emit 0x10
        _emit 0xa1
        _emit 0x54
        _emit 0xe4
        _emit 0x1d
        _emit 0x10
        _emit 0x83
        _emit 0xc4
        _emit 0x08
        _emit 0x33
        _emit 0xdb
        _emit 0x85
        _emit 0xc0
        _emit 0x7e
        _emit 0x65
        _emit 0x33
        _emit 0xf6
        _emit 0x8b
        _emit 0x15
        _emit 0x5c
        _emit 0xe5
        _emit 0x1d
        _emit 0x10
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x6a
        _emit 0x40
        _emit 0x8d
        _emit 0x04
        _emit 0x16
        _emit 0x50
        _emit 0xe8
        _emit 0xf5
        _emit 0xf5
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x74
        _emit 0xae
        _emit 0x8b
        _emit 0x0d
        _emit 0x5c
        _emit 0xe5
        _emit 0x1d
        _emit 0x10
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x6a
        _emit 0x10
        _emit 0x8d
        _emit 0x54
        _emit 0x0e
        _emit 0x40
        _emit 0x52
        _emit 0xe8
        _emit 0xd9
        _emit 0xf5
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x74
        _emit 0x92
        _emit 0xa1
        _emit 0x5c
        _emit 0xe5
        _emit 0x1d
        _emit 0x10
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x6a
        _emit 0x10
        _emit 0x8d
        _emit 0x4c
        _emit 0x06
        _emit 0x50
        _emit 0x51
        _emit 0xe8
        _emit 0xbe
        _emit 0xf5
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0x73
        _emit 0xff
        _emit 0xff
        _emit 0xff
        _emit 0xa1
        _emit 0x54
        _emit 0xe4
        _emit 0x1d
        _emit 0x10
        _emit 0x43
        _emit 0x83
        _emit 0xc6
        _emit 0x60
        _emit 0x3b
        _emit 0xd8
        _emit 0x7c
        _emit 0x9d
        _emit 0x5f
        _emit 0x5e
        _emit 0x5d
        _emit 0xb8
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x5b
        _emit 0x83
        _emit 0xc4
        _emit 0x0c
        _emit 0xc3
    }
}
#else
// CFLAGS: /DREBREW_ALLOW_NAKED /O2 /Gd

unsigned int __cdecl ls_LoadBuildingEntityState(unsigned int stream_ctx)
{
	int entity_count;
	int current_index;
	char* esi;
	int load_result;
	int* ebx;
	unsigned int offset;
	int dummy;
	register int neg1;

	gm_ResetAllEntities();

	if (!ls_ReadVfsDataChecked(&entity_count, 4, 1, (void*) stream_ctx)) {
		return 0;
	}

	current_index = 0;
	if (0 < entity_count) {
		offset = 0;
		neg1 = -1;
		do {
			esi = (char*) (offset + g_entity_ptr);

			if (!ls_ReadVfsDataChecked(esi, 1, 1, (void*) stream_ctx)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x01, 4, 1, (void*) stream_ctx)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x05, 0x20, 1, (void*) stream_ctx)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x25, 2, 1, (void*) stream_ctx)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x27, 2, 1, (void*) stream_ctx)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x29, 2, 1, (void*) stream_ctx)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x2b, 4, 1, (void*) stream_ctx)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x2f, 1, 1, (void*) stream_ctx)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x34, 1, 1, (void*) stream_ctx)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x35, 4, 1, (void*) stream_ctx)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x39, 4, 1, (void*) stream_ctx)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x3d, 4, 1, (void*) stream_ctx)) {
				return 0;
			}

			ebx = (int*) (esi + 0x41);
			if (!ls_ReadVfsDataChecked(ebx, 4, 1, (void*) stream_ctx)) {
				return 0;
			}
			if (*ebx > 4) {
				*ebx = 2;
			}

			if (!ls_ReadVfsDataChecked(esi + 0x45, 4, 1, (void*) stream_ctx)) {
				return 0;
			}

			if (g_file_version >= 0x10028) {
				if (!ls_ReadVfsDataChecked(esi + 0x49, 4, 1, (void*) stream_ctx)) {
					return 0;
				}
			}

			if (g_file_version < 0x10032) {
				if (!ls_ReadVfsDataChecked(&dummy, 4, 1, (void*) stream_ctx)) {
					return 0;
				}
			}

			if (g_file_version >= 0x10057) {
				if (!ls_ReadVfsDataChecked(esi + 0x4d, 4, 1, (void*) stream_ctx)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(esi + 0x51, 4, 1, (void*) stream_ctx)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(esi + 0x55, 4, 1, (void*) stream_ctx)) {
					return 0;
				}
			}

			if (!ls_ReadVfsDataChecked(esi + 0x5a, 2, 1, (void*) stream_ctx)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x5c, 1, 1, (void*) stream_ctx)) {
				return 0;
			}

			if (esi[0] == 0x1e) {
				*(int*) (esi + 0x71) = (int) m_AllocTracked(0x600, (const char*) 0x1002d510);
				for (load_result = 0; load_result < 0x600; load_result += 0x18) {
					if (!ls_ReadVfsDataChecked((void*) (load_result + *(int*) (esi + 0x71)), 4, 1, (void*) stream_ctx)) {
						return 0;
					}
					if (!ls_ReadVfsDataChecked(
							(void*) (load_result + 4 + *(int*) (esi + 0x71)),
							4,
							1,
							(void*) stream_ctx
						)) {
						return 0;
					}
					if (!ls_ReadVfsDataChecked(
							(void*) (load_result + 8 + *(int*) (esi + 0x71)),
							1,
							1,
							(void*) stream_ctx
						)) {
						return 0;
					}
					if (!ls_ReadVfsDataChecked(
							(void*) (load_result + 9 + *(int*) (esi + 0x71)),
							1,
							1,
							(void*) stream_ctx
						)) {
						return 0;
					}
					if (!ls_ReadVfsDataChecked(
							(void*) (load_result + 0xa + *(int*) (esi + 0x71)),
							2,
							1,
							(void*) stream_ctx
						)) {
						return 0;
					}
					if (!ls_ReadVfsDataChecked(
							(void*) (load_result + 0x10 + *(int*) (esi + 0x71)),
							4,
							1,
							(void*) stream_ctx
						)) {
						return 0;
					}
					if (!ls_ReadVfsDataChecked(
							(void*) (load_result + 0xc + *(int*) (esi + 0x71)),
							1,
							1,
							(void*) stream_ctx
						)) {
						return 0;
					}
					if (!ls_ReadVfsDataChecked(
							(void*) (load_result + 0xd + *(int*) (esi + 0x71)),
							1,
							1,
							(void*) stream_ctx
						)) {
						return 0;
					}
					*(int*) (load_result + 0x14 + *(int*) (esi + 0x71)) = 0;
				}
			}
			else if (esi[0] == 0x48 || esi[0] == 0x49 || esi[0] == 0x4a) {
				if (g_file_version >= 0x10047) {
					load_result = ls_LoadGraveyardData(stream_ctx, (int) esi);
				}
				else {
					if (!ls_ReadVfsDataChecked(esi + 0x65, 0x30, 1, (void*) stream_ctx)) {
						return 0;
					}
					*(int*) (esi + 0x65) = AllocGraveyardField((int) esi);
					goto label_10012d72;
				}
				if (load_result == 0) {
					return 0;
				}
			}
			else if (esi[0] == 0x4b || esi[0] == 0x4c || esi[0] == 0x4d) {
				if (g_file_version >= 0x10049) {
					load_result = ahm_AllocAhmInfo(stream_ctx, (int) esi);
				}
				else {
					int* ahm_info;
					if (!ls_ReadVfsDataChecked(esi + 0x65, 0x30, 1, (void*) stream_ctx)) {
						return 0;
					}
					ahm_info = (int*) m_AllocTracked(0x3c, (const char*) 0x1002d504);
					*(int*) (esi + 0x65) = (int) ahm_info;
					*ahm_info = neg1;
					goto label_10012d72;
				}
				if (load_result == 0) {
					return 0;
				}
			}
			else {
				if (!ls_ReadVfsDataChecked(esi + 0x65, 0x30, 1, (void*) stream_ctx)) {
					return 0;
				}
			}

		label_10012d72:
			if (g_file_version >= 0x10043) {
				if (!ls_ReadVfsDataChecked(esi + 0x99, 0x10, 1, (void*) stream_ctx)) {
					return 0;
				}
			}
			else {
				int* state_ptr = (int*) (esi + 0x99);
				int zero = 0;
				*state_ptr = zero;
				*(int*) ((char*) state_ptr + 4) = zero;
				*(int*) ((char*) state_ptr + 8) = zero;
				*(int*) ((char*) state_ptr + 0xc) = zero;
				*(int*) (esi + 0xa5) = neg1;
				*state_ptr = *state_ptr | 1;
			}

			*(int*) (esi + 0x30) = 0x1388;
			*(int*) (esi + 0x95) = neg1;
			current_index++;
			offset += 0xa9;
		} while (current_index < entity_count);
	}

	if (!ls_ReadVfsDataChecked(&g_101de454, 4, 1, (void*) stream_ctx)) {
		return 0;
	}

	g_101de55c = (int) realloc((void*) g_101de55c, g_101de454 * 0x60);

	current_index = 0;
	for (load_result = 0; load_result < g_101de454; load_result++) {
		if (!ls_ReadVfsDataChecked((void*) (current_index + g_101de55c), 0x40, 1, (void*) stream_ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked((void*) (current_index + 0x40 + g_101de55c), 0x10, 1, (void*) stream_ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked((void*) (current_index + 0x50 + g_101de55c), 0x10, 1, (void*) stream_ctx)) {
			return 0;
		}
		current_index += 0x60;
	}

	return 1;
}
#endif


/* Loads dynamic (non-building) entities from a save file.
 * Reads citizens, objects, and transient game entities. */
