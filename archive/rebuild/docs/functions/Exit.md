# Function: Exit

## Metadata

| Field | Value |
|-------|-------|
| **Export Name** | Exit |
| **Export Ordinal** | 1 |
| **Virtual Address** | 0x10009350 |
| **File Offset** | 0x00009350 |
| **Section** | .text |
| **Section Offset** | 0x00008350 |
| **Size** | 68 bytes (0x44) |
| **Calling Convention** | __stdcall (assumed) |

## Description

The `Exit` function is the second export from server.dll. It handles cleanup and shutdown of the server component. The function:

1. Checks if the server was initialized
2. If initialized, performs cleanup loop
3. Calls shutdown functions
4. Clears global state

## Disassembly

```asm
0x10009350:  a1 94 40 76 11        mov    eax, ds:0x11764094
0x10009355:  85 c0                 test   eax, eax
0x10009357:  74 3a                 je     0x10009393
0x10009359:  56                    push   esi
0x1000935a:  8b 35 58 40 02 10     mov    esi, DWORD PTR ds:0x10024058
0x10009360:  c7 05 80 46 03 10 01  mov    DWORD PTR ds:0x10034680, 0x1
0x10009367:  00 00 00 
0x1000936a:  6a 0a                 push   0xa
0x1000936c:  ff d6                 call   esi
0x1000936e:  a1 80 46 03 10        mov    eax, ds:0x10034680
0x10009373:  85 c0                 test   eax, eax
0x10009375:  75 f3                 jne    0x1000936a
0x10009377:  a1 94 40 76 11        mov    eax, ds:0x11764094
0x1000937c:  6a 00                 push   0x0
0x1000937e:  50                    push   eax
0x1000937f:  ff 15 54 40 02 10     call   DWORD PTR ds:0x10024054
0x10009385:  33 c0                 xor    eax, eax
0x10009387:  a3 94 40 76 11        mov    ds:0x11764094, eax
0x1000938c:  5e                    pop    esi
0x1000938d:  c3                    ret
0x1000938e:  90                    nop
0x1000938f:  90                    nop
0x10009390:  90                    nop
0x10009391:  90                    nop
0x10009392:  90                    nop
0x10009393:  ...
```

## Code Analysis

### Parameters
Unknown - no stack parameters accessed directly.

### Local Variables
- **ESI** - Saved register, used to hold function pointer

### Global Variables Accessed
- `0x11764094` - Server handle/state (set by Init)
- `0x10034680` - Control flag for shutdown loop
- `0x10024058` - IAT entry for imported function
- `0x10024054` - IAT entry for imported function

### Function Calls

1. **Indirect call via ESI (0x1000936c)**
   - ESI loaded from `0x10024058`
   - Called in a loop with parameter 0xa (10)
   - Likely `Sleep(10)` or similar delay function

2. **Indirect call via IAT (0x1000937f)**
   - Address: `0x10024054`
   - Parameters: 0, handle from 0x11764094
   - Likely `closesocket` or cleanup function

### Control Flow

```
Entry:
  Load server handle
  If zero (not initialized):
    Jump to exit
  
  Save ESI
  Load function pointer (likely Sleep)
  Set shutdown flag = 1
  
ShutdownLoop:
  Push 10 (milliseconds)
  Call Sleep function
  Check if shutdown flag still set
  If yes, loop again
  
Cleanup:
  Load server handle
  Push 0
  Push handle
  Call cleanup function (likely closesocket)
  
Finalize:
  Clear server handle to 0
  Restore ESI
  Return
```

### Key Logic

1. **Guard Check**: If Init was never called (handle is 0), return immediately
2. **Graceful Shutdown Loop**: Repeatedly calls a function (likely Sleep) while a flag is set
3. **Resource Cleanup**: Calls proper cleanup function with the server handle
4. **State Reset**: Clears the global handle to indicate "not initialized"

## Notes

- Function is 68 bytes
- Contains a loop for graceful shutdown (0x1000936a - 0x10009375)
- Uses two imported functions via IAT
- Properly saves/restores ESI (callee-saved register)
- Clears global state after cleanup to allow re-initialization

## Cross-References

- Called by: Unknown (external callers via export)
- Calls: 
  - Function at IAT offset 0x58 (via ESI) - likely Sleep
  - Function at IAT offset 0x54 - likely closesocket
- Data refs:
  - 0x11764094 (global handle)
  - 0x10034680 (control flag)

## Related Functions

- **Init**: Sets up the server handle that Exit cleans up

## Comparable C Code

Based on the assembly analysis, here is the equivalent C code:

```c
// Global variables
static HANDLE g_serverHandle = NULL;    // At 0x11764094
static volatile BOOL g_shutdownFlag = FALSE;  // At 0x10034680

// IAT function pointers
#define IAT_SLEEP_FUNC ((VOID (WINAPI*)(DWORD))0x10024058)
#define IAT_CLOSE_FUNC ((BOOL (WINAPI*)(HANDLE, DWORD))0x10024054)

/**
 * @brief Shutdown and cleanup the server
 * 
 * Performs graceful shutdown by:
 * 1. Checking if server was initialized
 * 2. Waiting for shutdown to complete (with Sleep loop)
 * 3. Closing the server handle
 * 4. Clearing global state
 */
__declspec(dllexport) VOID __stdcall Exit(VOID)
{
    HANDLE hServer;
    
    // Check if initialized
    hServer = g_serverHandle;
    if (hServer == NULL) {
        return;  // Not initialized, nothing to do
    }
    
    // Set shutdown flag to trigger graceful shutdown
    g_shutdownFlag = TRUE;
    
    // Wait loop - repeatedly sleep while shutdown is in progress
    // This gives worker threads time to finish
    while (g_shutdownFlag) {
        Sleep(10);  // 10 milliseconds
    }
    
    // Get handle again (may have been changed)
    hServer = g_serverHandle;
    
    // Close the server handle/resource
    // Parameter 0 might be exit code or flags
    CloseHandle(hServer);  // or closesocket(), TerminateThread(), etc.
    
    // Clear global state to allow re-initialization
    g_serverHandle = NULL;
    
    return;
}
```

### Simplified Version

```c
static HANDLE g_hServer = NULL;
static volatile BOOL g_bShuttingDown = FALSE;

VOID __stdcall Exit(VOID)
{
    if (g_hServer == NULL) {
        return;
    }
    
    // Signal shutdown
    g_bShuttingDown = TRUE;
    
    // Wait for graceful shutdown (10ms intervals)
    while (g_bShuttingDown) {
        Sleep(10);
    }
    
    // Cleanup
    CloseHandle(g_hServer);
    g_hServer = NULL;
}
```

## Assembly Source

See: `rebuild/asm/_exit.asm`
