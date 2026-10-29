typedef unsigned char u8;

/* Partial reconstruction: entry state setup and the first entity probe are
 * recovered from the native body; the remaining message paths are listed in
 * the row blocker. */

int __cdecl fcn_004efd30();
int __cdecl fcn_004f08d0();
int __cdecl fcn_004c4450();
int __cdecl fcn_005373e0();

/* ADDRESS: GOLDTL 0x00586c10 */
int __cdecl fcn_00586c10(char* obj)
{
    int state[57];
    int i;
    int r;
    int ent;

    for (i = 0; i < 57; i++)
        state[i] = 0;
    *(u8*) 0x14cf72f = 0;
    i = *(int*) 0x7e46ac | 0x80;
    state[0x1a] = *(int*) 0x6b7fac;
    if (*(int*) (obj + 0x61) == 0)
        return i;
    r = fcn_004efd30(*(int*) (obj + 1));
    if (r != 0)
        return r;
    ent = fcn_004f08d0(obj);
    if (ent != -1 && fcn_004c4450(ent) == 0) {
        fcn_005373e0((void*) 0x586c10, 0x20007);
        return 0;
    }
    return 0;
}
