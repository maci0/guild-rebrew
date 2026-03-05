import re

# Fix vfs.c one last time
with open('src/server.dll/Units/vfs/vfs.c', 'r') as f:
    content = f.read()

# Fix 167 (compress_block 2nd param cast)
content = content.replace("compress_block((void*)param_1, (char*)param_2);",
                          "compress_block((void*)param_1, (int)param_2);")

# Fix 336
content = content.replace("fseek(*(FILE**) (param_1 + 4), *(int*) (iVar3 + 4), 0);",
                          "fseek(*(int*) (param_1 + 4), *(int*) (iVar3 + 4), 0);")
content = content.replace("fseek(*(int*) (param_1 + 4),",
                          "fseek((FILE*)*(int*) (param_1 + 4),")

# Fix 617
content = content.replace("crt_locked_call4b(*(void**) (param_1 + 4), 1, param_3, *(void**) (param_1 + 0x40));",
                          "crt_locked_call4b(*(int*) (param_1 + 4), 1, param_3, *(int*) (param_1 + 0x40));")
content = content.replace("crt_locked_call4b(*(int*) (param_1 + 4), 1, param_3, *(int*) (param_1 + 0x40));",
                          "crt_locked_call4b((void*)*(int*) (param_1 + 4), 1, param_3, (void*)*(int*) (param_1 + 0x40));")

with open('src/server.dll/Units/vfs/vfs.c', 'w') as f:
    f.write(content)

