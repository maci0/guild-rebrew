#!/usr/bin/env python3
"""Push game struct definitions to Ghidra via ReVa MCP.

Defines the core game data structures discovered through offset analysis
and pushes them to Ghidra's /rebrew DTM category via parse-c-structure.
"""

import json
import sys

import httpx

ENDPOINT = "http://localhost:8080/mcp/message"
PROGRAM = "/server.dll"
CATEGORY = "/rebrew"

STRUCTS = {
    "EntityStruct": """
#pragma pack(1)
typedef struct EntityStruct {
    unsigned short entity_type;
    unsigned char entity_class;
    unsigned char pad03;
    int id;
    char field_08;
    char pad09[3];
    char sub_type;
    char pad0d;
    int quantity;
    char status_flags;
    char pad13[9];
    int slot_state;
    char pad20[2];
    char field_22;
    char pad23[4];
    unsigned short parent_index;
    char pad29[3];
    int timestamp;
    char pad30[9];
    int position_data;
    char pad3d[29];
    short field_5a;
    char morale;
    int linked_list_head;
    char pad61[4];
    unsigned char count_level;
    char pad66[11];
    int building_ref;
    char pad75[11];
    int field_80;
    char pad84[21];
    int position_block[4];
    char pada9[187];
    char role_byte;
    char secondary_role;
    unsigned char office_type;
    char field_167;
    unsigned char office_rank;
    unsigned char office_flags;
    char pad16a[2];
    int employer_entity;
    int previous_worker;
    int work_state;
    int container_list;
    char pad17c[8];
    int bool_flag;
    char pad188[4];
    int field_18c;
    char pad190[8];
    int resource_counter;
    int production_counter;
    int material_counter;
    int product_counter;
    char pad1a8[12];
    int position_block2[4];
    char pad1c4[4];
    int office_holder;
    int permission_flags;
    char pad1d0[60];
    int owner_ref;
    char pad210[12];
} EntityStruct;
#pragma pack()
""",
    "BuildingPrototype": """
#pragma pack(1)
typedef struct BuildingPrototype {
    unsigned char type_byte;
    char pad01[34];
    char component_list;
    char pad24[547];
    unsigned char stat_count_lo;
    unsigned char stat_count_hi;
    char pad249[4];
} BuildingPrototype;
#pragma pack()
""",
    "ObjectPrototype": """
#pragma pack(1)
typedef struct ObjectPrototype {
    unsigned char item_category;     /* 0x00 - item category: 0x17, 0x25 = special */
    char pad01[35];                  /* 0x01 */
    unsigned char recipe_type;       /* 0x24 */
    char pad25[17];                  /* 0x25 */
    unsigned short base_quantity;    /* 0x36 - base production quantity */
    char pad38[9];                   /* 0x38 */
} ObjectPrototype;
#pragma pack()
""",
    "SeasonSlot": """
#pragma pack(1)
typedef struct SeasonSlot {
    char pad00[4];                   /* 0x00 */
    int owner_id;                    /* 0x04 - entity ID of owner */
    char pad08[8];                   /* 0x08 */
    int production_count;            /* 0x10 - production count, -1 = unused */
    char pad14[4];                   /* 0x14 */
    int material_count;              /* 0x18 - material count */
    int product_count;               /* 0x1c - product count */
    char pad20[4];                   /* 0x20 */
    int xp_gained;                   /* 0x24 - experience gained */
    char pad28[37];                  /* 0x28 */
    int total_xp;                    /* 0x4d - total XP accumulated */
} SeasonSlot;
#pragma pack()
""",
    "QueryResult": """
#pragma pack(1)
typedef struct QueryResult {
    char pad00[14];                  /* 0x00 */
    int count;                       /* 0x0e - result count */
    char pad12[2];                   /* 0x12 */
    int entity_id;                   /* 0x14 - first entity ID */
    char pad18[4];                   /* 0x18 */
    int entries[1];                  /* 0x1c - variable-length entity ID array */
} QueryResult;
#pragma pack()
""",
}


def init_session(client):
    resp = client.post(
        ENDPOINT,
        json={
            "jsonrpc": "2.0",
            "id": 0,
            "method": "initialize",
            "params": {
                "protocolVersion": "2025-03-26",
                "capabilities": {},
                "clientInfo": {"name": "rebrew-structs", "version": "1.0"},
            },
        },
        headers={
            "Content-Type": "application/json",
            "Accept": "application/json, text/event-stream",
        },
        timeout=15,
    )
    sid = resp.headers.get("Mcp-Session-Id", "")
    if not sid:
        print("ERROR: No session ID")
        sys.exit(1)
    return sid


def call_tool(client, sid, tool_name, arguments, req_id):
    headers = {
        "Content-Type": "application/json",
        "Accept": "application/json, text/event-stream",
        "Mcp-Session-Id": sid,
    }
    resp = client.post(
        ENDPOINT,
        json={
            "jsonrpc": "2.0",
            "id": req_id,
            "method": "tools/call",
            "params": {"name": tool_name, "arguments": arguments},
        },
        headers=headers,
        timeout=60,
    )
    for line in resp.text.split("\n"):
        if line.startswith("data: "):
            data = json.loads(line[6:])
            if "result" in data:
                content = data["result"].get("content", [])
                if content:
                    return content[0].get("text", ""), False
            if "error" in data:
                return data["error"].get("message", str(data["error"])), True
    try:
        data = json.loads(resp.text)
        if "result" in data:
            content = data["result"].get("content", [])
            if content:
                return content[0].get("text", ""), False
        if "error" in data:
            return data["error"].get("message", str(data["error"])), True
    except json.JSONDecodeError:
        pass
    return resp.text[:200], True


def main():
    with httpx.Client(timeout=60.0) as client:
        sid = init_session(client)
        print(f"Session: {sid}")

        req_id = 1
        ok_count = 0
        fail_count = 0

        for name, c_code in STRUCTS.items():
            result, is_err = call_tool(
                client,
                sid,
                "parse-c-structure",
                {
                    "programPath": PROGRAM,
                    "cDefinition": c_code.strip(),
                    "category": CATEGORY,
                },
                req_id,
            )
            req_id += 1
            if is_err:
                print(f"  FAIL {name}: {result[:120]}")
                fail_count += 1
            else:
                print(f"  OK   {name}")
                ok_count += 1

        print(f"\nDone: {ok_count} OK, {fail_count} FAIL")


if __name__ == "__main__":
    main()
