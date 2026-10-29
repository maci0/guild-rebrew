extern char* g_6b7e98;

void __cdecl fcn_00428720(char*);

/* Iterate the 128 0xc98-byte records behind g_6b7e94 and call fcn_00428720
 * for each active record whose owner differs from g_6b7e98's record. */
/* ADDRESS: GOLDTL 0x0040c6d0 */
int __cdecl fcn_0040c6d0(void)
{
    int i;
    int id;
    char* obj;

    for (i = 0; i < 128; i++) {
        obj = *(char**) 0x6b7e94 + i * 0xc98;
        id = *(int*) (obj + 0x100);
        if (id == -1)
            continue;
        if ((*(unsigned char*) (obj + 0x124) & 1) == 0)
            continue;
        if (*(int*) (obj + 0x104) != *(int*) (g_6b7e98 + 0x104))
            continue;
        if (id == *(int*) (g_6b7e98 + 0x100))
            continue;
        fcn_00428720(obj);
    }
    return 0;
}
