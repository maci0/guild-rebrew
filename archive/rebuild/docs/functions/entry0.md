# Function: entry0 (DllMain)

## Metadata

| Field | Value |
|-------|-------|
| **Function Name** | entry0 (DllMain) |
| **Virtual Address** | 0x1001B9D4 |
| **File Offset** | 0x0001C9D4 |
| **Section** | .text |
| **Section Offset** | 0x0001A9D4 |
| **Size** | 157 bytes (0x9D) |
| **Calling Convention** | __stdcall |

## Description

The DLL entry point (DllMain) called by Windows loader. Handles:
- DLL_PROCESS_ATTACH (value 1)
- DLL_THREAD_ATTACH (value 2)
- DLL_THREAD_DETACH (value 3)
- DLL_PROCESS_DETACH (value 0)

## Disassembly

```asm
0x1001B9D4:  55                    push    ebp
0x1001B9D5:  8B EC                 mov     ebp, esp
0x1001B9D7:  53                    push    ebx
0x1001B9D8:  8B 5D 08              mov     ebx, [ebp+8]    ; hinstDLL
0x1001B9DB:  56                    push    esi
0x1001B9DC:  8B 75 0C              mov     esi, [ebp+0Ch]  ; fdwReason
0x1001B9DF:  57                    push    edi
0x1001B9E0:  8B 7D 10              mov     edi, [ebp+10h]  ; lpReserved
0x1001B9E3:  85 F6                 test    esi, esi
0x1001B9E5:  75 09                 jnz     short loc_1001B9F0
0x1001B9E7:  83 3D FC 54 03 10 00  cmp     dword ptr ds:[100354FCh], 0
0x1001B9EE:  EB 26                 jmp     short loc_1001BA16

loc_1001B9F0:
0x1001B9F0:  83 FE 01              cmp     esi, 1
0x1001B9F3:  74 05                 je      short loc_1001B9FA
0x1001B9F5:  83 FE 02              cmp     esi, 2
0x1001B9F8:  75 22                 jnz     short loc_1001BA1C

loc_1001B9FA:
0x1001B9FA:  A1 88 75 76 11        mov     eax, ds:dword_11767588
0x1001B9FF:  85 C0                 test    eax, eax
0x1001BA01:  74 09                 jz      short loc_1001BA0C
0x1001BA03:  57                    push    edi
0x1001BA04:  56                    push    esi
0x1001BA05:  53                    push    ebx
0x1001BA06:  FF D0                 call    eax
0x1001BA08:  85 C0                 test    eax, eax
0x1001BA0A:  74 0C                 jz      short loc_1001BA18

loc_1001BA0C:
0x1001BA0C:  57                    push    edi
0x1001BA0D:  56                    push    esi
0x1001BA0E:  53                    push    ebx
0x1001BA0F:  E8 E7 FE FF FF        call    sub_1001B8FB
0x1001BA14:  85 C0                 test    eax, eax

loc_1001BA16:
0x1001BA16:  75 04                 jnz     short loc_1001BA1C

loc_1001BA18:
0x1001BA18:  33 C0                 xor     eax, eax
0x1001BA1A:  EB 60                 jmp     short loc_1001BA7C

loc_1001BA1C:
; ... continues for 157 bytes total
```

## Code Analysis

### Parameters
- `[ebp+8]` (ebx) = hinstDLL - Module handle
- `[ebp+0Ch]` (esi) = fdwReason - Why called (0-3)
- `[ebp+10h]` (edi) = lpReserved - Reserved

### Local Variables
None - uses registers only.

### Global Variables Accessed
- `0x100354FC` - Flag for initialization
- `0x11767588` - Function pointer table

### Control Flow
1. Check fdwReason (esi)
2. If 0 (PROCESS_DETACH), check termination flag
3. If 1 or 2 (PROCESS_ATTACH/THREAD_ATTACH), call init functions
4. If 3 (THREAD_DETACH), handle cleanup
5. Return TRUE (1) for success, FALSE (0) for failure

### Function Calls
- `sub_1001B8FB` - Internal initialization function
- Function pointer at `0x11767588` - Custom handler

## Comparable C Code

```c
BOOL __stdcall DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
    // Check reason code
    switch (fdwReason) {
        case DLL_PROCESS_DETACH:  // 0
            if (g_terminationFlag != 0) {
                return TRUE;
            }
            // Fall through
            
        case DLL_PROCESS_ATTACH:  // 1
        case DLL_THREAD_ATTACH:   // 2
            // Call custom handler if set
            if (g_pCustomHandler != NULL) {
                if (!g_pCustomHandler(hinstDLL, fdwReason, lpReserved)) {
                    return FALSE;
                }
            }
            
            // Call internal initialization
            if (!InternalInit(hinstDLL, fdwReason, lpReserved)) {
                return FALSE;
            }
            return TRUE;
            
        case DLL_THREAD_DETACH:   // 3
        default:
            return TRUE;
    }
}
```

## Notes

- Standard DllMain structure
- Calls initialization functions on attach
- Returns FALSE if initialization fails
- Size: 157 bytes (0x9D)
- Important: This is the DLL entry point

## Cross-References

- Called by: Windows Loader
- Calls: sub_1001B8FB, function pointer at 0x11767588
- Data refs: 0x100354FC, 0x11767588

## Assembly Source

See: `rebuild/asm/_entry0.asm`
