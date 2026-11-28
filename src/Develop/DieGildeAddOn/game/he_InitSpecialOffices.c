extern int gm_GameTimeHour;

void __cdecl gm_AddTime(void *, int, int, int);

/* ADDRESS: GOLDTL 0x0057ba50 */
/* ADDRESS: GOLDDE 0x005618b0 */
void __cdecl he_InitSpecialOffices(void *self)
{
    char *rec;

    rec = (char *)self;
    if ((*(unsigned char *)(rec + 0x78) & 4) == 0 && *(unsigned short *)&gm_GameTimeHour > 0xa) {
        gm_AddTime(rec + 0x52, 0x18, 0, 0);
        *(unsigned short *)(rec + 0x56) = 0xa;
        *(int *)(rec + 0x58) = 0;
        *(int *)(rec + 0x5c) = 0;
        *(int *)(rec + 0x70) = 0;
    }
}
