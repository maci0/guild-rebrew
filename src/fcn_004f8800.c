void *memset(void *, int, unsigned int);
int __cdecl fcn_0051af00(void *, int, int);
int __cdecl fcn_004fa5f0(void *, int, int);

/* ADDRESS: GOLDTL 0x004f8800 */
int __cdecl fcn_004f8800(char *dx, int *si)
{
    unsigned char buf[0x200];

    if (si[0] != 3 && si[0] != 1) return 1;
    if (dx[0x169] != 0x22) return 1;
    if (si[0] == 3 && dx[2] == 6) {
        memset(buf, 0, 0x200);
        fcn_0051af00(buf, 0x1da8, dx[9] ? 0x29d : 0x275);
        fcn_004fa5f0(buf, 0, 0x657c7);
    } else if (si[0] == 1 && dx[2] == 6) {
        fcn_0051af00(si + 5, 0x679060, 0x1da7);
    }
    return 2;
}
