unsigned int __cdecl vfs_fwrite(void* buf, int size, int count, char* stream);

/* ADDRESS: GOLDTL 0x004b64b0 */
int __cdecl fcn_004b64b0(char* file)
{
    char* q;

    if (!file)
        return 0;
    if (vfs_fwrite((void*) 0x6a3440, 1, 1, file) == -1)
        return 0;
    for (q = (char*) 0x10069a8; q - 4 < (char*) 0x1007ba4; q += 0x24) {
        if (vfs_fwrite((void*) (q - 8), 4, 1, file) == -1)
            return 0;
        if (vfs_fwrite((void*) (q - 4), 4, 1, file) == -1)
            return 0;
        if (vfs_fwrite((void*) q, 0xe, 1, file) == -1)
            return 0;
        if (vfs_fwrite((void*) (q + 0x10), 4, 1, file) == -1)
            return 0;
        if (vfs_fwrite((void*) (q + 0x14), 4, 1, file) == -1)
            return 0;
        if (vfs_fwrite((void*) (q + 0x18), 1, 1, file) == -1)
            return 0;
    }
    return 1;
}
