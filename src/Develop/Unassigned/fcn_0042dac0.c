extern int __cdecl sub_64d41a(void *, unsigned long, unsigned long, unsigned long, void *);
extern void *__cdecl sub_64e2f9(void *, unsigned long);
extern void __cdecl sub_64e48f(void *, int, int);
extern void __cdecl sub_64ed28(void *, int, int, void *);
extern void __cdecl sub_64e1fd(void *);
extern void __cdecl sub_41ddd0(unsigned long);
#include "GOLDTL.txt_OpenText_gconf.h"
extern char g_149d120[][0x74];
extern char g_1052f00[];
extern char g_1053000[][0x50];
extern char* g_14a5320[];
extern int g_11bb000[];
extern char g_6790b0[];
extern char g_679888[];
__declspec(dllimport) int __stdcall MessageBoxA(void*, const char*, const char*, unsigned int);

/* ADDRESS: GOLDTL 0x0042dac0 */
int __cdecl fcn_0042dac0(int a)
{
    char *p;
    char buf[0x104];
    void* f;
    int n, v;
    int *first, *last;

    p = g_149d120[a] + 0x60;

    sub_64d41a(buf, 0x679de4, (unsigned long) g_1052f00, (unsigned long) g_679888, g_149d120[a]);
    f = sub_64e2f9(buf, (unsigned long) g_6790b0);
    if (f == 0) {
        MessageBoxA(0, "Could not write ResourceFile!", "txt_SaveTextFile", 0x30);
        sub_41ddd0((unsigned long) g_6b7fa0);
        g_6b7fa0 = 0;
        return 0;
    }
    sub_64e48f(f, 0, 0);
    first = (int*) p;
    last = (int*) (p + 4);
    n = *last - *first + 1;
    sub_64ed28(&n, 4, 1, f);
    sub_64ed28(first, 4, 1, f);
    sub_64ed28(last, 4, 1, f);
    for (n = *first; n < *last + 1; n++) {
        v = (int) g_14a5320[n] - *(int *)(p + 8);
        sub_64ed28(&v, 4, 1, f);
    }
    for (n = *first; n < *last + 1; n++) {
        sub_64ed28(g_1053000[n], 0x50, 1, f);
    }
    for (n = *first; n < *last + 1; n++) {
        sub_64ed28(g_11bb000 + n, 1, 1, f);
    }

    sub_64ed28(p + 12, 4, 1, f);
    sub_64ed28(*(void**) (p + 8), *(int *)(p + 12), 1, f);
    sub_64e1fd(f);
    return 1;
}
