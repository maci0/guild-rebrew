// FUNCTION: GOLD 0x005e7cf1
// SIZE: 12

/* Wall: reference prologue is `push edi; mov edi,[esp+8]` + 3x `stosd`;
 * plain stores, struct-assign, memset, and *p++ loop all emit different
 * prologues/idioms at this size. Parked. */
void __cdecl fcn_005e7cf1(int* dst)
{
    dst[0] = 0;
    dst[1] = 0;
    dst[2] = 0;
}
