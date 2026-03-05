import re

with open('src/server.dll/DieGildeAddOn/game/spiel.c', 'r') as f:
    content = f.read()

# Fix the conflicting definitions of FindEntityByOwner and get_msg_field
content = content.replace("char* __cdecl FindEntityByOwner(int param_1)", "int __cdecl FindEntityByOwner(int param_1)")
content = content.replace("int __cdecl get_msg_field(char* msg, char* pkt)", "int __cdecl get_msg_field(int msg, int pkt)")

with open('src/server.dll/DieGildeAddOn/game/spiel.c', 'w') as f:
    f.write(content)

