/* Mode byte at Gold 0x5fbf78 has no canonical declaration. */
char __cdecl d3_FormatMeshAssetNames(char*, char*, int, char*, char*);
char* __cdecl d3_FindModelByName(char*);
char* __cdecl d3_LoadModelTemplate(char*, char*);

/* ADDRESS: GOLD 0x0044e190 */
char* __cdecl d3_AcquireModelTemplate(char* name, char* path)
{
    char first[256];
    char second[256];
    char* result;
    char* extra;
    int i;

    d3_FormatMeshAssetNames(name, path, 0, second, first);
    result = d3_FindModelByName(first);
    if (result == 0) {
        result = d3_FindModelByName(second);
        if (result == 0) {
            result = d3_LoadModelTemplate(second, first);
            if (result != 0) {
                ++*(int*) (result + 0x1dc);
            }
            if (d3_FormatMeshAssetNames(name, path, -1, second, first) != 0) {
                extra = d3_LoadModelTemplate(second, first);
                if (extra != 0) {
                    ++*(int*) (extra + 0x1dc);
                }
            }
            if ((*(unsigned int*) 0x5fbf78 & 0x7f) == 1) {
                for (i = 1; i < 3; i++) {
                    if (d3_FormatMeshAssetNames(name, path, i, second, first) != 0) {
                        extra = d3_LoadModelTemplate(second, first);
                        if (extra != 0) {
                            ++*(int*) (extra + 0x1dc);
                        }
                    }
                }
            }
        }
    }
    return result;
}
