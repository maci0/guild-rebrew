typedef unsigned long u32;

/*
 * Init target metadata
 * VA start: 0x10009320
 * VA end:   0x10009350
 * Size:     48 bytes
 *
 * Original disassembly:
 * 0x10009320: 8b 4c 24 04          mov    ecx, [esp+0x4]
 * 0x10009324: 8d 44 24 04          lea    eax, [esp+0x4]
 * 0x10009328: 50                   push   eax
 * 0x10009329: 6a 00                push   0
 * 0x1000932b: 51                   push   ecx
 * 0x1000932c: 68 a0 93 00 10       push   0x100093a0
 * 0x10009331: 6a 00                push   0
 * 0x10009333: 6a 00                push   0
 * 0x10009335: ff 15 50 40 02 10    call   dword ptr [0x10024050]
 * 0x1000933b: 33 d2                xor    edx, edx
 * 0x1000933d: a3 94 40 76 11       mov    dword ptr [0x11764094], eax
 * 0x10009342: 85 c0                test   eax, eax
 * 0x10009344: 0f 95 c2             setne  dl
 * 0x10009347: 8b c2                mov    eax, edx
 * 0x10009349: c3                   ret
 * 0x1000934a: 90 90 90 90 90 90    nop padding
 */

typedef u32 (__stdcall *init_target_t)(u32, u32, u32, u32, u32, u32);

#define srv_GameLoop 0x100093A0UL
#define THREAD_CREATE_RUN_IMMEDIATELY 0
#define CREATE_THREAD_SLOT (*(u32 *)0x10024050)
#define hGameServerThread (*(u32 *)0x11764094)

__declspec(dllexport) int __cdecl Init(void *serverInitParams)
{
    u32 result;
    result = ((init_target_t)CREATE_THREAD_SLOT)(
        0,
        0,
        srv_GameLoop,
        (u32)serverInitParams,
        THREAD_CREATE_RUN_IMMEDIATELY,
        (u32)&serverInitParams
    );
    hGameServerThread = result;
    return result != 0;
}
