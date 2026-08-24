/* ReadVfsDataChecked — wrapper around ReadVfsData, nonzero on success. */

// FUNCTION: SERVER 0x10012440

#include "../loadsave_dump1.c"

int __cdecl ReadVfsDataChecked(int a, int b, int c, int d)
{
    /* ReadVfsData wrapper: nonzero on success (unsigned > 0 carry idiom). */
    return (unsigned int)ReadVfsData(a, b, c, d) > 0;
}
