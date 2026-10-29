void __cdecl fcn_00401180(void* a, void* b);

/* ADDRESS: GOLDTL 0x004011a0 */
void __cdecl fcn_004011a0(void* a0, char* a1)
{
    char* p;

    p = a1 - 1;
    do {
        fcn_00401180(a0, p + 1);
        p = p + 1;
    } while (*p != 0);
}
