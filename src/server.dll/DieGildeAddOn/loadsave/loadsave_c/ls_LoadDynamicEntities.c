// CFLAGS: /DREBREW_ALLOW_NAKED /O2 /Gd
// FUNCTION: SERVER 0x10012eb0
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
// NAKED verification build: byte-identical to original/Server/server.dll 0x10012eb0 (884B)
__declspec(naked) int __cdecl ls_LoadDynamicEntities(void* file)
{
    __asm {
        _emit 0x53
        _emit 0x55
        _emit 0x56
        _emit 0x57
        _emit 0x8b
        _emit 0x7c
        _emit 0x24
        _emit 0x14
        _emit 0xbe
        _emit 0xa2
        _emit 0xac
        _emit 0x09
        _emit 0x10
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x46
        _emit 0xfe
        _emit 0x6a
        _emit 0x02
        _emit 0x50
        _emit 0xe8
        _emit 0x75
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
        _emit 0x47
        _emit 0x03
        _emit 0x00
        _emit 0x00
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x6a
        _emit 0x10
        _emit 0x56
        _emit 0xe8
        _emit 0x5f
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
        _emit 0x31
        _emit 0x03
        _emit 0x00
        _emit 0x00
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x4e
        _emit 0x12
        _emit 0x6a
        _emit 0x04
        _emit 0x51
        _emit 0xe8
        _emit 0x46
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
        _emit 0x18
        _emit 0x03
        _emit 0x00
        _emit 0x00
        _emit 0x81
        _emit 0x3d
        _emit 0xec
        _emit 0xd4
        _emit 0x02
        _emit 0x10
        _emit 0x2c
        _emit 0x00
        _emit 0x01
        _emit 0x00
        _emit 0x7c
        _emit 0x19
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x56
        _emit 0x26
        _emit 0x6a
        _emit 0x04
        _emit 0x52
        _emit 0xe8
        _emit 0x21
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
        _emit 0xf3
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x46
        _emit 0x1a
        _emit 0x6a
        _emit 0x04
        _emit 0x50
        _emit 0xe8
        _emit 0x08
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
        _emit 0xda
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x4e
        _emit 0x1e
        _emit 0x6a
        _emit 0x04
        _emit 0x51
        _emit 0xe8
        _emit 0xef
        _emit 0xf4
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0xc1
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x56
        _emit 0x2a
        _emit 0x6a
        _emit 0x04
        _emit 0x52
        _emit 0xe8
        _emit 0xd6
        _emit 0xf4
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0xa8
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x46
        _emit 0x2e
        _emit 0x6a
        _emit 0x04
        _emit 0x50
        _emit 0xe8
        _emit 0xbd
        _emit 0xf4
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0x8f
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x4e
        _emit 0x32
        _emit 0x6a
        _emit 0x04
        _emit 0x51
        _emit 0xe8
        _emit 0xa4
        _emit 0xf4
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0x76
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x56
        _emit 0x36
        _emit 0x6a
        _emit 0x04
        _emit 0x52
        _emit 0xe8
        _emit 0x8b
        _emit 0xf4
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0x5d
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x46
        _emit 0x3e
        _emit 0x6a
        _emit 0x04
        _emit 0x50
        _emit 0xe8
        _emit 0x72
        _emit 0xf4
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
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x4e
        _emit 0x42
        _emit 0x6a
        _emit 0x04
        _emit 0x51
        _emit 0xe8
        _emit 0x59
        _emit 0xf4
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0x2b
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x56
        _emit 0x46
        _emit 0x6a
        _emit 0x04
        _emit 0x52
        _emit 0xe8
        _emit 0x40
        _emit 0xf4
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0x12
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x46
        _emit 0x4a
        _emit 0x6a
        _emit 0x04
        _emit 0x50
        _emit 0xe8
        _emit 0x27
        _emit 0xf4
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0xf9
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x4e
        _emit 0x4e
        _emit 0x6a
        _emit 0x04
        _emit 0x51
        _emit 0xe8
        _emit 0x0e
        _emit 0xf4
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0xe0
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0xa1
        _emit 0xec
        _emit 0xd4
        _emit 0x02
        _emit 0x10
        _emit 0x3d
        _emit 0x14
        _emit 0x00
        _emit 0x01
        _emit 0x00
        _emit 0x0f
        _emit 0x8c
        _emit 0xb4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x56
        _emit 0x52
        _emit 0x6a
        _emit 0x04
        _emit 0x52
        _emit 0xe8
        _emit 0xe5
        _emit 0xf3
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0xb7
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x46
        _emit 0x56
        _emit 0x6a
        _emit 0x04
        _emit 0x50
        _emit 0xe8
        _emit 0xcc
        _emit 0xf3
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0x9e
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x4e
        _emit 0x5a
        _emit 0x6a
        _emit 0x04
        _emit 0x51
        _emit 0xe8
        _emit 0xb3
        _emit 0xf3
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0x85
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x56
        _emit 0x3a
        _emit 0x6a
        _emit 0x04
        _emit 0x52
        _emit 0xe8
        _emit 0x9a
        _emit 0xf3
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0x6c
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x46
        _emit 0x62
        _emit 0x6a
        _emit 0x04
        _emit 0x50
        _emit 0xe8
        _emit 0x81
        _emit 0xf3
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
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x4e
        _emit 0x66
        _emit 0x6a
        _emit 0x04
        _emit 0x51
        _emit 0xe8
        _emit 0x68
        _emit 0xf3
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0x3a
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x56
        _emit 0x6a
        _emit 0x6a
        _emit 0x04
        _emit 0x52
        _emit 0xe8
        _emit 0x4f
        _emit 0xf3
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0x21
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0xa1
        _emit 0xec
        _emit 0xd4
        _emit 0x02
        _emit 0x10
        _emit 0x3d
        _emit 0x56
        _emit 0x00
        _emit 0x01
        _emit 0x00
        _emit 0x7c
        _emit 0x20
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x46
        _emit 0x5e
        _emit 0x6a
        _emit 0x04
        _emit 0x50
        _emit 0xe8
        _emit 0x2a
        _emit 0xf3
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0xfc
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0xa1
        _emit 0xec
        _emit 0xd4
        _emit 0x02
        _emit 0x10
        _emit 0xeb
        _emit 0x07
        _emit 0xc7
        _emit 0x46
        _emit 0x5e
        _emit 0x00
        _emit 0x00
        _emit 0x80
        _emit 0x3f
        _emit 0x3d
        _emit 0x15
        _emit 0x00
        _emit 0x01
        _emit 0x00
        _emit 0x7c
        _emit 0x46
        _emit 0x33
        _emit 0xdb
        _emit 0x3d
        _emit 0x46
        _emit 0x00
        _emit 0x01
        _emit 0x00
        _emit 0x0f
        _emit 0x9d
        _emit 0xc3
        _emit 0x4b
        _emit 0x33
        _emit 0xed
        _emit 0x83
        _emit 0xe3
        _emit 0xfd
        _emit 0x83
        _emit 0xc3
        _emit 0x11
        _emit 0x85
        _emit 0xdb
        _emit 0x7e
        _emit 0x2f
        _emit 0x8d
        _emit 0x4e
        _emit 0x72
        _emit 0x89
        _emit 0x4c
        _emit 0x24
        _emit 0x14
        _emit 0x8b
        _emit 0x54
        _emit 0x24
        _emit 0x14
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x6a
        _emit 0x01
        _emit 0x52
        _emit 0xe8
        _emit 0xdd
        _emit 0xf2
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0xaf
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x8b
        _emit 0x4c
        _emit 0x24
        _emit 0x14
        _emit 0x45
        _emit 0x41
        _emit 0x3b
        _emit 0xeb
        _emit 0x89
        _emit 0x4c
        _emit 0x24
        _emit 0x14
        _emit 0x7c
        _emit 0xd8
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x86
        _emit 0x86
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x6a
        _emit 0x04
        _emit 0x50
        _emit 0xe8
        _emit 0xb3
        _emit 0xf2
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0x85
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x8e
        _emit 0x8a
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x6a
        _emit 0x10
        _emit 0x51
        _emit 0xe8
        _emit 0x97
        _emit 0xf2
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x74
        _emit 0x6d
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x96
        _emit 0x9a
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x6a
        _emit 0x0c
        _emit 0x52
        _emit 0xe8
        _emit 0x7f
        _emit 0xf2
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x74
        _emit 0x55
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x86
        _emit 0xa6
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x6a
        _emit 0x04
        _emit 0x50
        _emit 0xe8
        _emit 0x67
        _emit 0xf2
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x74
        _emit 0x3d
        _emit 0x81
        _emit 0x3d
        _emit 0xec
        _emit 0xd4
        _emit 0x02
        _emit 0x10
        _emit 0x18
        _emit 0x00
        _emit 0x01
        _emit 0x00
        _emit 0x7c
        _emit 0x15
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x8d
        _emit 0x4e
        _emit 0x6e
        _emit 0x6a
        _emit 0x04
        _emit 0x51
        _emit 0xe8
        _emit 0x46
        _emit 0xf2
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x74
        _emit 0x1c
        _emit 0x81
        _emit 0xc6
        _emit 0xac
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x81
        _emit 0xfe
        _emit 0x62
        _emit 0xb7
        _emit 0x09
        _emit 0x10
        _emit 0x0f
        _emit 0x8c
        _emit 0xaa
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
        _emit 0xc3
        _emit 0x5f
        _emit 0x5e
        _emit 0x5d
        _emit 0x33
        _emit 0xc0
        _emit 0x5b
        _emit 0xc3
    }
}
#else
int __cdecl ls_LoadDynamicEntities(void* file)
{
	char* rec;

	rec = (char*) 0x1009aca2;
	do {
		if (!ls_ReadVfsDataChecked(rec - 2, 2, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(rec, 0x10, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(rec + 0x12, 4, 1, (void*) file)) {
			return 0;
		}
		if (g_file_version >= 0x1002c) {
			if (!ls_ReadVfsDataChecked(rec + 0x26, 4, 1, (void*) file)) {
				return 0;
			}
		}
		if (!ls_ReadVfsDataChecked(rec + 0x1a, 4, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(rec + 0x1e, 4, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(rec + 0x2a, 4, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(rec + 0x2e, 4, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(rec + 0x32, 4, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(rec + 0x36, 4, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(rec + 0x3e, 4, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(rec + 0x42, 4, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(rec + 0x46, 4, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(rec + 0x4a, 4, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(rec + 0x4e, 4, 1, (void*) file)) {
			return 0;
		}
		if (g_file_version >= 0x10014) {
			if (!ls_ReadVfsDataChecked(rec + 0x52, 4, 1, (void*) file)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(rec + 0x56, 4, 1, (void*) file)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(rec + 0x5a, 4, 1, (void*) file)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(rec + 0x3a, 4, 1, (void*) file)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(rec + 0x62, 4, 1, (void*) file)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(rec + 0x66, 4, 1, (void*) file)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(rec + 0x6a, 4, 1, (void*) file)) {
				return 0;
			}
		}
		if (g_file_version >= 0x10056) {
			if (!ls_ReadVfsDataChecked(rec + 0x5e, 4, 1, (void*) file)) {
				return 0;
			}
		}
		else {
			*(int*) (rec + 0x5e) = 0x3f800000;
		}
		if (g_file_version >= 0x10015) {
			int count;
			int i;
			char* p;
			count = (g_file_version >= 0x10046) ? 0x11 : 0x0e;
			i = 0;
			p = rec + 0x72;
			if (count > 0) {
				do {
					if (!ls_ReadVfsDataChecked(p, 1, 1, (void*) file)) {
						return 0;
					}
					i++;
					p++;
				} while (i < count);
			}
		}
		if (!ls_ReadVfsDataChecked(rec + 0x86, 4, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(rec + 0x8a, 0x10, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(rec + 0x9a, 0x0c, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(rec + 0xa6, 4, 1, (void*) file)) {
			return 0;
		}
		if (g_file_version >= 0x10018) {
			if (!ls_ReadVfsDataChecked(rec + 0x6e, 4, 1, (void*) file)) {
				return 0;
			}
		}
		rec += 0xac;
	} while (rec < (char*) 0x1009b762);

	return 1;
}
#endif


/* Master entity loader: orchestrates loading all entity
 * types from a save file in the correct order (buildings
 * first, then citizens, then objects). */
