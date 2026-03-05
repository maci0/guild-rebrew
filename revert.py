import re

with open('src/server.dll/Units/vfs/vfs.c', 'r') as f:
    content = f.read()

# Fix everything back to int
content = content.replace("extern int __cdecl flush_stream(void*, int);", "extern int __cdecl flush_stream(int, int);")
content = content.replace("int __cdecl flush_stream(void* param_1, int param_2)", "int __cdecl flush_stream(int param_1, int param_2)")

content = content.replace("extern int __cdecl compress_block(int, int);", "extern int __cdecl compress_block(void* param_1, char* param_2, char* param_3, int param_4);")

content = content.replace("write_result = compress_block((void*)obj, (char*)out_buf, (char*)in_buf, size);", "write_result = compress_block((void*)obj, (char*)out_buf, (char*)in_buf, size);")

# VFS Write
content = content.replace("int __cdecl vfs_write(void* param_1, int param_2, int param_3)", "int __cdecl vfs_write(int* param_1, int param_2, int param_3)")

content = content.replace("extern int __cdecl close_stream(void*);", "extern int __cdecl close_stream(int);")
content = content.replace("int __cdecl close_stream(void* param_1)", "int __cdecl close_stream(int param_1)")

with open('src/server.dll/Units/vfs/vfs.c', 'w') as f:
    f.write(content)
