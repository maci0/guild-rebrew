/* ADDRESS: GOLD 0x0052e1c0 */
void __cdecl fcn_0052e1c0(void)
{
    char* slot;
    char* record;

    slot = (char*) 0x760640;
    do {
        record = *(char**) slot;
        if (record)
            *(int*) (record + 0x224) = 0;
        *(char**) slot = 0;
        slot += 0xc8;
    } while ((int) slot < 0x761f40);
}
