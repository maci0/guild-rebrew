extern void *__cdecl sub_4cef30(int);
extern void *__cdecl sub_4ce610(void *);
extern int __cdecl sub_64d41a(char *, unsigned long, int, int);
extern void *__cdecl sub_445600(char *, int, int, int);
extern int __cdecl sub_455350(void *, void *, char *);
extern char __cdecl sub_45b990(void *, char *, char *, char *, char *);
extern int __cdecl sub_407e30(void *, void *, void *, void *, void *, void *, void *);
extern int __cdecl sub_45b920(void *, void *, void *, char *);
extern int __cdecl sub_402ab0(void *, char *, int);
extern int __cdecl sub_455140(void *, unsigned long, char *);
extern int __cdecl sub_451380(char *, unsigned long);
extern void __cdecl sub_438cb0(void *, char *);

/* ADDRESS: GOLDTL 0x004d2c80 */
int __cdecl fcn_004d2c80(int *arr, int arg1)
{
    char buf[0x100], l[0x40];
    void *ebx, *esi, *edi, *p;
    int j, v, ok;
    unsigned long *q;

    ebx = *(void **)(*(unsigned *)0x67a370 + 0xb0);
    for (j = 0; j < 0x10; j++) {
        v = arr[j];
        if (v == -1)
            continue;
        esi = sub_4cef30(v);
        if (esi == 0)
            continue;
        p = sub_4ce610(esi);
        if (p != 0) {
            q = (unsigned long *)p;
            if (*q == 0x174 || *q == 0x176 || *q == 0x15e || *q == 0x160)
                sub_64d41a(buf, 0x68bcd8, v, j);
            else
                sub_64d41a(buf, 0x68bcc4, v, j);
        } else {
            sub_64d41a(buf, 0x68bcc4, v, j);
        }
        edi = sub_445600(buf, 0, 0x100, 0);
        if (edi == 0)
            continue;
        sub_455350(edi, (char *)edi + 0x4c, l);
        ok = sub_45b990(ebx, l, l + 0x14, l + 0x1c, l + 0x24);
        if (!ok)
            return 0;
        sub_407e30(ebx, (char *)esi + 0x184, 0, 2, 0, 0, 0);
        sub_45b920(ebx, (char *)edi + 0x4c, 0, buf);
        sub_402ab0((char *)esi + 0x184, buf, 1);
        sub_455140(edi, 0x662d40, l);
        sub_451380(l, 0x662d40);
        sub_438cb0((char *)(*(unsigned long *)((char *)esi + 0x184) + 0x34), l);
    }
    return 0;
}
