extern int g_7f4c04;

void __cdecl fcn_00500bb0(void *, int, int, int);

/* ADDRESS: GOLDTL 0x0057ba50 */
void __cdecl fcn_0057ba50(void *self)
{
    char *rec;

    rec = (char *)self;
    if ((*(unsigned char *)(rec + 0x78) & 4) == 0 && *(unsigned short *)&g_7f4c04 > 0xa) {
        fcn_00500bb0(rec + 0x52, 0x18, 0, 0);
        *(unsigned short *)(rec + 0x56) = 0xa;
        *(int *)(rec + 0x58) = 0;
        *(int *)(rec + 0x5c) = 0;
        *(int *)(rec + 0x70) = 0;
    }
}
