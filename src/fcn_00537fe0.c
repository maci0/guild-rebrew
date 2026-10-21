typedef int (__stdcall *F1_537fe0)(int);
typedef int (__stdcall *F4_537fe0)(int, int, int, int);

/* ADDRESS: GOLDTL 0x00537fe0 */
int __stdcall fcn_00537fe0(int arg0, int arg1, void *arg2)
{
    int x;

    if (arg0 == 0) {
        x = (*(F1_537fe0 *)0x662288)(0x11);
        if (*(int *)arg2 == 0x1b && (short)x >> 15) return 1;
        if (*(int *)arg2 == 9 && (*(unsigned char *)((char *)arg2 + 8) & 0x20)) return 1;
        if (*(int *)arg2 == 0x1b && (*(unsigned char *)((char *)arg2 + 8) & 0x20)) return 1;
    }
    return (*(F4_537fe0 *)0x66228c)(*(int *)0x7747dc, arg0, arg1, (int)arg2);
}
