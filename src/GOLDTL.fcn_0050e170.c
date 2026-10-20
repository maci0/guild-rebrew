typedef struct ENT_50e170 ENT_50e170;
struct ENT_50e170 {
    unsigned char pad_000[0x14];
    int id;
    unsigned char pad_018[4];
    unsigned char f1c;
};

extern int __cdecl fcn_0050dfd0(char* a1, int a2);
extern unsigned short* __cdecl fcn_00502cd0(int container_id, int arg_count, ...);
extern int __cdecl fcn_00502850(void);

/* ADDRESS: GOLDTL 0x0050e170 */
/* The call to 0x50dfd0 passes two stack arguments; the callee body at
 * 0x50dfd0 reads only the first. */
int __cdecl fcn_0050e170(ENT_50e170* a0, int a1, int a2)
{
    int total;
    int i;
    int n;
    unsigned short* p;

    total = fcn_0050dfd0((char*) a0, a1);
    p = fcn_00502cd0(a0->id, 1, 0, a1);
    if (p != 0) {
        n = *(int*) ((char*) p + 0xe);
        if (total - n > a2) {
            return a2;
        }
        return total - n;
    }
    i = 0;
    if (fcn_00502cd0(a0->id, 1, 5) != 0) {
        do {
            i++;
        } while (fcn_00502850() != 0);
    }
    if (i >= (int) (unsigned char) a0->f1c) {
        return 0;
    }
    if (total >= a2) {
        return a2;
    }
    return total;
}
