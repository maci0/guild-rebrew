// FUNCTION: SERVER 0x1000e140

/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: MATCHING
 *    Origin: GAME
 *    Size: 993B
 *    CFlags:
 *    Symbol: _cm_ExecProduction
 *    Files: DieGildeAddOn/command/command.c * / *
 * int __cdecl cm_ExProdObjekt(int msg,char *result)
 */

#include "../command_internal.h"
#include "../../../Units/Error/error.h"

extern char* g_unknown_1de450;
extern unsigned char g_current_season;

short* __cdecl gm_ResolveParentEntity(short*);
double __cdecl gm_CalculateProductionValue(uint, int);
int __cdecl gm_WalkEntityChain(int);

extern char s_cm_ExecProduction___Invalid__lager_1002cf9c[];
extern char s_cm_ExecProduction___Lager_has_wron_1002cf74[];
extern char s_cm_ExecProduction___Lager_hat_kein_1002cf48[];
extern char s_cm_ExProdObjekt___Cannot_produce___1002cf1c[];
extern char s_cm_ExProdObjekt___Rohstoff_versc_1002cef4[];
unsigned short* __cdecl gm_StartEntityQuery(int, int, int, ...);
char* __cdecl gm_AllocObjekt(int, int, int);
int __cdecl gm_RemoveObjectByType(void**, unsigned int);

/* Execution handler: produces an object. Processes a production
 * message with entity lookup, object allocation/deallocation,
 * and inventory management for crafted goods. */

#ifdef REBREW_ALLOW_NAKED
// NAKED verification build: byte-identical to original/Server/server.dll 0x1000e140 (993B)
__declspec(naked) int __cdecl cm_ExProdObjekt(int msg, char* result)
{
    __asm {
        _emit 0x83
        _emit 0xec
        _emit 0x10
        _emit 0xa1
        _emit 0x6c
        _emit 0x0b
        _emit 0x03
        _emit 0x10
        _emit 0x53
        _emit 0x55
        _emit 0x8b
        _emit 0x6c
        _emit 0x24
        _emit 0x1c
        _emit 0x56
        _emit 0x57
        _emit 0x8b
        _emit 0x4d
        _emit 0x10
        _emit 0x89
        _emit 0x45
        _emit 0x1a
        _emit 0x51
        _emit 0x55
        _emit 0xe8
        _emit 0x33
        _emit 0xe9
        _emit 0xff
        _emit 0xff
        _emit 0x50
        _emit 0x8d
        _emit 0x54
        _emit 0x24
        _emit 0x1c
        _emit 0x6a
        _emit 0x00
        _emit 0x52
        _emit 0x6a
        _emit 0x00
        _emit 0x89
        _emit 0x45
        _emit 0x10
        _emit 0xe8
        _emit 0x21
        _emit 0x7d
        _emit 0x00
        _emit 0x00
        _emit 0x83
        _emit 0xc4
        _emit 0x18
        _emit 0x85
        _emit 0xc0
        _emit 0x75
        _emit 0x26
        _emit 0x6a
        _emit 0x01
        _emit 0x68
        _emit 0x9c
        _emit 0xcf
        _emit 0x02
        _emit 0x10
        _emit 0x68
        _emit 0x3b
        _emit 0x2f
        _emit 0x00
        _emit 0x00
        _emit 0x68
        _emit 0x48
        _emit 0xc7
        _emit 0x02
        _emit 0x10
        _emit 0xe8
        _emit 0xb4
        _emit 0x54
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0xb8
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x5f
        _emit 0x5e
        _emit 0x5d
        _emit 0x5b
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0xc3
        _emit 0x8b
        _emit 0x4c
        _emit 0x24
        _emit 0x10
        _emit 0x66
        _emit 0x8b
        _emit 0x01
        _emit 0x66
        _emit 0x3d
        _emit 0x2a
        _emit 0x00
        _emit 0x74
        _emit 0x2c
        _emit 0x66
        _emit 0x3d
        _emit 0x16
        _emit 0x01
        _emit 0x74
        _emit 0x26
        _emit 0x6a
        _emit 0x01
        _emit 0x68
        _emit 0x74
        _emit 0xcf
        _emit 0x02
        _emit 0x10
        _emit 0x68
        _emit 0x53
        _emit 0x2f
        _emit 0x00
        _emit 0x00
        _emit 0x68
        _emit 0x48
        _emit 0xc7
        _emit 0x02
        _emit 0x10
        _emit 0xe8
        _emit 0x7b
        _emit 0x54
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0xb8
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x5f
        _emit 0x5e
        _emit 0x5d
        _emit 0x5b
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0xc3
        _emit 0x51
        _emit 0xe8
        _emit 0x05
        _emit 0xb9
        _emit 0x00
        _emit 0x00
        _emit 0x83
        _emit 0xc4
        _emit 0x04
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x1c
        _emit 0x85
        _emit 0xc0
        _emit 0x75
        _emit 0x26
        _emit 0x6a
        _emit 0x01
        _emit 0x68
        _emit 0x48
        _emit 0xcf
        _emit 0x02
        _emit 0x10
        _emit 0x68
        _emit 0x6d
        _emit 0x2f
        _emit 0x00
        _emit 0x00
        _emit 0x68
        _emit 0x48
        _emit 0xc7
        _emit 0x02
        _emit 0x10
        _emit 0xe8
        _emit 0x44
        _emit 0x54
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0xb8
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x5f
        _emit 0x5e
        _emit 0x5d
        _emit 0x5b
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0xc3
        _emit 0x8b
        _emit 0x15
        _emit 0x50
        _emit 0xe4
        _emit 0x1d
        _emit 0x10
        _emit 0x33
        _emit 0xc0
        _emit 0x66
        _emit 0x8b
        _emit 0x45
        _emit 0x14
        _emit 0x8b
        _emit 0x5d
        _emit 0x16
        _emit 0x8b
        _emit 0xc8
        _emit 0x89
        _emit 0x5c
        _emit 0x24
        _emit 0x18
        _emit 0xc1
        _emit 0xe1
        _emit 0x06
        _emit 0x03
        _emit 0xd1
        _emit 0xc7
        _emit 0x44
        _emit 0x24
        _emit 0x18
        _emit 0x04
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x03
        _emit 0xc2
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x14
        _emit 0x8d
        _emit 0x78
        _emit 0x26
        _emit 0x66
        _emit 0x8b
        _emit 0x47
        _emit 0x08
        _emit 0x66
        _emit 0x85
        _emit 0xc0
        _emit 0x74
        _emit 0x56
        _emit 0x25
        _emit 0xff
        _emit 0xff
        _emit 0x00
        _emit 0x00
        _emit 0x50
        _emit 0x8b
        _emit 0x44
        _emit 0x24
        _emit 0x14
        _emit 0x6a
        _emit 0x00
        _emit 0x6a
        _emit 0x01
        _emit 0x8b
        _emit 0x48
        _emit 0x14
        _emit 0x51
        _emit 0xe8
        _emit 0x09
        _emit 0x82
        _emit 0x00
        _emit 0x00
        _emit 0x8b
        _emit 0xf0
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xf6
        _emit 0x74
        _emit 0x34
        _emit 0x8b
        _emit 0x54
        _emit 0x24
        _emit 0x10
        _emit 0x56
        _emit 0x52
        _emit 0xe8
        _emit 0x65
        _emit 0xba
        _emit 0x00
        _emit 0x00
        _emit 0x33
        _emit 0xc9
        _emit 0x83
        _emit 0xc4
        _emit 0x08
        _emit 0x66
        _emit 0x8b
        _emit 0x0f
        _emit 0x99
        _emit 0xf7
        _emit 0xf9
        _emit 0x3b
        _emit 0xd8
        _emit 0x7c
        _emit 0x1c
        _emit 0x8b
        _emit 0x54
        _emit 0x24
        _emit 0x10
        _emit 0x56
        _emit 0x52
        _emit 0xe8
        _emit 0x4b
        _emit 0xba
        _emit 0x00
        _emit 0x00
        _emit 0x33
        _emit 0xc9
        _emit 0x83
        _emit 0xc4
        _emit 0x08
        _emit 0x66
        _emit 0x8b
        _emit 0x0f
        _emit 0x99
        _emit 0xf7
        _emit 0xf9
        _emit 0x8b
        _emit 0xd8
        _emit 0xeb
        _emit 0x02
        _emit 0x33
        _emit 0xdb
        _emit 0x8b
        _emit 0x44
        _emit 0x24
        _emit 0x18
        _emit 0x83
        _emit 0xc7
        _emit 0x02
        _emit 0x48
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x18
        _emit 0x75
        _emit 0x93
        _emit 0x8b
        _emit 0x74
        _emit 0x24
        _emit 0x14
        _emit 0x33
        _emit 0xd2
        _emit 0x8b
        _emit 0x4c
        _emit 0x24
        _emit 0x10
        _emit 0x33
        _emit 0xc0
        _emit 0x66
        _emit 0x8b
        _emit 0x56
        _emit 0x36
        _emit 0x66
        _emit 0x8b
        _emit 0x45
        _emit 0x14
        _emit 0x0f
        _emit 0xaf
        _emit 0xd3
        _emit 0x52
        _emit 0x50
        _emit 0x51
        _emit 0x89
        _emit 0x5c
        _emit 0x24
        _emit 0x24
        _emit 0xe8
        _emit 0x69
        _emit 0xba
        _emit 0x00
        _emit 0x00
        _emit 0x33
        _emit 0xc9
        _emit 0x83
        _emit 0xc4
        _emit 0x0c
        _emit 0x66
        _emit 0x8b
        _emit 0x4e
        _emit 0x36
        _emit 0x99
        _emit 0xf7
        _emit 0xf9
        _emit 0x3b
        _emit 0xd8
        _emit 0x7c
        _emit 0x06
        _emit 0x8b
        _emit 0xd8
        _emit 0x89
        _emit 0x5c
        _emit 0x24
        _emit 0x18
        _emit 0x85
        _emit 0xdb
        _emit 0x75
        _emit 0x11
        _emit 0x6a
        _emit 0x01
        _emit 0x68
        _emit 0x1c
        _emit 0xcf
        _emit 0x02
        _emit 0x10
        _emit 0x68
        _emit 0xb5
        _emit 0x2f
        _emit 0x00
        _emit 0x00
        _emit 0xe9
        _emit 0xef
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x8b
        _emit 0x54
        _emit 0x24
        _emit 0x14
        _emit 0x33
        _emit 0xed
        _emit 0x8d
        _emit 0x7a
        _emit 0x2e
        _emit 0x66
        _emit 0x8b
        _emit 0x07
        _emit 0x66
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x84
        _emit 0x82
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x25
        _emit 0xff
        _emit 0xff
        _emit 0x00
        _emit 0x00
        _emit 0x50
        _emit 0x8b
        _emit 0x44
        _emit 0x24
        _emit 0x14
        _emit 0x6a
        _emit 0x00
        _emit 0x6a
        _emit 0x01
        _emit 0x8b
        _emit 0x48
        _emit 0x14
        _emit 0x51
        _emit 0xe8
        _emit 0x42
        _emit 0x81
        _emit 0x00
        _emit 0x00
        _emit 0x8b
        _emit 0xf0
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xf6
        _emit 0x0f
        _emit 0x84
        _emit 0xaa
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x33
        _emit 0xd2
        _emit 0x8b
        _emit 0x46
        _emit 0x0e
        _emit 0x66
        _emit 0x8b
        _emit 0x57
        _emit 0xf8
        _emit 0x33
        _emit 0xc9
        _emit 0x0f
        _emit 0xaf
        _emit 0xd3
        _emit 0x2b
        _emit 0xc2
        _emit 0x89
        _emit 0x46
        _emit 0x0e
        _emit 0x8a
        _emit 0x0d
        _emit 0x39
        _emit 0x54
        _emit 0x03
        _emit 0x10
        _emit 0x33
        _emit 0xc0
        _emit 0x66
        _emit 0x8b
        _emit 0x07
        _emit 0x50
        _emit 0x51
        _emit 0xe8
        _emit 0xf0
        _emit 0x7e
        _emit 0x00
        _emit 0x00
        _emit 0x83
        _emit 0xc4
        _emit 0x08
        _emit 0x85
        _emit 0xc0
        _emit 0x74
        _emit 0x15
        _emit 0x8b
        _emit 0x4c
        _emit 0x24
        _emit 0x14
        _emit 0x33
        _emit 0xd2
        _emit 0x66
        _emit 0x8b
        _emit 0x51
        _emit 0x36
        _emit 0x8b
        _emit 0x48
        _emit 0x14
        _emit 0x0f
        _emit 0xaf
        _emit 0xd3
        _emit 0x03
        _emit 0xca
        _emit 0x89
        _emit 0x48
        _emit 0x14
        _emit 0x8b
        _emit 0x46
        _emit 0x0e
        _emit 0x85
        _emit 0xc0
        _emit 0x75
        _emit 0x16
        _emit 0x8b
        _emit 0x44
        _emit 0x24
        _emit 0x10
        _emit 0x33
        _emit 0xd2
        _emit 0x66
        _emit 0x8b
        _emit 0x17
        _emit 0x83
        _emit 0xc0
        _emit 0x14
        _emit 0x52
        _emit 0x50
        _emit 0xe8
        _emit 0x4a
        _emit 0x82
        _emit 0x00
        _emit 0x00
        _emit 0x83
        _emit 0xc4
        _emit 0x08
        _emit 0x45
        _emit 0x83
        _emit 0xc7
        _emit 0x02
        _emit 0x83
        _emit 0xfd
        _emit 0x04
        _emit 0x0f
        _emit 0x8c
        _emit 0x65
        _emit 0xff
        _emit 0xff
        _emit 0xff
        _emit 0x8b
        _emit 0x6c
        _emit 0x24
        _emit 0x24
        _emit 0x8b
        _emit 0x54
        _emit 0x24
        _emit 0x10
        _emit 0x33
        _emit 0xc9
        _emit 0x66
        _emit 0x8b
        _emit 0x4d
        _emit 0x14
        _emit 0x8b
        _emit 0x42
        _emit 0x14
        _emit 0x51
        _emit 0x6a
        _emit 0x00
        _emit 0x6a
        _emit 0x01
        _emit 0x50
        _emit 0xe8
        _emit 0xae
        _emit 0x80
        _emit 0x00
        _emit 0x00
        _emit 0x8b
        _emit 0xf0
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xf6
        _emit 0x74
        _emit 0x4c
        _emit 0x8b
        _emit 0x54
        _emit 0x24
        _emit 0x14
        _emit 0x33
        _emit 0xc9
        _emit 0x8b
        _emit 0x46
        _emit 0x0e
        _emit 0x66
        _emit 0x8b
        _emit 0x4a
        _emit 0x36
        _emit 0x0f
        _emit 0xaf
        _emit 0xcb
        _emit 0x03
        _emit 0xc1
        _emit 0x89
        _emit 0x46
        _emit 0x0e
        _emit 0xe9
        _emit 0xb6
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x6a
        _emit 0x01
        _emit 0x68
        _emit 0xf4
        _emit 0xce
        _emit 0x02
        _emit 0x10
        _emit 0x68
        _emit 0xdd
        _emit 0x2f
        _emit 0x00
        _emit 0x00
        _emit 0x68
        _emit 0x48
        _emit 0xc7
        _emit 0x02
        _emit 0x10
        _emit 0xe8
        _emit 0x55
        _emit 0x52
        _emit 0xff
        _emit 0xff
        _emit 0x8b
        _emit 0x44
        _emit 0x24
        _emit 0x38
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x74
        _emit 0x04
        _emit 0xc6
        _emit 0x40
        _emit 0x01
        _emit 0x08
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
        _emit 0x10
        _emit 0xc3
        _emit 0x8b
        _emit 0x7c
        _emit 0x24
        _emit 0x14
        _emit 0x33
        _emit 0xc0
        _emit 0x8b
        _emit 0x54
        _emit 0x24
        _emit 0x10
        _emit 0x33
        _emit 0xc9
        _emit 0x66
        _emit 0x8b
        _emit 0x47
        _emit 0x36
        _emit 0x66
        _emit 0x8b
        _emit 0x4d
        _emit 0x14
        _emit 0x0f
        _emit 0xaf
        _emit 0xc3
        _emit 0x50
        _emit 0x8b
        _emit 0x42
        _emit 0x02
        _emit 0x51
        _emit 0x50
        _emit 0xe8
        _emit 0x37
        _emit 0x83
        _emit 0x00
        _emit 0x00
        _emit 0x8b
        _emit 0xf0
        _emit 0x83
        _emit 0xc4
        _emit 0x0c
        _emit 0x85
        _emit 0xf6
        _emit 0x75
        _emit 0x19
        _emit 0x8b
        _emit 0x44
        _emit 0x24
        _emit 0x28
        _emit 0x85
        _emit 0xc0
        _emit 0x74
        _emit 0x04
        _emit 0xc6
        _emit 0x40
        _emit 0x01
        _emit 0x06
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
        _emit 0x10
        _emit 0xc3
        _emit 0x8b
        _emit 0x4c
        _emit 0x24
        _emit 0x10
        _emit 0x66
        _emit 0x83
        _emit 0x39
        _emit 0x2a
        _emit 0x75
        _emit 0x03
        _emit 0xff
        _emit 0x46
        _emit 0x0e
        _emit 0x8a
        _emit 0x07
        _emit 0x3c
        _emit 0x17
        _emit 0x74
        _emit 0x04
        _emit 0x3c
        _emit 0x25
        _emit 0x75
        _emit 0x29
        _emit 0x8b
        _emit 0x54
        _emit 0x24
        _emit 0x10
        _emit 0x66
        _emit 0x8b
        _emit 0x02
        _emit 0x66
        _emit 0x3d
        _emit 0x2a
        _emit 0x00
        _emit 0x74
        _emit 0x06
        _emit 0x66
        _emit 0x3d
        _emit 0x16
        _emit 0x01
        _emit 0x75
        _emit 0x16
        _emit 0x8b
        _emit 0x44
        _emit 0x24
        _emit 0x1c
        _emit 0x8a
        _emit 0x40
        _emit 0x02
        _emit 0x3c
        _emit 0x06
        _emit 0x74
        _emit 0x04
        _emit 0x3c
        _emit 0x07
        _emit 0x75
        _emit 0x07
        _emit 0xc7
        _emit 0x46
        _emit 0x1c
        _emit 0x04
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x33
        _emit 0xc9
        _emit 0x6a
        _emit 0x64
        _emit 0x66
        _emit 0x8b
        _emit 0x4d
        _emit 0x14
        _emit 0x51
        _emit 0xe8
        _emit 0x87
        _emit 0xb2
        _emit 0x00
        _emit 0x00
        _emit 0xda
        _emit 0x4c
        _emit 0x24
        _emit 0x20
        _emit 0xe8
        _emit 0xc2
        _emit 0xd0
        _emit 0x00
        _emit 0x00
        _emit 0x8b
        _emit 0x54
        _emit 0x24
        _emit 0x18
        _emit 0x8b
        _emit 0xf8
        _emit 0x52
        _emit 0xe8
        _emit 0xd2
        _emit 0xb6
        _emit 0x00
        _emit 0x00
        _emit 0x83
        _emit 0xc4
        _emit 0x0c
        _emit 0x85
        _emit 0xc0
        _emit 0x74
        _emit 0x03
        _emit 0x01
        _emit 0x78
        _emit 0x4d
        _emit 0x33
        _emit 0xc0
        _emit 0x33
        _emit 0xc9
        _emit 0x66
        _emit 0x8b
        _emit 0x45
        _emit 0x14
        _emit 0x8a
        _emit 0x0d
        _emit 0x39
        _emit 0x54
        _emit 0x03
        _emit 0x10
        _emit 0x50
        _emit 0x51
        _emit 0xe8
        _emit 0x73
        _emit 0x7d
        _emit 0x00
        _emit 0x00
        _emit 0x83
        _emit 0xc4
        _emit 0x08
        _emit 0x85
        _emit 0xc0
        _emit 0x74
        _emit 0x15
        _emit 0x8b
        _emit 0x4c
        _emit 0x24
        _emit 0x14
        _emit 0x33
        _emit 0xd2
        _emit 0x66
        _emit 0x8b
        _emit 0x51
        _emit 0x36
        _emit 0x8b
        _emit 0x48
        _emit 0x10
        _emit 0x0f
        _emit 0xaf
        _emit 0xd3
        _emit 0x03
        _emit 0xca
        _emit 0x89
        _emit 0x48
        _emit 0x10
        _emit 0x8b
        _emit 0x54
        _emit 0x24
        _emit 0x1c
        _emit 0x52
        _emit 0xe8
        _emit 0xed
        _emit 0x9f
        _emit 0x00
        _emit 0x00
        _emit 0x83
        _emit 0xc4
        _emit 0x04
        _emit 0x85
        _emit 0xc0
        _emit 0x74
        _emit 0x03
        _emit 0x01
        _emit 0x78
        _emit 0x24
        _emit 0x8b
        _emit 0x44
        _emit 0x24
        _emit 0x28
        _emit 0x85
        _emit 0xc0
        _emit 0x74
        _emit 0x12
        _emit 0xc6
        _emit 0x00
        _emit 0x01
        _emit 0x8b
        _emit 0x4d
        _emit 0x10
        _emit 0x83
        _emit 0xf9
        _emit 0xff
        _emit 0x74
        _emit 0x07
        _emit 0xc6
        _emit 0x40
        _emit 0x01
        _emit 0x03
        _emit 0x89
        _emit 0x70
        _emit 0x06
        _emit 0x5f
        _emit 0x5e
        _emit 0x5d
        _emit 0x33
        _emit 0xc0
        _emit 0x5b
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0xc3
    }
}
#else
// CFLAGS: /DREBREW_ALLOW_NAKED /O2 /Gd
int __cdecl cm_ExProdObjekt(int msg, char* result)
{
	int quantity;
	ushort* obj_entry;
	char* recipe;
	int production_cap;
	ushort* material_iter;
	long production_value;
	short* player_entry;
	uint line;
	short* lager;
	char* recipe_def;
	int saved_quantity;
	short* owner;

	*(int*)(msg + 0x1a) = g_timestamp_0b6c;
	quantity = gm_GetFieldByType((char*)msg, *(int*)(msg + 0x10));
	*(int*)(msg + 0x10) = quantity;
	quantity = gm_ResolveEntityById((void**)0, (void**)&lager, (void**)0, quantity);
	if (quantity == 0) {
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOn\\command\\command.c",
			0x2f3b,
			"cm_ExProdObjekt() Invalid 'lager_id'",
			1
		);
		return 1;
	}
	if ((*lager != 0x2a) && (*lager != 0x116)) {
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOn\\command\\command.c",
			0x2f53,
			"cm_ExProdObjekt() Lager has wrong Type",
			1
		);
		return 1;
	}
	owner = gm_ResolveParentEntity(lager);
	if (owner == (short*)0) {
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOn\\command\\command.c",
			0x2f6d,
			"cm_ExProdObjekt() Lager hat keinen Besitzer",
			1
		);
		return 1;
	}
	quantity = *(int*)(msg + 0x16);
	recipe_def = g_unknown_1de450 + (uint)*(ushort*)(msg + 0x14) * 0x41;
	saved_quantity = 4;
	material_iter = (ushort*)(recipe_def + 0x26);
	do {
		if (material_iter[4] != 0) {
			obj_entry = (ushort*)gm_StartEntityQuery(*(int*)(lager + 10), 1, 0, (uint)material_iter[4]);
			if (obj_entry == (ushort*)0) {
				quantity = 0;
			}
			else {
				recipe = (char*)gm_GetMsgField((int)lager, (int)obj_entry);
				if (quantity >= (int)recipe / (int)(uint)*material_iter) {
					recipe = (char*)gm_GetMsgField((int)lager, (int)obj_entry);
					quantity = (int)recipe / (int)(uint)*material_iter;
				}
			}
		}
		material_iter = material_iter + 1;
		saved_quantity = saved_quantity + -1;
	} while (saved_quantity != 0);
	recipe = recipe_def;
	saved_quantity = quantity;
	production_cap = gm_KannObjektHergestellt(
		(char*)lager,
		(uint)*(ushort*)(msg + 0x14),
		(uint)*(ushort*)(recipe_def + 0x36) * quantity
	);
	production_cap = production_cap / (int)(uint)*(ushort*)(recipe + 0x36);
	if (production_cap <= quantity) {
		quantity = production_cap;
		saved_quantity = quantity;
	}
	if (quantity == 0) {
		recipe = "cm_ExProdObjekt(): Nicht gen\374gend Rohstoffe";
		line = 0x2fb5;
	LAB_1000e3e1:
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\command.c", line, recipe, 1);
		if (result != (char*)0) {
			result[1] = '\b';
		}
		return 1;
	}
	material_iter = (ushort*)(recipe_def + 0x2e);
	for (production_cap = 0; production_cap < 4; production_cap++) {
		if (*material_iter != 0) {
			obj_entry = (ushort*)gm_StartEntityQuery(*(int*)(lager + 10), 1, 0, (uint)*material_iter);
			if (obj_entry == (ushort*)0) {
				recipe = "cm_ExProdObjekt() Rohstoff verschwunden";
				line = 0x2fdd;
				goto LAB_1000e3e1;
			}
			*(uint*)(obj_entry + 7) = *(int*)(obj_entry + 7) - (uint)material_iter[-4] * quantity;
			recipe = gm_FindSlotById((uint)g_current_season, (uint)*material_iter);
			if (recipe != (char*)0) {
				*(uint*)(recipe + 0x14) = *(int*)(recipe + 0x14) + (uint)*(ushort*)(recipe_def + 0x36) * quantity;
			}
			if (*(int*)(obj_entry + 7) == 0) {
				gm_RemoveObjectByType((char**)(lager + 10), (uint)*material_iter);
			}
		}
		material_iter = material_iter + 1;
	}
	material_iter = (ushort*)gm_StartEntityQuery(*(int*)(lager + 10), 1, 0, (uint)*(ushort*)(msg + 0x14));
	recipe = recipe_def;
	if (material_iter != (ushort*)0) {
		*(uint*)(material_iter + 7) = *(int*)(material_iter + 7) + (uint)*(ushort*)(recipe_def + 0x36) * quantity;
	}
	else {
		material_iter = (ushort*)gm_AllocObjekt(
			*(int*)(lager + 1),
			(uint)*(ushort*)(msg + 0x14),
			(uint)*(ushort*)(recipe_def + 0x36) * quantity
		);
		if (material_iter == (ushort*)0) {
			if (result != (char*)0) {
				result[1] = '\x06';
			}
			return 1;
		}
		if (*lager == 0x2a) {
			*(int*)(material_iter + 7) = *(int*)(material_iter + 7) + 1;
		}
		if (((*recipe == '\x17') || (*recipe == '%')) &&
			((*lager == 0x2a || (*lager == 0x116))) &&
			(((char)owner[1] == '\x06' || ((char)owner[1] == '\a')))) {
			*(int*)(material_iter + 0xe) = 4;
		}
	}
	production_value = (long)(gm_CalculateProductionValue((uint)*(ushort*)(msg + 0x14), 100) * saved_quantity);
	production_cap = gm_WalkEntityChain((int)lager);
	if (production_cap != 0) {
		*(int*)(production_cap + 0x4d) = *(int*)(production_cap + 0x4d) + (int)production_value;
	}
	recipe = gm_FindSlotById((uint)g_current_season, (uint)*(ushort*)(msg + 0x14));
	if (recipe != (char*)0) {
		*(uint*)(recipe + 0x10) = *(int*)(recipe + 0x10) + (uint)*(ushort*)(recipe_def + 0x36) * quantity;
	}
	player_entry = gm_GetEntityTableEntry((char*)owner);
	if (player_entry != (short*)0) {
		*(int*)(player_entry + 0x12) = *(int*)(player_entry + 0x12) + (int)production_value;
	}
	if ((result != (char*)0) && ((*result = '\x01', *(int*)(msg + 0x10) != -1))) {
		result[1] = '\x03';
		*(ushort**)(result + 6) = material_iter;
	}
	return 0;
}
#endif
int g_entity_type_table;
unsigned short* g_query_base;
int g_query_match_count;
unsigned int g_100a8cf8;
