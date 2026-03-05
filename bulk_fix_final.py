import re

# Fix vfs.c one last time
with open('src/server.dll/Units/vfs/vfs.c', 'r') as f:
    content = f.read()

# Fix 156
content = content.replace("locked_fwrite(*(int*) (param_1 + 0x48), 1, remaining, *(int*) (param_1 + 0x40));",
                          "locked_fwrite(*(void**) (param_1 + 0x48), 1, remaining, *(void**) (param_1 + 0x40));")

# Fix 167
content = content.replace("compress_block(param_1, param_2);",
                          "compress_block((void*)param_1, (char*)param_2);")

# Fix 336
content = content.replace("fseek(*(int*) (param_1 + 4), *(int*) (iVar3 + 4), 0);",
                          "fseek(*(FILE**) (param_1 + 4), *(int*) (iVar3 + 4), 0);")

# Fix 617
content = content.replace("crt_locked_call4b(*(int*) (param_1 + 4), 1, param_3, *(int*) (param_1 + 0x40));",
                          "crt_locked_call4b(*(void**) (param_1 + 4), 1, param_3, *(void**) (param_1 + 0x40));")

# The declarations for close_stream, WriteFileBufferLocked might also have issues
content = content.replace("int __cdecl flush_stream(int param_1, int param_2)", "unsigned int __cdecl flush_stream(int param_1, int param_2)")

with open('src/server.dll/Units/vfs/vfs.c', 'w') as f:
    f.write(content)

