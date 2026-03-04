import requests
import json
import uuid

data = {
    "data": """
    # server.dll (Europa 1400: The Guild) - System Architecture and Entity Management

    ## 1. Exports and Entry Points
    - **entry (0x1001b9d4)**: Standard DllMain entry point handling CRT initialization and process attach/detach notifications.
    - **Init (0x10009320)**: Exported function called by the host engine to initialize the game server thread. Creates the core ServerMainThread and returns the handle validity.
    - **Exit (0x10009350)**: Exported function called by the host engine to shut down the server thread. Sets a global shutdown flag, waits briefly, then forcefully terminates if necessary.

    ## 2. Infrastructure and Utilities
    - **Memory Tracking**: The server uses a custom tracked heap allocator (`AllocateTrackedHeapBlock` 0x10006580, `FreeTrackedHeapBlock` 0x10006820). It groups allocations by a string `groupTag` (usually the source filename like "D:\\Develop\\Units\\m_alloc\\m_alloc.c") and tracks counts and sizes in `DAT_10034640`. Prevents memory leaks and underflows with explicit tracking.
    - **Logging System**: Handled by `DispatchLogOutput` (0x10002640). Depending on a bitmask (`_g_log_mode_flags`), it writes to a file (looking up the severity string name from `g_severity_table` to write to `__server.log` or `gilde_server.log`), OutputDebugStringA (debugger), or WriteConsoleA (Win32 Console).
    - **Virtual File System (VFS)**: Handled by `ReadVfsData` (0x10008e40). Supports standard file reads, raw memory buffer reading, and transparent gzip decompression utilizing zlib state machines.

    ## 3. Entity Management System
    The server manages game objects across three distinct global arrays/pools. Every newly allocated entity receives a monotonically increasing ID from `g_next_global_entity_id` (`DAT_10030b6c`), which starts at 1.
    
    1. **Static Entities Array (DAT_100358a0)**: Stores buildings and static world structures. Array of 0x300 (768) elements. Stride length 0x10e bytes.
    2. **Dynamic Entities Array (DAT_1014d8c0)**: Stores dynamic characters and players. Array of 0x100 (256) elements. Stride length 0xa9 bytes.
    3. **Existing Objects Array (DAT_100a8c34)**: Massive general-purpose item/object pool. Array of 0x5007 (20487) slots. Stride length 0x43 bytes. Managed by the low-level allocator `AllocateObjectSlot` (0x100165a0).

    ### Entity Resolution and Allocation
    - **ResolveEntityById (0x10015e90)**: Central routing function. Given an `entity_id` (often from a network packet), it searches all three global arrays (Dynamic, Existing, Static) and returns 1, 2, or 3 respectively, along with the correct memory pointer.
    - **AllocGameObject (0x10016760)**: High-level entity allocation wrapper. Resolves the `parent_id` via `ResolveEntityById` to find the correct entity list head. Allocates a new generic object slot, inserts it into the parent's linked list, and initializes core fields (type, global ID, parent pointers).
    - Specific command handlers map directly to entity creation, e.g., `validate_cmd_10_AllocPlayer` (0x1000d570) creates players in the dynamic array, and `0x1000bdf0` creates buildings/alchemist objects.
    """
}

# The endpoint for the Cognee MCP server running locally
url = "http://localhost:8000/messages"

payload = {
    "jsonrpc": "2.0",
    "id": 1,
    "method": "tools/call",
    "params": {
        "name": "cognee_cognify",
        "arguments": {
            "data": data["data"]
        }
    }
}

try:
    response = requests.post(url, json=payload, timeout=10)
    print("Status Code:", response.status_code)
    print("Response:", response.text)
except Exception as e:
    print(f"Failed to post to MCP: {e}")

