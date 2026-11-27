void __cdecl d3_DeactivateObjectAnimation(char*, char*);
void __cdecl d3_SetObjectAnimationActive(char*, char*, int);

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
    frames = *(char**) (0x68 + stream);

    if (paused) {
        d3_DeactivateObjectAnimation(*(char**) (*(char**) (obj + 0x34) + 0x1ec) + 0xf4, frames);
        *(unsigned char*) (obj + 0x8c) |= 4;
    } else {
        d3_SetObjectAnimationActive(*(char**) (*(char**) (obj + 0x34) + 0x1ec) + 0xf4, frames, 1);
        *(unsigned char*) (obj + 0x8c) &= 0xfb;
    }
}
