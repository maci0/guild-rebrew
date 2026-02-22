# Function: Init

## Metadata

| Field | Value |
|-------|-------|
| **Export Name** | Init |
| **Export Ordinal** | 2 |
| **Virtual Address** | 0x10009320 |
| **File Offset** | 0x00009320 |
| **Section** | .text |
| **Section Offset** | 0x00008320 |
| **Size** | 48 bytes (0x30) |
| **Calling Convention** | __stdcall (assumed) |

## Description

The `Init` function is one of two exports from server.dll. Based on its name and structure, this function initializes the server component. It appears to:

1. Set up some initialization parameters
2. Call a Winsock function (likely `WSAStartup` or `socket` creation)
3. Store the result in a global variable
4. Return success/failure status

## Disassembly

```asm
0x10009320:  8b 4c 24 04           mov    ecx, DWORD PTR [esp+0x4]
0x10009324:  8d 44 24 04           lea    eax, [esp+0x4]
0x10009328:  50                    push   eax
0x10009329:  6a 00                 push   0x0
0x1000932b:  51                    push   ecx
0x1000932c:  68 a0 93 00 10        push   0x100093a0
0x10009331:  6a 00                 push   0x0
0x10009333:  6a 00                 push   0x0
0x10009335:  ff 15 50 40 02 10     call   DWORD PTR ds:0x10024050
0x1000933b:  33 d2                 xor    edx, edx
0x1000933d:  a3 94 40 76 11        mov    ds:0x11764094, eax
0x10009342:  85 c0                 test   eax, eax
0x10009344:  0f 95 c2              setne  dl
0x10009347:  8b c2                 mov    eax, edx
0x10009349:  c3                    ret
0x1000934a:  90                    nop
0x1000934b:  90                    nop
0x1000934c:  90                    nop
0x1000934d:  90                    nop
0x1000934e:  90                    nop
0x1000934f:  90                    nop
```

## Code Analysis

### Parameters
The function takes at least one parameter from `[esp+0x4]` (standard __stdcall convention with return address at `[esp]`).

### Local Variables
None apparent - uses registers only.

### Global Variables Accessed
- `0x11764094` - Stores the result of the function call (likely a socket handle or status)

### Function Calls
- **Indirect call** via `0x10024050` - This is in the IAT (Import Address Table)
  - IAT offset: 0x10024050 corresponds to entry at offset 0x50 in IAT
  - Based on imports analysis, this is likely `CreateThread` or a Winsock function

### Control Flow
1. Load parameter from stack into ECX
2. Load address of parameter into EAX
3. Push arguments for function call (6 pushes total)
4. Call function via IAT
5. Store result in global variable at 0x11764094
6. Set return value based on success (non-zero = success)
7. Return

### Return Value
- Returns 1 (true) if the called function succeeded (EAX != 0)
- Returns 0 (false) if the called function failed (EAX == 0)

## Notes

- The function is 48 bytes with padding
- 6 NOPs at the end for alignment
- The call at 0x10009335 goes to the IAT, suggesting this is an imported function
- The pattern suggests network/socket initialization
- Address 0x100093a0 pushed as parameter is a pointer to data in .text section (likely a string or structure)

## Cross-References

- Called by: Unknown (external callers via export)
- Calls: Function at IAT offset 0x50
- Data refs: 0x100093a0 (parameter), 0x11764094 (global)

## Comparable C Code

Based on the assembly analysis, here is the equivalent C code:

```c
// Global variable (at 0x11764094)
static HANDLE g_serverHandle = NULL;

// Function pointer type for the imported function
// (likely CreateThread or WSAStartup based on parameters)
typedef DWORD (*InitFuncPtr)(DWORD param1, DWORD param2, LPCSTR param3, 
                              DWORD param4, DWORD param5);

// IAT entry at 0x10024050
#define IAT_INIT_FUNC ((InitFuncPtr*)0x10024050)

/**
 * @brief Initialize the server component
 * 
 * @param param Some initialization parameter from caller
 * @return BOOL TRUE on success, FALSE on failure
 */
__declspec(dllexport) BOOL __stdcall Init(LPVOID param)
{
    DWORD result;
    BOOL success;
    
    // Call the imported initialization function
    // 6 parameters pushed: 0, 0, param, string_ptr, 0, 0
    result = (*IAT_INIT_FUNC)(0, 0, (LPCSTR)param, 0x100093a0, 0, 0);
    
    // Store result in global variable
    g_serverHandle = (HANDLE)result;
    
    // Return TRUE if non-zero, FALSE otherwise
    success = (result != 0);
    
    return success;
}
```

### Simplified Version

A more practical interpretation:

```c
static HANDLE g_hServer = NULL;

BOOL __stdcall Init(LPVOID lpParam)
{
    // Create a thread or initialize network
    // Parameter 0x100093a0 points to a string "SERVER" or thread function
    HANDLE hResult = CreateThread(
        NULL,           // default security
        0,              // default stack size  
        (LPTHREAD_START_ROUTINE)0x100093a0,  // thread function
        lpParam,        // parameter
        0,              // creation flags
        NULL            // thread ID
    );
    
    g_hServer = hResult;
    return (hResult != NULL);
}
```

## Assembly Source

See: `rebuild/asm/_init.asm`
