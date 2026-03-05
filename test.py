import re

with open('src/server.dll/Units/vfs/vfs.c', 'r') as f:
    content = f.read()

# Fix fseek call
content = content.replace("fseek(*(FILE**) (param_1 + 4), *(int*) (iVar3 + 4), 0);", "fseek(*(FILE**) ((int)param_1 + 4), *(int*) (iVar3 + 4), 0);")
content = content.replace("fseek((FILE*)*param_1, *(int*) (iVar3 + 4), 0);", "fseek((FILE*)*param_1, *(int*) (iVar3 + 4), 0);")
content = re.sub(r"fseek\(\(FILE\*\)\*param_1, \*\(\w+\*\) \(iVar3 \+ 4\), 0\);", r"fseek((FILE*)*param_1, *(int*)(iVar3 + 4), 0);", content)

# Check line 336 directly to find exact shape
lines = content.split('\n')
for i, line in enumerate(lines):
    if 'fseek(' in line:
        # Cast first arg
        lines[i] = re.sub(r'fseek\(([^,]+),', r'fseek((FILE*)(\1),', line)
    if 'crt_locked_call4b(' in line:
        # Check if it has 4 args
        parts = line.split('crt_locked_call4b(')
        if len(parts) > 1:
            args = parts[1].split(',')
            if len(args) == 4:
                lines[i] = re.sub(r'crt_locked_call4b\(([^,]+),([^,]+),([^,]+),([^)]+)\)', 
                                  r'crt_locked_call4b((void*)(\1),\2,\3,(void*)(\4))', line)

content = '\n'.join(lines)
# Make sure we don't accidentally cast (FILE*) twice
content = content.replace("(FILE*)(FILE*)", "(FILE*)")
content = content.replace("(FILE*)((FILE*)", "(FILE*)(")

# Check ReadVfsDataChecked definition and declarations
content = content.replace("int __cdecl flush_stream(int param_1, int param_2)", "int __cdecl flush_stream(void* param_1, int param_2)")
content = content.replace("extern int __cdecl flush_stream(int, int);", "extern int __cdecl flush_stream(void*, int);")

content = content.replace("int __cdecl vfs_write(void* param_1, int param_2, int param_3)", "int __cdecl vfs_write(int* param_1, int param_2, int param_3)")

with open('src/server.dll/Units/vfs/vfs.c', 'w') as f:
    f.write(content)
