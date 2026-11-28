int __cdecl vfs_ReadDword(void*, void*);

/* ADDRESS: GOLDTL 0x0044dc60 */
int __cdecl d3_ReadMatUOffset(int a1, char* p)
{
    return vfs_ReadDword((void*) a1,
        (void*) (*(int*) (p + 8) * 224 + *(int*) (p + 0x10) + 0xd4));
}
