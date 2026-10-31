void *memset(void *, int, unsigned int);
int __cdecl io_FormatTextBuffer(void *, int, int);
int __cdecl fcn_004fa5f0(void *, int, int);

/* ADDRESS: GOLDTL 0x004f8730 */
int __cdecl fcn_004f8730(char *dx, int *si)
{
    unsigned char buf[0x200];

    if (si[0] != 3 && si[0] != 1) return 1;
    if (dx[0x169] != 0x1d) return 1;
    if (si[0] == 3 && dx[2] == 6) {
        memset(buf, 0, 0x200);
        io_FormatTextBuffer(buf, 0x1da6, dx[9] ? 0x298 : 0x270);
        fcn_004fa5f0(buf, 0, 0x657c7);
    } else if (si[0] == 1 && dx[2] == 6) {
        io_FormatTextBuffer(si + 5, 0x679060, 0x1da5);
    }
    return 2;
}
