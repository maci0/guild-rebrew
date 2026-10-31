int __cdecl io_FormatTextBuffer(void *buf, int len);
int __cdecl fcn_005cad70(void *a1, void *buf);
int __cdecl gm_LookupEntityRecordById(int value);
int __cdecl fcn_005dcf40(int value, int mode);

/* ADDRESS: GOLDTL 0x005dd050 */
int __cdecl fcn_005dd050(void *a1, void *a2)
{
    char buf[0x100];
    int r;

    if (*(char *)((char *)a1 + 2) == 6) {
        io_FormatTextBuffer(buf, 0x9d);
        r = fcn_005cad70(a1, buf);
    } else {
        r = gm_LookupEntityRecordById(*(int *)((char *)a2 + 4));
    }
    if (r) {
        fcn_005dcf40(r, 1);
        return 1;
    }
    return 0;
}
