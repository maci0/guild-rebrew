typedef unsigned long u32;

#ifndef _MSC_VER
#ifndef __declspec
#define __declspec(x)
#endif
#endif

typedef u32 (__stdcall *sleep_fn_t)(u32);
typedef u32 (__stdcall *close_fn_t)(u32, u32);
typedef u32 (__stdcall *post_fn_t)(u32);

/*
 * Exit target metadata
 * VA start: 0x10009350
 * VA end:   0x10009394
 * Size:     68 bytes
 *
 * Original disassembly:
 * a1 94 40 76 11    mov eax,[0x11764094]
 * 85 c0             test eax,eax
 * 74 3a             je +0x3a
 * 56                push esi
 * 8b 35 58 40 02 10 mov esi,[0x10024058]
 * c7 05 80 46 03 10 01 00 00 00 mov dword [0x10034680],1
 * 6a 0a             push 0x0a
 * ff d6             call esi
 * a1 80 46 03 10    mov eax,[0x10034680]
 * 85 c0             test eax,eax
 * 75 f3             jne loop
 * a1 94 40 76 11    mov eax,[0x11764094]
 * 6a 00             push 0
 * 50                push eax
 * ff 15 54 40 02 10 call dword [0x10024054]
 * 8b 0d 94 40 76 11 mov ecx,[0x11764094]
 * 51                push ecx
 * ff 15 10 40 02 10 call dword [0x10024010]
 * 5e                pop esi
 * c3                ret
 */

#define G_SERVER_HANDLE (*(u32 *)0x11764094)
#define G_SHUTDOWN_FLAG (*(u32 *)0x10034680)
#define P_SLEEP_SLOT (*(u32 *)0x10024058)
#define P_CLOSE_SLOT (*(u32 *)0x10024054)
#define P_POST_SLOT (*(u32 *)0x10024010)

// FUNCTION: SERVER 0x10009350
__declspec(dllexport) void __cdecl Exit(void)
{
    u32 h;
    if (G_SERVER_HANDLE) {
        sleep_fn_t pSleep = (sleep_fn_t)P_SLEEP_SLOT;
        G_SHUTDOWN_FLAG = 1;
        do {
            pSleep(10);
        } while (G_SHUTDOWN_FLAG);

        h = G_SERVER_HANDLE;
        ((close_fn_t)P_CLOSE_SLOT)(h, 0);
        ((post_fn_t)P_POST_SLOT)(G_SERVER_HANDLE);
    }
}
