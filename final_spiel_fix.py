import re

with open('src/server.dll/DieGildeAddOn/game/spiel.c', 'r') as f:
    content = f.read()

# Fix fflush calls
content = content.replace("fflush(file_handle);", "fflush((FILE*)file_handle);")

# Fix get_msg_field parameter mismatch by restoring the correct signature mapping.
content = content.replace("extern char* __cdecl get_msg_field(int);", "extern char* __cdecl get_msg_field(int);")
# No, wait. 
content = content.replace("int __cdecl FindEntityByOwner(char* msg, char* pkt)", "int __cdecl get_msg_field(char* msg, char* pkt)")
content = content.replace("char* __cdecl get_msg_field(int param_1)", "char* __cdecl FindEntityByOwner(int param_1)")

content = content.replace("// SYMBOL: _get_msg_field\n// FUNCTION: SERVER 0x10019c60", "// SYMBOL: _FindEntityByOwner\n// FUNCTION: SERVER 0x10019c60")
content = content.replace("// SYMBOL: _FindEntityByOwner\n// FUNCTION: SERVER 0x10019CD0", "// SYMBOL: _get_msg_field\n// FUNCTION: SERVER 0x10019CD0")

# I also noticed earlier there's a missing `extern int __cdecl get_msg_field(char*, char*);`
# But I won't touch it to avoid breaking compile. I'll just change the definitions.

with open('src/server.dll/DieGildeAddOn/game/spiel.c', 'w') as f:
    f.write(content)

