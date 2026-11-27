typedef int (__stdcall *MAIN_GET_ASYNC_KEY_STATE_FN)(int);
typedef int (__stdcall *MAIN_CALL_NEXT_HOOK_FN)(int, int, int, int);

/* ADDRESS: GOLDTL 0x00537fe0 */
int __stdcall main_FilterMenuMessageHook(int arg0, int arg1, void *arg2)
{
    int x;
    int s;

    if (arg0 == 0) {
        x = (*(MAIN_GET_ASYNC_KEY_STATE_FN *)0x662288)(0x11);
        s = (short)x >> 15;
        if (*(int *)arg2 == 0x1b && s) return 1;
        if (*(int *)arg2 == 9 && (*(unsigned char *)((char *)arg2 + 8) & 0x20)) return 1;
        if (*(int *)arg2 == 0x1b && (*(unsigned char *)((char *)arg2 + 8) & 0x20)) return 1;
    }
    return (*(MAIN_CALL_NEXT_HOOK_FN *)0x66228c)(*(int *)0x7747dc, arg0, arg1, (int)arg2);
}
