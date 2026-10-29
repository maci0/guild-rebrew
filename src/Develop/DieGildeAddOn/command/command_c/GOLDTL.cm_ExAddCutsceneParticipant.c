char* __cdecl fcn_004e6a30(int id);
int __cdecl fcn_004e6b70(int id, int participant);

/* Inferred distinct client handler name. */
/* ADDRESS: GOLDTL 0x004c9f50 */
int __cdecl cm_ExAddCutsceneParticipant(char* command, char* result)
{
    if (fcn_004e6a30(*(int*) (command + 0x10)) == 0)
        return 1;
    if (!fcn_004e6b70(*(int*) (command + 0x10), *(int*) (command + 0x14)))
        return 1;
    if (result != 0)
        result[0] = 1;
    return 0;
}
