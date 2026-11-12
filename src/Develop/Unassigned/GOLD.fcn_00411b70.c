void __cdecl fcn_00435740(char* sounds, char* name);

/* ADDRESS: GOLD 0x00411b70 */
int __cdecl fcn_00411b70(char* model)
{
    int offset;
    char* pages;
    char* name;

    offset = 0;
    do {
        pages = *(char**) (model + 0x1ec);
        if (pages != 0) {
            name = *(char**) (pages + offset + 0x178);
            if (name != 0) {
                fcn_00435740(pages + 0xf4, name);
            }
        }
        offset += 0x7c;
    } while (offset < 0x174);
    return 1;
}
