void __cdecl fcn_00435810(char*, char*);
void __cdecl fcn_00435870(char*, char*, int);

/* ADDRESS: GOLD 0x00404c20 */
void __cdecl fcn_00404c20(char* obj, int paused)
{
    char* stream;
    char* frames;


    if (*(int*) (obj + 0x128) == 0)
        return;
    stream = *(char**) (obj + 0x70);
    if (stream == 0)
        return;
    frames = *(char**) (stream + 0x68);

    if (paused) {
        fcn_00435810(*(char**) (*(char**) (obj + 0x34) + 0x1ec) + 0xf4, frames);
        obj[0x8c] |= 4;
    } else {
        fcn_00435870(*(char**) (*(char**) (obj + 0x34) + 0x1ec) + 0xf4, frames, 1);
        obj[0x8c] &= 0xfb;
    }
}
