extern char* g_5fb5b0;
extern int g_fc52f0, g_fc28f4, g_fb98f4, g_fb9598;
char __cdecl fcn_004378c0(int, unsigned int);

/* ADDRESS: GOLD 0x00438e60 */
char __cdecl fcn_00438e60(char* scene, char* node, unsigned int flags, void (__cdecl* callback)(char*))
{
    char* p;
    unsigned int single;

    if (flags == 0)
        return 0;
    if (node != 0) {
        single = flags & 0x200;
        p = node;
        do {
            if (fcn_004378c0(*(int*) (p + 0x218), flags))
                callback(p);
            if (*(char**) (p + 0x1fc) != 0)
                fcn_00438e60(scene, *(char**) (p + 0x1fc), flags & ~0x200U, callback);
            if (single != 0)
                break;
            p = *(char**) (p + 0x1f0);
            if (p != 0 && (p[0x210] & 1))
                return 1;
        } while (p != 0);
    } else {
        if (scene == g_5fb5b0) {
            *(int*) (scene + 0x80) = g_fc52f0;
            *(int*) (scene + 0x84) = g_fc28f4;
            *(int*) (scene + 0xa4) = g_fb98f4;
            *(int*) (scene + 0xa8) = g_fb9598;
        }
        p = *(char**) (scene + 0x80);
        while (p != 0 && p != (char*) 0xfc2700) {
            fcn_00438e60(scene, p, flags, callback);
            p = *(char**) (p + 0x1f0);
        }
    }
    return 1;
}
