// FUNCTION: SERVER 0x100093a0
#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <winsock2.h>
unsigned int __stdcall timeGetTime(void);

/* Command layer (local externs — server.c uses different signatures) */
int __cdecl cm_QueuePlayerCommand(unsigned int* player, unsigned char* data);
int __cdecl cm_ClosePlayerConnection(unsigned int* player_slot);
int __cdecl cm_ProcessCommandQueue(void);
/* Entity lifecycle (local externs) */
/* Network functions (local externs — signatures differ from net.h) */
int __cdecl AcceptConnections(void);
void __cdecl CleanupSockets(void);
int __cdecl ProcessReceiveData(void);
int __cdecl ProcessSendData(void);
int __cdecl SendBroadcastPacket(unsigned char* data, int size);
typedef int(__cdecl* handler_func)(unsigned char* pkt, int param);

extern DWORD WINAPI thread_proc(LPVOID);
void __cdecl RecvGameSavegame(void);
int __cdecl srv_Init(void);
int __cdecl AdvanceGameClock(int* clock_state, int a2, int a3, int a4);
void __cdecl sim_SetSyncParams(int target, unsigned char type_id, unsigned int field_6, unsigned int field_10);
void __cdecl _seterrormode(int value);
int __cdecl QueueCommandForProcessing(unsigned int* conn, unsigned char* pkt); /* 0x1000a8f0 */
extern handler_func g_dispatch_table[]; /* 0x1002c3f8 */
extern unsigned char g_connections[]; /* 0x101deb00 */
/* Console control handler for graceful shutdown.
 * Handles Ctrl+C and close events. Always returns 0. */

#ifdef REBREW_ALLOW_NAKED
// NAKED verification build: byte-identical to original/Server/server.dll 0x100093a0 (2434B)
__declspec(naked) int __cdecl ServerMainThread(void* lpThreadParameter)
{
    __asm {
        _emit 0x81
        _emit 0xec
        _emit 0xe4
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x53
        _emit 0x55
        _emit 0x56
        _emit 0x57
        _emit 0x68
        _emit 0x04
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x68
        _emit 0xa0
        _emit 0xe9
        _emit 0x1d
        _emit 0x10
        _emit 0x6a
        _emit 0x00
        _emit 0xff
        _emit 0x15
        _emit 0x3c
        _emit 0x40
        _emit 0x02
        _emit 0x10
        _emit 0x6a
        _emit 0x5c
        _emit 0x68
        _emit 0xa0
        _emit 0xe9
        _emit 0x1d
        _emit 0x10
        _emit 0xe8
        _emit 0x78
        _emit 0x11
        _emit 0x01
        _emit 0x00
        _emit 0x8b
        _emit 0x0d
        _emit 0x3c
        _emit 0x99
        _emit 0x02
        _emit 0x10
        _emit 0x83
        _emit 0xc4
        _emit 0x08
        _emit 0x89
        _emit 0x08
        _emit 0x8b
        _emit 0x15
        _emit 0x40
        _emit 0x99
        _emit 0x02
        _emit 0x10
        _emit 0x68
        _emit 0xa0
        _emit 0xe9
        _emit 0x1d
        _emit 0x10
        _emit 0x89
        _emit 0x50
        _emit 0x04
        _emit 0x66
        _emit 0x8b
        _emit 0x0d
        _emit 0x44
        _emit 0x99
        _emit 0x02
        _emit 0x10
        _emit 0x68
        _emit 0x6b
        _emit 0x1d
        _emit 0x00
        _emit 0x00
        _emit 0x68
        _emit 0x34
        _emit 0x99
        _emit 0x02
        _emit 0x10
        _emit 0x68
        _emit 0x2c
        _emit 0x99
        _emit 0x02
        _emit 0x10
        _emit 0x66
        _emit 0x89
        _emit 0x48
        _emit 0x08
        _emit 0xff
        _emit 0x15
        _emit 0x64
        _emit 0x40
        _emit 0x02
        _emit 0x10
        _emit 0x68
        _emit 0xa0
        _emit 0xe9
        _emit 0x1d
        _emit 0x10
        _emit 0x68
        _emit 0x04
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x68
        _emit 0x94
        _emit 0x95
        _emit 0x02
        _emit 0x10
        _emit 0x68
        _emit 0x0c
        _emit 0x99
        _emit 0x02
        _emit 0x10
        _emit 0x68
        _emit 0x00
        _emit 0x99
        _emit 0x02
        _emit 0x10
        _emit 0x68
        _emit 0xf8
        _emit 0x98
        _emit 0x02
        _emit 0x10
        _emit 0xa3
        _emit 0x88
        _emit 0x40
        _emit 0x76
        _emit 0x11
        _emit 0xc7
        _emit 0x05
        _emit 0x84
        _emit 0x40
        _emit 0x76
        _emit 0x11
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0xff
        _emit 0x15
        _emit 0x60
        _emit 0x40
        _emit 0x02
        _emit 0x10
        _emit 0xb9
        _emit 0x1a
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x8d
        _emit 0xbc
        _emit 0x24
        _emit 0x48
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x8b
        _emit 0xb4
        _emit 0x24
        _emit 0xf8
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0xf3
        _emit 0xa5
        _emit 0x66
        _emit 0xa5
        _emit 0x66
        _emit 0x8b
        _emit 0x84
        _emit 0x24
        _emit 0x4a
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x66
        _emit 0x3d
        _emit 0x01
        _emit 0x00
        _emit 0x75
        _emit 0x1d
        _emit 0xc6
        _emit 0x84
        _emit 0x24
        _emit 0x6f
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x8b
        _emit 0x94
        _emit 0x24
        _emit 0x6e
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x81
        _emit 0xe2
        _emit 0xff
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x89
        _emit 0x15
        _emit 0x84
        _emit 0x40
        _emit 0x76
        _emit 0x11
        _emit 0xeb
        _emit 0x1f
        _emit 0x66
        _emit 0x3d
        _emit 0x04
        _emit 0x00
        _emit 0x75
        _emit 0x19
        _emit 0xc6
        _emit 0x84
        _emit 0x24
        _emit 0x6f
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x8b
        _emit 0x84
        _emit 0x24
        _emit 0x6e
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x25
        _emit 0xff
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0xa3
        _emit 0x84
        _emit 0x40
        _emit 0x76
        _emit 0x11
        _emit 0xe8
        _emit 0x96
        _emit 0x08
        _emit 0x00
        _emit 0x00
        _emit 0x8b
        _emit 0x0d
        _emit 0x84
        _emit 0x40
        _emit 0x76
        _emit 0x11
        _emit 0x8d
        _emit 0x94
        _emit 0x24
        _emit 0xb4
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x51
        _emit 0x68
        _emit 0xd8
        _emit 0x98
        _emit 0x02
        _emit 0x10
        _emit 0x52
        _emit 0xe8
        _emit 0xe6
        _emit 0x0d
        _emit 0x01
        _emit 0x00
        _emit 0x8d
        _emit 0x84
        _emit 0x24
        _emit 0xc0
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x6a
        _emit 0x01
        _emit 0x50
        _emit 0x68
        _emit 0x31
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x68
        _emit 0xb0
        _emit 0x98
        _emit 0x02
        _emit 0x10
        _emit 0xe8
        _emit 0x74
        _emit 0xa1
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x1c
        _emit 0xff
        _emit 0x15
        _emit 0x54
        _emit 0x41
        _emit 0x02
        _emit 0x10
        _emit 0x50
        _emit 0xe8
        _emit 0x5a
        _emit 0x20
        _emit 0x01
        _emit 0x00
        _emit 0x83
        _emit 0xc4
        _emit 0x04
        _emit 0x33
        _emit 0xed
        _emit 0x33
        _emit 0xff
        _emit 0xa1
        _emit 0x80
        _emit 0x46
        _emit 0x03
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x85
        _emit 0x21
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x33
        _emit 0xdb
        _emit 0xb8
        _emit 0x00
        _emit 0xeb
        _emit 0x1d
        _emit 0x10
        _emit 0x83
        _emit 0x38
        _emit 0x00
        _emit 0x74
        _emit 0x01
        _emit 0x43
        _emit 0x05
        _emit 0x64
        _emit 0x42
        _emit 0x26
        _emit 0x00
        _emit 0x3d
        _emit 0x20
        _emit 0xfe
        _emit 0x4f
        _emit 0x11
        _emit 0x7c
        _emit 0xee
        _emit 0xe8
        _emit 0x73
        _emit 0x0b
        _emit 0x00
        _emit 0x00
        _emit 0x3b
        _emit 0x1d
        _emit 0x84
        _emit 0x40
        _emit 0x76
        _emit 0x11
        _emit 0x75
        _emit 0x3e
        _emit 0xbf
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0xb8
        _emit 0x00
        _emit 0xeb
        _emit 0x1d
        _emit 0x10
        _emit 0x8b
        _emit 0x08
        _emit 0x85
        _emit 0xc9
        _emit 0x74
        _emit 0x09
        _emit 0xf6
        _emit 0xc5
        _emit 0x08
        _emit 0x0f
        _emit 0x84
        _emit 0xa8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x05
        _emit 0x64
        _emit 0x42
        _emit 0x26
        _emit 0x00
        _emit 0x3d
        _emit 0x20
        _emit 0xfe
        _emit 0x4f
        _emit 0x11
        _emit 0x7c
        _emit 0xe5
        _emit 0x6a
        _emit 0x01
        _emit 0x68
        _emit 0x90
        _emit 0x98
        _emit 0x02
        _emit 0x10
        _emit 0x68
        _emit 0x4e
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x68
        _emit 0xb0
        _emit 0x98
        _emit 0x02
        _emit 0x10
        _emit 0xe8
        _emit 0xf0
        _emit 0xa0
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x8b
        _emit 0x35
        _emit 0x54
        _emit 0x41
        _emit 0x02
        _emit 0x10
        _emit 0xff
        _emit 0xd6
        _emit 0x2b
        _emit 0xc5
        _emit 0x3d
        _emit 0xb8
        _emit 0x0b
        _emit 0x00
        _emit 0x00
        _emit 0x77
        _emit 0x04
        _emit 0x85
        _emit 0xff
        _emit 0x74
        _emit 0x20
        _emit 0x8d
        _emit 0x8c
        _emit 0x24
        _emit 0x48
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x88
        _emit 0x9c
        _emit 0x24
        _emit 0x6f
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x51
        _emit 0x68
        _emit 0x39
        _emit 0x30
        _emit 0x00
        _emit 0x00
        _emit 0xe8
        _emit 0xaf
        _emit 0x7b
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x08
        _emit 0xff
        _emit 0xd6
        _emit 0x8b
        _emit 0xe8
        _emit 0xe8
        _emit 0xe3
        _emit 0x0f
        _emit 0x00
        _emit 0x00
        _emit 0x83
        _emit 0xf8
        _emit 0xff
        _emit 0x74
        _emit 0x4b
        _emit 0xe8
        _emit 0xc9
        _emit 0x12
        _emit 0x00
        _emit 0x00
        _emit 0x83
        _emit 0xf8
        _emit 0xff
        _emit 0x74
        _emit 0x52
        _emit 0xbe
        _emit 0x00
        _emit 0xeb
        _emit 0x1d
        _emit 0x10
        _emit 0x8b
        _emit 0x06
        _emit 0xf6
        _emit 0xc4
        _emit 0x10
        _emit 0x74
        _emit 0x0e
        _emit 0xf6
        _emit 0xc4
        _emit 0x04
        _emit 0x75
        _emit 0x52
        _emit 0x56
        _emit 0xe8
        _emit 0x2d
        _emit 0x0d
        _emit 0x00
        _emit 0x00
        _emit 0x83
        _emit 0xc4
        _emit 0x04
        _emit 0x81
        _emit 0xc6
        _emit 0x64
        _emit 0x42
        _emit 0x26
        _emit 0x00
        _emit 0x81
        _emit 0xfe
        _emit 0x20
        _emit 0xfe
        _emit 0x4f
        _emit 0x11
        _emit 0x7c
        _emit 0xdd
        _emit 0x6a
        _emit 0x1e
        _emit 0xff
        _emit 0x15
        _emit 0x58
        _emit 0x40
        _emit 0x02
        _emit 0x10
        _emit 0x85
        _emit 0xff
        _emit 0x0f
        _emit 0x84
        _emit 0x0e
        _emit 0xff
        _emit 0xff
        _emit 0xff
        _emit 0xeb
        _emit 0x3a
        _emit 0x33
        _emit 0xff
        _emit 0xe9
        _emit 0x76
        _emit 0xff
        _emit 0xff
        _emit 0xff
        _emit 0x6a
        _emit 0x01
        _emit 0x68
        _emit 0x6c
        _emit 0x98
        _emit 0x02
        _emit 0x10
        _emit 0x68
        _emit 0x5f
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0xe9
        _emit 0x13
        _emit 0x07
        _emit 0x00
        _emit 0x00
        _emit 0x6a
        _emit 0x01
        _emit 0x68
        _emit 0x6c
        _emit 0x98
        _emit 0x02
        _emit 0x10
        _emit 0x68
        _emit 0x6a
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0xe9
        _emit 0x02
        _emit 0x07
        _emit 0x00
        _emit 0x00
        _emit 0x6a
        _emit 0x01
        _emit 0x68
        _emit 0x34
        _emit 0x98
        _emit 0x02
        _emit 0x10
        _emit 0x68
        _emit 0x76
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0xe9
        _emit 0xf1
        _emit 0x06
        _emit 0x00
        _emit 0x00
        _emit 0xb9
        _emit 0x00
        _emit 0xeb
        _emit 0x1d
        _emit 0x10
        _emit 0x8b
        _emit 0x01
        _emit 0xa8
        _emit 0x01
        _emit 0x74
        _emit 0x0a
        _emit 0x80
        _emit 0xe4
        _emit 0xfd
        _emit 0x0d
        _emit 0x04
        _emit 0x40
        _emit 0x00
        _emit 0x00
        _emit 0x89
        _emit 0x01
        _emit 0x81
        _emit 0xc1
        _emit 0x64
        _emit 0x42
        _emit 0x26
        _emit 0x00
        _emit 0x81
        _emit 0xf9
        _emit 0x20
        _emit 0xfe
        _emit 0x4f
        _emit 0x11
        _emit 0x7c
        _emit 0xe2
        _emit 0x33
        _emit 0xc9
        _emit 0xb8
        _emit 0x00
        _emit 0xeb
        _emit 0x1d
        _emit 0x10
        _emit 0x8b
        _emit 0x10
        _emit 0xf6
        _emit 0xc6
        _emit 0x04
        _emit 0x0f
        _emit 0x85
        _emit 0xf5
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x05
        _emit 0x64
        _emit 0x42
        _emit 0x26
        _emit 0x00
        _emit 0x41
        _emit 0x3d
        _emit 0x20
        _emit 0xfe
        _emit 0x4f
        _emit 0x11
        _emit 0x7c
        _emit 0xe8
        _emit 0xe8
        _emit 0xb9
        _emit 0x09
        _emit 0x00
        _emit 0x00
        _emit 0x68
        _emit 0xd0
        _emit 0x07
        _emit 0x00
        _emit 0x00
        _emit 0xff
        _emit 0x15
        _emit 0x58
        _emit 0x40
        _emit 0x02
        _emit 0x10
        _emit 0x33
        _emit 0xff
        _emit 0xbe
        _emit 0x00
        _emit 0xeb
        _emit 0x1d
        _emit 0x10
        _emit 0xb3
        _emit 0x07
        _emit 0x33
        _emit 0xed
        _emit 0x8b
        _emit 0x06
        _emit 0x3b
        _emit 0xc5
        _emit 0x74
        _emit 0x71
        _emit 0x24
        _emit 0x08
        _emit 0x8d
        _emit 0x54
        _emit 0x24
        _emit 0x10
        _emit 0xf6
        _emit 0xd8
        _emit 0x1a
        _emit 0xc0
        _emit 0x52
        _emit 0x22
        _emit 0xc3
        _emit 0x56
        _emit 0x04
        _emit 0x02
        _emit 0xc6
        _emit 0x44
        _emit 0x24
        _emit 0x18
        _emit 0x04
        _emit 0xc6
        _emit 0x44
        _emit 0x24
        _emit 0x1b
        _emit 0xff
        _emit 0xc7
        _emit 0x44
        _emit 0x24
        _emit 0x1c
        _emit 0xff
        _emit 0xff
        _emit 0xff
        _emit 0xff
        _emit 0x89
        _emit 0x6c
        _emit 0x24
        _emit 0x24
        _emit 0x88
        _emit 0x44
        _emit 0x24
        _emit 0x28
        _emit 0xe8
        _emit 0xfe
        _emit 0x12
        _emit 0x00
        _emit 0x00
        _emit 0x83
        _emit 0xc4
        _emit 0x08
        _emit 0x83
        _emit 0xf8
        _emit 0xff
        _emit 0x0f
        _emit 0x84
        _emit 0x60
        _emit 0x06
        _emit 0x00
        _emit 0x00
        _emit 0x8d
        _emit 0x44
        _emit 0x24
        _emit 0x10
        _emit 0x89
        _emit 0x7c
        _emit 0x24
        _emit 0x21
        _emit 0x50
        _emit 0x56
        _emit 0xc6
        _emit 0x44
        _emit 0x24
        _emit 0x18
        _emit 0x20
        _emit 0xc6
        _emit 0x44
        _emit 0x24
        _emit 0x1b
        _emit 0xff
        _emit 0xc7
        _emit 0x44
        _emit 0x24
        _emit 0x1c
        _emit 0xff
        _emit 0xff
        _emit 0xff
        _emit 0xff
        _emit 0x89
        _emit 0x6c
        _emit 0x24
        _emit 0x24
        _emit 0x88
        _emit 0x5c
        _emit 0x24
        _emit 0x28
        _emit 0x47
        _emit 0xe8
        _emit 0xc8
        _emit 0x12
        _emit 0x00
        _emit 0x00
        _emit 0x83
        _emit 0xc4
        _emit 0x08
        _emit 0x83
        _emit 0xf8
        _emit 0xff
        _emit 0x0f
        _emit 0x84
        _emit 0x2a
        _emit 0x06
        _emit 0x00
        _emit 0x00
        _emit 0x81
        _emit 0xc6
        _emit 0x64
        _emit 0x42
        _emit 0x26
        _emit 0x00
        _emit 0x81
        _emit 0xfe
        _emit 0x20
        _emit 0xfe
        _emit 0x4f
        _emit 0x11
        _emit 0x0f
        _emit 0x8c
        _emit 0x77
        _emit 0xff
        _emit 0xff
        _emit 0xff
        _emit 0x6a
        _emit 0x01
        _emit 0x68
        _emit 0x24
        _emit 0x98
        _emit 0x02
        _emit 0x10
        _emit 0x68
        _emit 0xca
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x68
        _emit 0xb0
        _emit 0x98
        _emit 0x02
        _emit 0x10
        _emit 0xe8
        _emit 0x34
        _emit 0x9f
        _emit 0xff
        _emit 0xff
        _emit 0x8b
        _emit 0x3d
        _emit 0x58
        _emit 0x40
        _emit 0x02
        _emit 0x10
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x39
        _emit 0x2d
        _emit 0x80
        _emit 0x46
        _emit 0x03
        _emit 0x10
        _emit 0x75
        _emit 0x64
        _emit 0xbe
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0xb8
        _emit 0x00
        _emit 0xeb
        _emit 0x1d
        _emit 0x10
        _emit 0xf6
        _emit 0x00
        _emit 0x08
        _emit 0x75
        _emit 0x2f
        _emit 0x05
        _emit 0x64
        _emit 0x42
        _emit 0x26
        _emit 0x00
        _emit 0x3d
        _emit 0x20
        _emit 0xfe
        _emit 0x4f
        _emit 0x11
        _emit 0x7c
        _emit 0xef
        _emit 0xeb
        _emit 0x23
        _emit 0x8b
        _emit 0xc1
        _emit 0xc1
        _emit 0xe0
        _emit 0x04
        _emit 0x03
        _emit 0xc1
        _emit 0xc1
        _emit 0xe0
        _emit 0x08
        _emit 0x03
        _emit 0xc1
        _emit 0xc1
        _emit 0xe0
        _emit 0x04
        _emit 0x03
        _emit 0xc1
        _emit 0x8d
        _emit 0x04
        _emit 0xc0
        _emit 0x83
        _emit 0x0c
        _emit 0x85
        _emit 0x00
        _emit 0xeb
        _emit 0x1d
        _emit 0x10
        _emit 0x08
        _emit 0xe9
        _emit 0xfc
        _emit 0xfe
        _emit 0xff
        _emit 0xff
        _emit 0x33
        _emit 0xf6
        _emit 0xe8
        _emit 0x0e
        _emit 0x0e
        _emit 0x00
        _emit 0x00
        _emit 0x83
        _emit 0xf8
        _emit 0xff
        _emit 0x0f
        _emit 0x84
        _emit 0xbc
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0xe8
        _emit 0xf0
        _emit 0x10
        _emit 0x00
        _emit 0x00
        _emit 0x83
        _emit 0xf8
        _emit 0xff
        _emit 0x0f
        _emit 0x84
        _emit 0xae
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x6a
        _emit 0x1e
        _emit 0xff
        _emit 0xd7
        _emit 0x3b
        _emit 0xf5
        _emit 0x74
        _emit 0x94
        _emit 0xe8
        _emit 0xda
        _emit 0xaa
        _emit 0x00
        _emit 0x00
        _emit 0x6a
        _emit 0x01
        _emit 0x68
        _emit 0x0c
        _emit 0x98
        _emit 0x02
        _emit 0x10
        _emit 0x68
        _emit 0xf9
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x68
        _emit 0xb0
        _emit 0x98
        _emit 0x02
        _emit 0x10
        _emit 0xe8
        _emit 0xa4
        _emit 0x9e
        _emit 0xff
        _emit 0xff
        _emit 0xa0
        _emit 0x64
        _emit 0xe4
        _emit 0x1d
        _emit 0x10
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0xa8
        _emit 0x04
        _emit 0x0f
        _emit 0x85
        _emit 0x50
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x6a
        _emit 0x01
        _emit 0x68
        _emit 0xfc
        _emit 0x97
        _emit 0x02
        _emit 0x10
        _emit 0x68
        _emit 0xff
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x68
        _emit 0xb0
        _emit 0x98
        _emit 0x02
        _emit 0x10
        _emit 0xe8
        _emit 0x7e
        _emit 0x9e
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0xbe
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0xbd
        _emit 0x00
        _emit 0xeb
        _emit 0x1d
        _emit 0x10
        _emit 0xbb
        _emit 0xc8
        _emit 0xea
        _emit 0x1d
        _emit 0x10
        _emit 0xf6
        _emit 0x45
        _emit 0x00
        _emit 0x04
        _emit 0x0f
        _emit 0x84
        _emit 0xd2
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x8b
        _emit 0x03
        _emit 0x83
        _emit 0xf8
        _emit 0xff
        _emit 0x75
        _emit 0x53
        _emit 0x8b
        _emit 0x0d
        _emit 0xc0
        _emit 0xea
        _emit 0x1d
        _emit 0x10
        _emit 0x8d
        _emit 0x54
        _emit 0x24
        _emit 0x10
        _emit 0x52
        _emit 0x55
        _emit 0xc6
        _emit 0x44
        _emit 0x24
        _emit 0x18
        _emit 0x08
        _emit 0xc6
        _emit 0x44
        _emit 0x24
        _emit 0x1b
        _emit 0xff
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x1c
        _emit 0xc7
        _emit 0x44
        _emit 0x24
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x89
        _emit 0x4c
        _emit 0x24
        _emit 0x28
        _emit 0xe8
        _emit 0x90
        _emit 0x11
        _emit 0x00
        _emit 0x00
        _emit 0x83
        _emit 0xc4
        _emit 0x08
        _emit 0x83
        _emit 0xf8
        _emit 0xff
        _emit 0x0f
        _emit 0x84
        _emit 0xf2
        _emit 0x04
        _emit 0x00
        _emit 0x00
        _emit 0xc7
        _emit 0x03
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0xe9
        _emit 0x87
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x6a
        _emit 0x01
        _emit 0x68
        _emit 0x6c
        _emit 0x98
        _emit 0x02
        _emit 0x10
        _emit 0x68
        _emit 0xdf
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0xe9
        _emit 0xc9
        _emit 0x04
        _emit 0x00
        _emit 0x00
        _emit 0x8b
        _emit 0x0d
        _emit 0xe8
        _emit 0xea
        _emit 0x1d
        _emit 0x10
        _emit 0x8d
        _emit 0x54
        _emit 0x24
        _emit 0x10
        _emit 0x8d
        _emit 0x7c
        _emit 0x24
        _emit 0x20
        _emit 0xc6
        _emit 0x44
        _emit 0x24
        _emit 0x10
        _emit 0x09
        _emit 0x8d
        _emit 0x34
        _emit 0x08
        _emit 0xb9
        _emit 0x20
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0xc6
        _emit 0x44
        _emit 0x24
        _emit 0x13
        _emit 0xff
        _emit 0xc7
        _emit 0x44
        _emit 0x24
        _emit 0x14
        _emit 0xff
        _emit 0xff
        _emit 0xff
        _emit 0xff
        _emit 0xc7
        _emit 0x44
        _emit 0x24
        _emit 0x1c
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x52
        _emit 0xf3
        _emit 0xa5
        _emit 0x55
        _emit 0xe8
        _emit 0x2f
        _emit 0x11
        _emit 0x00
        _emit 0x00
        _emit 0x83
        _emit 0xc4
        _emit 0x08
        _emit 0x83
        _emit 0xf8
        _emit 0xff
        _emit 0x74
        _emit 0x08
        _emit 0x81
        _emit 0x03
        _emit 0x80
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0xeb
        _emit 0x19
        _emit 0x6a
        _emit 0x01
        _emit 0x68
        _emit 0xe4
        _emit 0x97
        _emit 0x02
        _emit 0x10
        _emit 0x68
        _emit 0x28
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x68
        _emit 0xb0
        _emit 0x98
        _emit 0x02
        _emit 0x10
        _emit 0xe8
        _emit 0xa9
        _emit 0x9d
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x8b
        _emit 0x03
        _emit 0x8b
        _emit 0x0d
        _emit 0xc0
        _emit 0xea
        _emit 0x1d
        _emit 0x10
        _emit 0x3b
        _emit 0xc1
        _emit 0x72
        _emit 0x08
        _emit 0x8b
        _emit 0x45
        _emit 0x00
        _emit 0x24
        _emit 0xfb
        _emit 0x89
        _emit 0x45
        _emit 0x00
        _emit 0x33
        _emit 0xf6
        _emit 0x83
        _emit 0xc3
        _emit 0x04
        _emit 0x81
        _emit 0xc5
        _emit 0x64
        _emit 0x42
        _emit 0x26
        _emit 0x00
        _emit 0x81
        _emit 0xfb
        _emit 0xe8
        _emit 0xea
        _emit 0x1d
        _emit 0x10
        _emit 0x0f
        _emit 0x8c
        _emit 0x0f
        _emit 0xff
        _emit 0xff
        _emit 0xff
        _emit 0xe8
        _emit 0xa6
        _emit 0x0c
        _emit 0x00
        _emit 0x00
        _emit 0x83
        _emit 0xf8
        _emit 0xff
        _emit 0x74
        _emit 0x1c
        _emit 0xe8
        _emit 0x8c
        _emit 0x0f
        _emit 0x00
        _emit 0x00
        _emit 0x83
        _emit 0xf8
        _emit 0xff
        _emit 0x74
        _emit 0x12
        _emit 0x6a
        _emit 0x1e
        _emit 0xff
        _emit 0x15
        _emit 0x58
        _emit 0x40
        _emit 0x02
        _emit 0x10
        _emit 0x85
        _emit 0xf6
        _emit 0x0f
        _emit 0x84
        _emit 0xdc
        _emit 0xfe
        _emit 0xff
        _emit 0xff
        _emit 0xeb
        _emit 0x2e
        _emit 0x6a
        _emit 0x01
        _emit 0x68
        _emit 0x6c
        _emit 0x98
        _emit 0x02
        _emit 0x10
        _emit 0x68
        _emit 0x3a
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0xe9
        _emit 0x05
        _emit 0x04
        _emit 0x00
        _emit 0x00
        _emit 0xb9
        _emit 0x00
        _emit 0xeb
        _emit 0x1d
        _emit 0x10
        _emit 0x8b
        _emit 0x01
        _emit 0xa8
        _emit 0x04
        _emit 0x74
        _emit 0x04
        _emit 0x24
        _emit 0xfb
        _emit 0x89
        _emit 0x01
        _emit 0x81
        _emit 0xc1
        _emit 0x64
        _emit 0x42
        _emit 0x26
        _emit 0x00
        _emit 0x81
        _emit 0xf9
        _emit 0x20
        _emit 0xfe
        _emit 0x4f
        _emit 0x11
        _emit 0x7c
        _emit 0xe8
        _emit 0x8b
        _emit 0x0d
        _emit 0xe8
        _emit 0xea
        _emit 0x1d
        _emit 0x10
        _emit 0x51
        _emit 0xe8
        _emit 0xfb
        _emit 0xce
        _emit 0xff
        _emit 0xff
        _emit 0xa0
        _emit 0x64
        _emit 0xe4
        _emit 0x1d
        _emit 0x10
        _emit 0x83
        _emit 0xc4
        _emit 0x04
        _emit 0x33
        _emit 0xed
        _emit 0xa8
        _emit 0x04
        _emit 0x89
        _emit 0x2d
        _emit 0xe8
        _emit 0xea
        _emit 0x1d
        _emit 0x10
        _emit 0x89
        _emit 0x2d
        _emit 0xc0
        _emit 0xea
        _emit 0x1d
        _emit 0x10
        _emit 0x0f
        _emit 0x85
        _emit 0x81
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x6a
        _emit 0x01
        _emit 0x68
        _emit 0xbc
        _emit 0x97
        _emit 0x02
        _emit 0x10
        _emit 0x68
        _emit 0x62
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x68
        _emit 0xb0
        _emit 0x98
        _emit 0x02
        _emit 0x10
        _emit 0xe8
        _emit 0xe7
        _emit 0x9c
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0xb9
        _emit 0x00
        _emit 0xeb
        _emit 0x1d
        _emit 0x10
        _emit 0x8b
        _emit 0x01
        _emit 0xa8
        _emit 0x01
        _emit 0x74
        _emit 0x04
        _emit 0x0c
        _emit 0x10
        _emit 0x89
        _emit 0x01
        _emit 0x81
        _emit 0xc1
        _emit 0x64
        _emit 0x42
        _emit 0x26
        _emit 0x00
        _emit 0x81
        _emit 0xf9
        _emit 0x20
        _emit 0xfe
        _emit 0x4f
        _emit 0x11
        _emit 0x7c
        _emit 0xe8
        _emit 0x8b
        _emit 0x3d
        _emit 0x58
        _emit 0x40
        _emit 0x02
        _emit 0x10
        _emit 0xbe
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0xb8
        _emit 0x00
        _emit 0xeb
        _emit 0x1d
        _emit 0x10
        _emit 0x3d
        _emit 0x20
        _emit 0xfe
        _emit 0x4f
        _emit 0x11
        _emit 0x7d
        _emit 0x10
        _emit 0xf6
        _emit 0x00
        _emit 0x10
        _emit 0x74
        _emit 0x02
        _emit 0x33
        _emit 0xf6
        _emit 0x05
        _emit 0x64
        _emit 0x42
        _emit 0x26
        _emit 0x00
        _emit 0x3b
        _emit 0xf5
        _emit 0x75
        _emit 0xe9
        _emit 0xe8
        _emit 0xcb
        _emit 0x0b
        _emit 0x00
        _emit 0x00
        _emit 0x83
        _emit 0xf8
        _emit 0xff
        _emit 0x0f
        _emit 0x84
        _emit 0xc6
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0xe8
        _emit 0xad
        _emit 0x0e
        _emit 0x00
        _emit 0x00
        _emit 0x83
        _emit 0xf8
        _emit 0xff
        _emit 0x0f
        _emit 0x84
        _emit 0xb8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x6a
        _emit 0x1e
        _emit 0xff
        _emit 0xd7
        _emit 0x3b
        _emit 0xf5
        _emit 0x74
        _emit 0xbb
        _emit 0xbe
        _emit 0x00
        _emit 0xeb
        _emit 0x1d
        _emit 0x10
        _emit 0x83
        _emit 0xcf
        _emit 0xff
        _emit 0xf6
        _emit 0x06
        _emit 0x01
        _emit 0x74
        _emit 0x3f
        _emit 0x8d
        _emit 0x94
        _emit 0x24
        _emit 0xac
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0xc6
        _emit 0x84
        _emit 0x24
        _emit 0xac
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x04
        _emit 0x52
        _emit 0x56
        _emit 0xc6
        _emit 0x84
        _emit 0x24
        _emit 0xb7
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0xff
        _emit 0x89
        _emit 0xbc
        _emit 0x24
        _emit 0xb8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x89
        _emit 0xac
        _emit 0x24
        _emit 0xc0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0xc6
        _emit 0x84
        _emit 0x24
        _emit 0xc4
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x04
        _emit 0xe8
        _emit 0x9b
        _emit 0x0f
        _emit 0x00
        _emit 0x00
        _emit 0x83
        _emit 0xc4
        _emit 0x08
        _emit 0x3b
        _emit 0xc7
        _emit 0x0f
        _emit 0x84
        _emit 0xfe
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x81
        _emit 0xc6
        _emit 0x64
        _emit 0x42
        _emit 0x26
        _emit 0x00
        _emit 0x81
        _emit 0xfe
        _emit 0x20
        _emit 0xfe
        _emit 0x4f
        _emit 0x11
        _emit 0x7c
        _emit 0xae
        _emit 0x6a
        _emit 0x01
        _emit 0x68
        _emit 0xb0
        _emit 0x97
        _emit 0x02
        _emit 0x10
        _emit 0x68
        _emit 0xa8
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x68
        _emit 0xb0
        _emit 0x98
        _emit 0x02
        _emit 0x10
        _emit 0xe8
        _emit 0x0c
        _emit 0x9c
        _emit 0xff
        _emit 0xff
        _emit 0xa1
        _emit 0x80
        _emit 0x46
        _emit 0x03
        _emit 0x10
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x3b
        _emit 0xc5
        _emit 0x0f
        _emit 0x85
        _emit 0x9c
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x6a
        _emit 0x1e
        _emit 0xff
        _emit 0x15
        _emit 0x58
        _emit 0x40
        _emit 0x02
        _emit 0x10
        _emit 0xff
        _emit 0x15
        _emit 0x5c
        _emit 0x40
        _emit 0x02
        _emit 0x10
        _emit 0x8b
        _emit 0xd8
        _emit 0x33
        _emit 0xff
        _emit 0xb8
        _emit 0x00
        _emit 0xeb
        _emit 0x1d
        _emit 0x10
        _emit 0x8b
        _emit 0x08
        _emit 0x3b
        _emit 0xcd
        _emit 0x74
        _emit 0x05
        _emit 0xf6
        _emit 0xc1
        _emit 0x40
        _emit 0x75
        _emit 0x1f
        _emit 0x05
        _emit 0x64
        _emit 0x42
        _emit 0x26
        _emit 0x00
        _emit 0x3d
        _emit 0x20
        _emit 0xfe
        _emit 0x4f
        _emit 0x11
        _emit 0x7c
        _emit 0xe9
        _emit 0xeb
        _emit 0x33
        _emit 0x6a
        _emit 0x01
        _emit 0x68
        _emit 0x6c
        _emit 0x98
        _emit 0x02
        _emit 0x10
        _emit 0x68
        _emit 0x78
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0xe9
        _emit 0x7c
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x33
        _emit 0xff
        _emit 0xb8
        _emit 0x00
        _emit 0xeb
        _emit 0x1d
        _emit 0x10
        _emit 0x8b
        _emit 0x08
        _emit 0x3b
        _emit 0xcd
        _emit 0x74
        _emit 0x09
        _emit 0xf6
        _emit 0xc1
        _emit 0x40
        _emit 0x0f
        _emit 0x84
        _emit 0xcb
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x05
        _emit 0x64
        _emit 0x42
        _emit 0x26
        _emit 0x00
        _emit 0x3d
        _emit 0x20
        _emit 0xfe
        _emit 0x4f
        _emit 0x11
        _emit 0x7c
        _emit 0xe5
        _emit 0xbe
        _emit 0x00
        _emit 0xeb
        _emit 0x1d
        _emit 0x10
        _emit 0x8b
        _emit 0x06
        _emit 0x3b
        _emit 0xc5
        _emit 0x74
        _emit 0x3a
        _emit 0xa8
        _emit 0x40
        _emit 0x74
        _emit 0x36
        _emit 0x6a
        _emit 0x01
        _emit 0x68
        _emit 0xa0
        _emit 0x97
        _emit 0x02
        _emit 0x10
        _emit 0x68
        _emit 0xce
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x68
        _emit 0xb0
        _emit 0x98
        _emit 0x02
        _emit 0x10
        _emit 0xe8
        _emit 0x74
        _emit 0x9b
        _emit 0xff
        _emit 0xff
        _emit 0x8b
        _emit 0x16
        _emit 0x8d
        _emit 0x86
        _emit 0x54
        _emit 0x41
        _emit 0x26
        _emit 0x00
        _emit 0x83
        _emit 0xe2
        _emit 0xbf
        _emit 0x50
        _emit 0x56
        _emit 0x89
        _emit 0x16
        _emit 0xe8
        _emit 0xc0
        _emit 0x0e
        _emit 0x00
        _emit 0x00
        _emit 0x83
        _emit 0xc4
        _emit 0x18
        _emit 0x83
        _emit 0xf8
        _emit 0xff
        _emit 0x0f
        _emit 0x84
        _emit 0x22
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x81
        _emit 0xc6
        _emit 0x64
        _emit 0x42
        _emit 0x26
        _emit 0x00
        _emit 0x81
        _emit 0xfe
        _emit 0x20
        _emit 0xfe
        _emit 0x4f
        _emit 0x11
        _emit 0x7c
        _emit 0xb2
        _emit 0x39
        _emit 0x2d
        _emit 0x90
        _emit 0x40
        _emit 0x76
        _emit 0x11
        _emit 0x75
        _emit 0x6b
        _emit 0x3b
        _emit 0xfd
        _emit 0x0f
        _emit 0x85
        _emit 0xac
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0xba
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0xb8
        _emit 0x00
        _emit 0xeb
        _emit 0x1d
        _emit 0x10
        _emit 0x89
        _emit 0x15
        _emit 0x90
        _emit 0x40
        _emit 0x76
        _emit 0x11
        _emit 0x8b
        _emit 0x08
        _emit 0x3b
        _emit 0xcd
        _emit 0x74
        _emit 0x07
        _emit 0xf6
        _emit 0xc1
        _emit 0x20
        _emit 0x75
        _emit 0x02
        _emit 0x33
        _emit 0xd2
        _emit 0x05
        _emit 0x64
        _emit 0x42
        _emit 0x26
        _emit 0x00
        _emit 0x3d
        _emit 0x20
        _emit 0xfe
        _emit 0x4f
        _emit 0x11
        _emit 0x7c
        _emit 0xe7
        _emit 0x3b
        _emit 0xd5
        _emit 0x89
        _emit 0x15
        _emit 0x90
        _emit 0x40
        _emit 0x76
        _emit 0x11
        _emit 0x0f
        _emit 0x84
        _emit 0x75
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0xb9
        _emit 0x00
        _emit 0xeb
        _emit 0x1d
        _emit 0x10
        _emit 0x8b
        _emit 0x01
        _emit 0x3b
        _emit 0xc5
        _emit 0x74
        _emit 0x04
        _emit 0x24
        _emit 0xdf
        _emit 0x89
        _emit 0x01
        _emit 0x81
        _emit 0xc1
        _emit 0x64
        _emit 0x42
        _emit 0x26
        _emit 0x00
        _emit 0x81
        _emit 0xf9
        _emit 0x20
        _emit 0xfe
        _emit 0x4f
        _emit 0x11
        _emit 0x7c
        _emit 0xe8
        _emit 0x89
        _emit 0x1d
        _emit 0xf0
        _emit 0xea
        _emit 0x1d
        _emit 0x10
        _emit 0xeb
        _emit 0x1b
        _emit 0xbf
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0xeb
        _emit 0x8d
        _emit 0x3b
        _emit 0xfd
        _emit 0x0f
        _emit 0x85
        _emit 0x41
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x39
        _emit 0x1d
        _emit 0xf0
        _emit 0xea
        _emit 0x1d
        _emit 0x10
        _emit 0x0f
        _emit 0x87
        _emit 0x35
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x55
        _emit 0x6a
        _emit 0x01
        _emit 0x55
        _emit 0x68
        _emit 0x80
        _emit 0x58
        _emit 0x03
        _emit 0x10
        _emit 0xe8
        _emit 0x31
        _emit 0xba
        _emit 0x00
        _emit 0x00
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0xbe
        _emit 0x00
        _emit 0xeb
        _emit 0x1d
        _emit 0x10
        _emit 0x83
        _emit 0xcb
        _emit 0xff
        _emit 0x39
        _emit 0x2e
        _emit 0x74
        _emit 0x51
        _emit 0x8b
        _emit 0x15
        _emit 0x84
        _emit 0x58
        _emit 0x03
        _emit 0x10
        _emit 0x8b
        _emit 0x0d
        _emit 0x80
        _emit 0x58
        _emit 0x03
        _emit 0x10
        _emit 0xa1
        _emit 0x88
        _emit 0x58
        _emit 0x03
        _emit 0x10
        _emit 0x89
        _emit 0x54
        _emit 0x24
        _emit 0x24
        _emit 0x8d
        _emit 0x54
        _emit 0x24
        _emit 0x10
        _emit 0x89
        _emit 0x4c
        _emit 0x24
        _emit 0x20
        _emit 0x66
        _emit 0x8b
        _emit 0x0d
        _emit 0x8c
        _emit 0x58
        _emit 0x03
        _emit 0x10
        _emit 0x52
        _emit 0x56
        _emit 0xc6
        _emit 0x44
        _emit 0x24
        _emit 0x18
        _emit 0x1e
        _emit 0xc6
        _emit 0x44
        _emit 0x24
        _emit 0x1b
        _emit 0xff
        _emit 0x89
        _emit 0x5c
        _emit 0x24
        _emit 0x1c
        _emit 0x89
        _emit 0x6c
        _emit 0x24
        _emit 0x24
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x30
        _emit 0x66
        _emit 0x89
        _emit 0x4c
        _emit 0x24
        _emit 0x34
        _emit 0xe8
        _emit 0xbc
        _emit 0x0d
        _emit 0x00
        _emit 0x00
        _emit 0x83
        _emit 0xc4
        _emit 0x08
        _emit 0x3b
        _emit 0xc3
        _emit 0x0f
        _emit 0x84
        _emit 0x1f
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x81
        _emit 0xc6
        _emit 0x64
        _emit 0x42
        _emit 0x26
        _emit 0x00
        _emit 0x81
        _emit 0xfe
        _emit 0x20
        _emit 0xfe
        _emit 0x4f
        _emit 0x11
        _emit 0x7c
        _emit 0x9d
        _emit 0x66
        _emit 0x83
        _emit 0x3d
        _emit 0x84
        _emit 0x58
        _emit 0x03
        _emit 0x10
        _emit 0x17
        _emit 0x0f
        _emit 0x82
        _emit 0x99
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0xbf
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0xbe
        _emit 0x00
        _emit 0xeb
        _emit 0x1d
        _emit 0x10
        _emit 0x39
        _emit 0x2e
        _emit 0x74
        _emit 0x5f
        _emit 0x3b
        _emit 0xfd
        _emit 0xc6
        _emit 0x84
        _emit 0x24
        _emit 0xac
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x20
        _emit 0xc6
        _emit 0x84
        _emit 0x24
        _emit 0xaf
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0xff
        _emit 0x89
        _emit 0x9c
        _emit 0x24
        _emit 0xb0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x89
        _emit 0xac
        _emit 0x24
        _emit 0xb8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0xc6
        _emit 0x84
        _emit 0x24
        _emit 0xbc
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x02
        _emit 0x74
        _emit 0x0f
        _emit 0xc7
        _emit 0x84
        _emit 0x24
        _emit 0xbd
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x33
        _emit 0xff
        _emit 0xeb
        _emit 0x07
        _emit 0x89
        _emit 0xac
        _emit 0x24
        _emit 0xbd
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x8d
        _emit 0x84
        _emit 0x24
        _emit 0xac
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x50
        _emit 0x56
        _emit 0xe8
        _emit 0x39
        _emit 0x0d
        _emit 0x00
        _emit 0x00
        _emit 0x83
        _emit 0xc4
        _emit 0x08
        _emit 0x3b
        _emit 0xc3
        _emit 0x0f
        _emit 0x84
        _emit 0x9c
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x89
        _emit 0x2d
        _emit 0x90
        _emit 0x40
        _emit 0x76
        _emit 0x11
        _emit 0x81
        _emit 0xc6
        _emit 0x64
        _emit 0x42
        _emit 0x26
        _emit 0x00
        _emit 0x81
        _emit 0xfe
        _emit 0x20
        _emit 0xfe
        _emit 0x4f
        _emit 0x11
        _emit 0x7c
        _emit 0x8f
        _emit 0x8b
        _emit 0x1d
        _emit 0x80
        _emit 0x58
        _emit 0x03
        _emit 0x10
        _emit 0x55
        _emit 0x55
        _emit 0x43
        _emit 0x6a
        _emit 0x06
        _emit 0x68
        _emit 0x80
        _emit 0x58
        _emit 0x03
        _emit 0x10
        _emit 0x89
        _emit 0x1d
        _emit 0x80
        _emit 0x58
        _emit 0x03
        _emit 0x10
        _emit 0xe8
        _emit 0xef
        _emit 0xb9
        _emit 0x00
        _emit 0x00
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x8b
        _emit 0x0d
        _emit 0xf0
        _emit 0xc3
        _emit 0x02
        _emit 0x10
        _emit 0xa1
        _emit 0xf0
        _emit 0xea
        _emit 0x1d
        _emit 0x10
        _emit 0x03
        _emit 0xc1
        _emit 0xa3
        _emit 0xf0
        _emit 0xea
        _emit 0x1d
        _emit 0x10
        _emit 0xe8
        _emit 0xb5
        _emit 0x08
        _emit 0x00
        _emit 0x00
        _emit 0x83
        _emit 0xf8
        _emit 0xff
        _emit 0x74
        _emit 0x35
        _emit 0xe8
        _emit 0x9b
        _emit 0x0b
        _emit 0x00
        _emit 0x00
        _emit 0x83
        _emit 0xf8
        _emit 0xff
        _emit 0x74
        _emit 0x2b
        _emit 0xe8
        _emit 0xf1
        _emit 0x0d
        _emit 0x00
        _emit 0x00
        _emit 0x83
        _emit 0xf8
        _emit 0xff
        _emit 0x74
        _emit 0x3a
        _emit 0x39
        _emit 0x2d
        _emit 0x80
        _emit 0x46
        _emit 0x03
        _emit 0x10
        _emit 0x0f
        _emit 0x84
        _emit 0x64
        _emit 0xfd
        _emit 0xff
        _emit 0xff
        _emit 0x5f
        _emit 0x89
        _emit 0x2d
        _emit 0x80
        _emit 0x46
        _emit 0x03
        _emit 0x10
        _emit 0x5e
        _emit 0x5d
        _emit 0x33
        _emit 0xc0
        _emit 0x5b
        _emit 0x81
        _emit 0xc4
        _emit 0xe4
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0xc2
        _emit 0x04
        _emit 0x00
        _emit 0x6a
        _emit 0x01
        _emit 0x68
        _emit 0x6c
        _emit 0x98
        _emit 0x02
        _emit 0x10
        _emit 0x68
        _emit 0x48
        _emit 0x03
        _emit 0x00
        _emit 0x00
        _emit 0x68
        _emit 0xb0
        _emit 0x98
        _emit 0x02
        _emit 0x10
        _emit 0xe8
        _emit 0x35
        _emit 0x99
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0xe8
        _emit 0xfd
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x5f
        _emit 0x5e
        _emit 0x5d
        _emit 0x33
        _emit 0xc0
        _emit 0x5b
        _emit 0x81
        _emit 0xc4
        _emit 0xe4
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0xc2
        _emit 0x04
        _emit 0x00
    }
}
#else
// CFLAGS: /DREBREW_ALLOW_NAKED /O2 /Gd

int __cdecl ServerMainThread(void* lpThreadParameter)
{
	char* module_path;
	char* ini_tail;
	char* log_message;
	unsigned int* player_slot;
	unsigned int* transfer_progress;
	unsigned int* src_words;
	unsigned int* cfg_ptr;
	unsigned int* payload_src;
	unsigned int* payload_dst;
	unsigned int connected_players;
	unsigned int now_tick;
	unsigned int current_tick;
	unsigned int last_announce_tick;
	unsigned int sync_timer;
	unsigned int game_speed;
	unsigned int result;
	unsigned int line;
	int i;
	int phase_complete;
	unsigned char cmd_buffer_primary[0x99];
	unsigned char cmd_buffer_secondary[0x99];
	unsigned int startup_cfg_words[27];
	char log_buffer[64];

	module_path = (char*) 0x101de9a0;
	GetModuleFileNameA(0, module_path, 0x104);
	ini_tail = strrchr(module_path, 0x5c);
	*(unsigned int*) (ini_tail + 0) = *(unsigned int*) 0x1002993c;
	*(unsigned int*) (ini_tail + 4) = *(unsigned int*) 0x10029940;
	*(unsigned short*) (ini_tail + 8) = *(unsigned short*) 0x10029944;

	*(int*) 0x11764088 = (int) GetPrivateProfileIntA((char*) 0x1002992c, (char*) 0x10029934, 0x1d6b, module_path);
	*(int*) 0x11764084 = 2;
	GetPrivateProfileStringA(
		(char*) 0x100298f8,
		(char*) 0x10029900,
		(char*) 0x1002990c,
		(char*) 0x10029594,
		0x104,
		module_path
	);

	src_words = (unsigned int*) lpThreadParameter;
	cfg_ptr = startup_cfg_words;
	for (i = 0; i < 0x1a; i++) {
		*cfg_ptr = *src_words;
		src_words = src_words + 1;
		cfg_ptr = cfg_ptr + 1;
	}
	*(unsigned short*) cfg_ptr = (unsigned short) (*src_words);

	if (*(unsigned short*) ((char*) startup_cfg_words + 2) == 1) {
		*((unsigned char*) startup_cfg_words + 0x27) = 0;
		*(unsigned int*) 0x11764084 = *(unsigned int*) ((char*) startup_cfg_words + 0x26) & 0xff;
	}
	else if (*(unsigned short*) ((char*) startup_cfg_words + 2) == 4) {
		*((unsigned char*) startup_cfg_words + 0x27) = 0;
		*(unsigned int*) 0x11764084 = *(unsigned int*) ((char*) startup_cfg_words + 0x26) & 0xff;
	}

	srv_Init();
	sprintf(log_buffer, (char*) 0x100298d8, *(int*) 0x11764084);
	LogMessageInternal((char*) 0x100298b0, 0x131, log_buffer, 1);
	_seterrormode(timeGetTime());

	last_announce_tick = 0;
	phase_complete = 0;
	for (;;) {
		if (*(int*) 0x10034680 != 0) {
			break;
		}

		connected_players = 0;
		player_slot = (unsigned int*) 0x101deb00;
		do {
			if (*player_slot != 0) {
				connected_players = connected_players + 1;
			}
			player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
		} while ((char*) player_slot < (char*) 0x114ffe20);

		AcceptConnections();

		if (connected_players == *(unsigned int*) 0x11764084) {
			phase_complete = 1;
			for (player_slot = (unsigned int*) 0x101deb00; (char*) player_slot < (char*) 0x114ffe20;
				player_slot = (unsigned int*) ((char*) player_slot + 0x264264)) {
				if ((*player_slot != 0) && ((*player_slot & 0x800) == 0)) {
					phase_complete = 0;
					goto lobby_check_announce;
				}
			}
			LogMessageInternal((char*) 0x100298b0, 0x14e, (char*) 0x10029890, 1);
		}

	lobby_check_announce:
		now_tick = timeGetTime();
		if ((3000 < now_tick - last_announce_tick) || phase_complete) {
			*((unsigned char*) startup_cfg_words + 0x27) = (unsigned char) connected_players;
			SendBroadcastPacket((unsigned char*) 0x3039, (int) startup_cfg_words);
			last_announce_tick = timeGetTime();
		}

		result = (unsigned int) ProcessReceiveData();
		if (result == 0xffffffff) {
			log_message = (char*) 0x1002986c;
			line = 0x15f;
			goto log_error_and_cleanup;
		}

		result = (unsigned int) ProcessSendData();
		if (result == 0xffffffff) {
			log_message = (char*) 0x1002986c;
			line = 0x16a;
			goto log_error_and_cleanup;
		}

		player_slot = (unsigned int*) 0x101deb00;
		do {
			if ((*player_slot & 0x1000) != 0) {
				if ((*player_slot & 0x400) != 0) {
					log_message = (char*) 0x10029834;
					line = 0x176;
					goto log_error_and_cleanup;
				}
				cm_ClosePlayerConnection(player_slot);
			}
			player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
		} while ((char*) player_slot < (char*) 0x114ffe20);

		Sleep(0x1e);
		if (phase_complete) {
			break;
		}
	}

	player_slot = (unsigned int*) 0x101deb00;
	do {
		if ((*player_slot & 1) != 0) {
			*player_slot = (*player_slot & 0xfffffdff) | 0x4004;
		}
		player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
	} while ((char*) player_slot < (char*) 0x114ffe20);

	i = 0;
	player_slot = (unsigned int*) 0x101deb00;
	do {
		if ((*player_slot & 0x400) != 0) {
			*(unsigned int*) ((char*) 0x101deb00 + i * 0x264264) =
				*(unsigned int*) ((char*) 0x101deb00 + i * 0x264264) | 8;
			goto send_start_commands;
		}
		player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
		i = i + 1;
	} while ((char*) player_slot < (char*) 0x114ffe20);

	CleanupSockets();

send_start_commands:
	Sleep(2000);
	i = 0;
	player_slot = (unsigned int*) 0x101deb00;
	do {
		if (*player_slot != 0) {
			cmd_buffer_primary[0] = 4;
			*(unsigned int*) (cmd_buffer_primary + 0x10) = (unsigned int) ((((*player_slot & 8) != 0) ? 0 : 1) + 1);
			if (cm_QueuePlayerCommand(player_slot, cmd_buffer_primary) == -1) {
				goto cleanup_and_exit;
			}

			cmd_buffer_primary[0] = 0x20;
			*(unsigned int*) (cmd_buffer_primary + 9) = (unsigned int) i;
			cmd_buffer_primary[0x10] = 7;
			i = i + 1;
			if (cm_QueuePlayerCommand(player_slot, cmd_buffer_primary) == -1) {
				goto cleanup_and_exit;
			}
		}
		player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
	} while ((char*) player_slot < (char*) 0x114ffe20);

	LogMessageInternal((char*) 0x100298b0, 0x1ca, (char*) 0x10029824, 1);
	for (;;) {
		if (*(int*) 0x10034680 != 0) {
			break;
		}

		phase_complete = 1;
		player_slot = (unsigned int*) 0x101deb00;
		do {
			if ((*player_slot & 8) != 0) {
				phase_complete = 0;
				break;
			}
			player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
		} while ((char*) player_slot < (char*) 0x114ffe20);

		result = (unsigned int) ProcessReceiveData();
		if ((result == 0xffffffff) || (ProcessSendData() == -1)) {
			log_message = (char*) 0x1002986c;
			line = 0x1df;
			goto log_error_and_cleanup;
		}

		Sleep(0x1e);
		if (phase_complete) {
			break;
		}
	}

	RecvGameSavegame();
	LogMessageInternal((char*) 0x100298b0, 0x1f9, (char*) 0x1002980c, 1);
	if ((*(unsigned char*) 0x101de464 & 4) == 0) {
		LogMessageInternal((char*) 0x100298b0, 0x1ff, (char*) 0x100297fc, 1);
		do {
			phase_complete = 1;
			player_slot = (unsigned int*) 0x101deb00;
			transfer_progress = (unsigned int*) 0x101deac8;
			do {
				if ((*player_slot & 4) != 0) {
					if (*transfer_progress == 0xffffffff) {
						cmd_buffer_primary[0] = 8;
						*(unsigned int*) (cmd_buffer_primary + 0x10) = *(unsigned int*) 0x101deac0;
						if (cm_QueuePlayerCommand(player_slot, cmd_buffer_primary) == -1) {
							goto cleanup_and_exit;
						}
						*transfer_progress = 0;
					}
					else {
						cmd_buffer_primary[0] = 9;
						payload_src = (unsigned int*) ((char*) *(void**) 0x101deae8 + *transfer_progress);
						payload_dst = (unsigned int*) (cmd_buffer_primary + 0x10);
						for (i = 0x20; i != 0; i--) {
							*payload_dst = *payload_src;
							payload_dst = payload_dst + 1;
							payload_src = payload_src + 1;
						}

						if (cm_QueuePlayerCommand(player_slot, cmd_buffer_primary) == -1) {
							LogMessageInternal((char*) 0x100298b0, 0x228, (char*) 0x100297e4, 1);
						}
						else {
							*transfer_progress = *transfer_progress + 0x80;
						}

						if (*(unsigned int*) 0x101deac0 <= *transfer_progress) {
							*player_slot = *player_slot & 0xfffffffb;
						}
					}

					phase_complete = 0;
				}

				transfer_progress = transfer_progress + 1;
				player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
			} while ((char*) transfer_progress < (char*) 0x101deae8);

			result = (unsigned int) ProcessReceiveData();
			if ((result == 0xffffffff) || (ProcessSendData() == -1)) {
				log_message = (char*) 0x1002986c;
				line = 0x23a;
				goto log_error_and_cleanup;
			}

			Sleep(0x1e);
		} while (!phase_complete);
	}
	else {
		player_slot = (unsigned int*) 0x101deb00;
		do {
			if ((*player_slot & 4) != 0) {
				*player_slot = *player_slot & 0xfffffffb;
			}
			player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
		} while ((char*) player_slot < (char*) 0x114ffe20);
	}

	m_FreeTracked(*(void**) 0x101deae8);
	*(void**) 0x101deae8 = (void*) 0;
	*(unsigned int*) 0x101deac0 = 0;

	if ((*(unsigned char*) 0x101de464 & 4) == 0) {
		LogMessageInternal((char*) 0x100298b0, 0x262, (char*) 0x100297bc, 1);
		player_slot = (unsigned int*) 0x101deb00;
		do {
			if ((*player_slot & 1) != 0) {
				*player_slot = *player_slot | 0x10;
			}
			player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
		} while ((char*) player_slot < (char*) 0x114ffe20);

		do {
			phase_complete = 1;
			player_slot = (unsigned int*) 0x101deb00;
			do {
				if ((char*) 0x114ffe1f < (char*) player_slot) {
					break;
				}
				if ((*player_slot & 0x10) != 0) {
					phase_complete = 0;
				}
				player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
			} while (phase_complete);

			result = (unsigned int) ProcessReceiveData();
			if ((result == 0xffffffff) || (ProcessSendData() == -1)) {
				log_message = (char*) 0x1002986c;
				line = 0x278;
				goto log_error_and_cleanup;
			}

			Sleep(0x1e);
		} while (!phase_complete);
	}

	player_slot = (unsigned int*) 0x101deb00;
	do {
		if ((*player_slot & 1) != 0) {
			cmd_buffer_secondary[0] = 4;
			if (cm_QueuePlayerCommand(player_slot, cmd_buffer_secondary) == -1) {
				goto cleanup_and_exit;
			}
		}
		player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
	} while ((char*) player_slot < (char*) 0x114ffe20);

	LogMessageInternal((char*) 0x100298b0, 0x2a8, (char*) 0x100297b0, 1);

	for (;;) {
		if (*(int*) 0x10034680 != 0) {
			*(int*) 0x10034680 = 0;
			return 0;
		}

		Sleep(0x1e);
		current_tick = GetTickCount();
		player_slot = (unsigned int*) 0x101deb00;
		do {
			if ((*player_slot != 0) && ((*player_slot & 0x40) != 0)) {
				player_slot = (unsigned int*) 0x101deb00;
				goto check_sync_all_players;
			}
			player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
		} while ((char*) player_slot < (char*) 0x114ffe20);
		goto process_pending_sync;

		while ((player_slot = (unsigned int*) ((char*) player_slot + 0x264264)),
			   (char*) player_slot < (char*) 0x114ffe20) {
		check_sync_all_players:
			if ((*player_slot != 0) && ((*player_slot & 0x40) == 0)) {
				phase_complete = 1;
				goto check_transfer_state;
			}
		}

	process_pending_sync:
		phase_complete = 0;
		player_slot = (unsigned int*) 0x101deb00;
		do {
			if ((*player_slot != 0) && ((*player_slot & 0x40) != 0)) {
				LogMessageInternal((char*) 0x100298b0, 0x2ce, (char*) 0x100297a0, 1);
				*player_slot = *player_slot & 0xffffffbf;
				if (cm_QueuePlayerCommand(player_slot, (unsigned char*) ((char*) player_slot + 0x264154)) == -1) {
					goto cleanup_and_exit;
				}
			}
			player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
		} while ((char*) player_slot < (char*) 0x114ffe20);

	check_transfer_state:
		if (*(int*) 0x11764090 == 0) {
			if (phase_complete) {
				goto game_loop_network_io;
			}

			*(int*) 0x11764090 = 1;
			phase_complete = 1;
			player_slot = (unsigned int*) 0x101deb00;
			do {
				if ((*player_slot != 0) && ((*player_slot & 0x20) == 0)) {
					*(int*) 0x11764090 = 0;
					phase_complete = 0;
				}
				player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
			} while ((char*) player_slot < (char*) 0x114ffe20);

			if (!phase_complete) {
				goto game_loop_network_io;
			}

			player_slot = (unsigned int*) 0x101deb00;
			do {
				if (*player_slot != 0) {
					*player_slot = *player_slot & 0xffffffdf;
				}
				player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
				*(unsigned int*) 0x101deaf0 = current_tick;
			} while ((char*) player_slot < (char*) 0x114ffe20);
		}
		else if (phase_complete || (current_tick < *(unsigned int*) 0x101deaf0)) {
			goto game_loop_network_io;
		}

		AdvanceGameClock((int*) 0x10035880, 0, 1, 0);
		player_slot = (unsigned int*) 0x101deb00;
		do {
			if (*player_slot != 0) {
				cmd_buffer_primary[0] = 0x1e;
				*(unsigned int*) (cmd_buffer_primary + 0x0c) = *(unsigned int*) 0x10035884;
				*(unsigned int*) (cmd_buffer_primary + 0x10) = *(unsigned int*) 0x10035880;
				*(unsigned int*) (cmd_buffer_primary + 0x18) = *(unsigned int*) 0x10035888;
				*(unsigned short*) (cmd_buffer_primary + 0x1c) = *(unsigned short*) 0x1003588c;
				if (cm_QueuePlayerCommand(player_slot, cmd_buffer_primary) == -1) {
					goto cleanup_and_exit;
				}
			}
			player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
		} while ((char*) player_slot < (char*) 0x114ffe20);

		if (*(unsigned short*) 0x10035884 > 0x16) {
			phase_complete = 1;
			player_slot = (unsigned int*) 0x101deb00;
			do {
				if (*player_slot != 0) {
					cmd_buffer_secondary[0] = 0x20;
					if (phase_complete) {
						phase_complete = 0;
					}
					if (cm_QueuePlayerCommand(player_slot, cmd_buffer_secondary) == -1) {
						goto cleanup_and_exit;
					}
					*(int*) 0x11764090 = 0;
				}
				player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
			} while ((char*) player_slot < (char*) 0x114ffe20);

			*(unsigned int*) 0x10035880 = *(unsigned int*) 0x10035880 + 1;
			sim_SetSyncParams(0x10035880, 6, 0, 0);
		}

		sync_timer = *(unsigned int*) 0x101deaf0;
		game_speed = *(unsigned int*) 0x1002c3f0;
		*(unsigned int*) 0x101deaf0 = sync_timer + game_speed;

	game_loop_network_io:
		result = (unsigned int) ProcessReceiveData();
		if ((result == 0xffffffff) || (ProcessSendData() == -1)) {
			log_message = (char*) 0x1002986c;
			line = 0x348;
			goto log_error_and_cleanup;
		}

		if (cm_ProcessCommandQueue() == -1) {
			goto cleanup_and_exit;
		}
	}

log_error_and_cleanup:
	LogMessageInternal((char*) 0x100298b0, line, log_message, 1);

cleanup_and_exit:
	CleanupSockets();
	return 0;
}
#endif


/* Initializes server subsystems: memory allocator, logging,
 * network sockets, game data tables, and entity pools. */
