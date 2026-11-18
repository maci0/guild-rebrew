void __cdecl fcn_00401180(void* a, void* b);

/* ADDRESS: GOLDTL 0x004011a0 */
void __cdecl fcn_004011a0(void* a0, char* text)
{
    char* cursor;

    cursor = text - 1;
    do {
        fcn_00401180(a0, cursor + 1);
        cursor = cursor + 1;
    } while (*cursor != 0);
}
