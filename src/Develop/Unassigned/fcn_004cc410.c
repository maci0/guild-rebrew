int __cdecl fcn_004e7ff0(unsigned char *arg);

/* ADDRESS: GOLDTL 0x004cc410 */
int __cdecl fcn_004cc410(char *a1, char *a2)
{
    int r;

    r = fcn_004e7ff0((unsigned char *) (a1 + 0x10));
    if (a2 != 0) {
        a2[0] = (r == 0) + 1;
        a2[1] = 0;
        *(int *) (a2 + 6) = 0;
    }
    return (r == 0);
}
