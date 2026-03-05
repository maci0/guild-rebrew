import re

with open('src/server.dll/Units/vfs/vfs.c', 'r') as f:
    content = f.read()

# Fix locked_fwrite definition
content = re.sub(
    r'void __cdecl locked_fwrite\(int param_1, unsigned int param_2, int param_3, int param_4\)',
    r'void __cdecl locked_fwrite(void* param_1, unsigned int param_2, int param_3, void* param_4)',
    content
)

# Fix compress_block definition
content = re.sub(
    r'int __cdecl compress_block\(int param_1, char\* param_2, char\* param_3, int param_4\)',
    r'int __cdecl compress_block(void* param_1, char* param_2, char* param_3, int param_4)',
    content
)

# Fix vfs_write definition (line 287 likely)
content = re.sub(
    r'int __cdecl vfs_write\(int\* param_1, int param_2, int param_3\)',
    r'int __cdecl vfs_write(void* param_1, int param_2, int param_3)',
    content
)

# Replace remaining `fseek((FILE*)param_1[0],` if the param is not actually `param_1[0]`
content = content.replace("fseek((FILE*)param_1[0]", "fseek((FILE*)*param_1")

# Fix fseek call
content = re.sub(r'fseek\(\(FILE\*\)param_1\[0\],', r'fseek((FILE*)*param_1,', content)

with open('src/server.dll/Units/vfs/vfs.c', 'w') as f:
    f.write(content)
