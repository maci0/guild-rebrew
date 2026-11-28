void __cdecl vfs_ReadByte(void* a, void* b);

/* ADDRESS: GOLDTL 0x004011a0 */
/* ADDRESS: GOLDDE 0x004011a0 */
void __cdecl vfs_ReadCString(void* a0, char* text)
{
    char* cursor;

    cursor = text - 1;
    do {
        vfs_ReadByte(a0, cursor + 1);
        cursor = cursor + 1;
    } while (*cursor != 0);
}
