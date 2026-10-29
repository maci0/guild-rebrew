typedef unsigned char u8;

/* Partial reconstruction: the entry probe, wait loop setup and the first
 * state reads are recovered from the native body; the render paths are
 * listed in the row blocker. */

int __cdecl fcn_005a74a0();
int __cdecl fcn_00525ef0();
int __cdecl fcn_005373e0();
int __cdecl fcn_00530510();
int __cdecl fcn_005305a0();

/* ADDRESS: GOLDTL 0x005a76b0 */
int __cdecl fcn_005a76b0(char* o)
{
    int r;

    r = -1;
    if (fcn_005a74a0(o) == 0) {
        *(int*) 0x7e2700 = 0;
        return 0;
    }
    fcn_00525ef0();
    fcn_005373e0((void*) 0x5a76b0, 0x20007);
    *(int*) 0x6a2520 = 0;
    fcn_00530510();
    fcn_005305a0();
    *(int*) 0x7746d0 = 0;
    *(unsigned short*) (o + 0x29) = (unsigned short) *(int*) 0x6b8010;
    return r;
}
