unsigned short *__cdecl fcn_00502cd0(int container_id, int arg_count, ...);
void *__cdecl gm_NextEntityQueryMatch(void);

/* ADDRESS: GOLDTL 0x0050d270 */
int __cdecl fcn_0050d270(int a)
{
    int total;
    unsigned short *p;

    total = 0;
    p = fcn_00502cd0(a, 1, 4, 9);
    if (p != 0) {
        do {
            total += *(int *) ((char *) p + 0xe);
            p = (unsigned short *) gm_NextEntityQueryMatch();
        } while (p != 0);
    }
    return total;
}
