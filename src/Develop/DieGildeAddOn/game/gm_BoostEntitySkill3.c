int __cdecl io_FormatTextBuffer(void *buf, int len);
int __cdecl d2_OpenEntityPicker(void *a1, void *buf);
int __cdecl gm_LookupEntityRecordById(int value);
int __cdecl gm_IncreaseEntitySkill(int value, int mode);

/* ADDRESS: GOLDTL 0x005dd0c0 */
/* ADDRESS: GOLDDE 0x005be660 */
int __cdecl gm_BoostEntitySkill3(void *actor, void *request)
{
    char buf[0x100];
    int r;

    if (*(char *)((char *)actor + 2) == 6) {
        io_FormatTextBuffer(buf, 0x9d);
    } else {
        r = gm_LookupEntityRecordById(*(int *)((char *)request + 4));
        if (r != 0) {
            gm_IncreaseEntitySkill(r, 3);
            return 1;
        }
        return 0;
    }
    r = d2_OpenEntityPicker(actor, buf);
    if (r != 0) {
        gm_IncreaseEntitySkill(r, 3);
        return 1;
    }
    return 0;
}
