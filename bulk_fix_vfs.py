import re

with open('src/server.dll/Units/vfs/vfs.c', 'r') as f:
    content = f.read()

# Fix compress_block mismatch 1
content = content.replace("write_result = compress_block((void*)obj, out_buf, in_buf, size);",
                          "write_result = compress_block(*(void**)(obj + 0x4c), &param_3, *(char**)(obj + 0x48), remaining);")
# Let's see how it's actually used
