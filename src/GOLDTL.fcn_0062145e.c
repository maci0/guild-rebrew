/* Picks one of two handler pairs for the shadow table at 0x006af208 and
 * tail-jumps through the first slot.  The native body also has an unused
 * EBP frame (push ebp / mov ebp, esp / pop ebp) that the optimizer drops for
 * this source, so the candidate is 4 bytes shorter. */
int __cdecl fcn_0061324e(void);

/* ADDRESS: GOLDTL 0x0062145e */
void __cdecl fcn_0062145e(void)
{
    if (fcn_0061324e() != 0) {
        *(void **)0x6af208 = (void *)0x62131c;
        *(void **)0x6af20c = (void *)0x62131c;
    } else {
        *(void **)0x6af208 = (void *)0x6210dd;
        *(void **)0x6af20c = (void *)0x621234;
    }
    (*(void (**)(void))0x6af208)();
}
