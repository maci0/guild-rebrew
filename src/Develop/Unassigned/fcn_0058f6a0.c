
extern int dword_14b55a4;
extern int dword_100f1dc;
extern int dword_14ce8e0;
extern int dword_67d370;
extern unsigned short word_774970;
extern unsigned char byte_7f4e28[];
extern int dword_14b556c;
extern int dword_7f4c00;
extern int dword_7f4c04;
extern int dword_7f4c08;
extern unsigned short word_7f4c0c;
extern unsigned int dword_7e46ac;
extern int dword_774654;
extern int dword_772514;

extern int __cdecl sub_5cd440(void);
extern int __cdecl sub_52a0c0(void);
extern int __cdecl sub_470820(void);
extern int __cdecl sub_473a90(void);
extern int __cdecl sub_471b60(void);
extern int __cdecl sub_4727a0(void);
extern int __cdecl sub_5340f0(void);
extern int __cdecl sub_519190(void);
extern int __cdecl sub_472250(void);
extern int __cdecl sub_525f60(void);
extern int __cdecl sub_526120(void);
extern int __cdecl sub_4a5e60(void);
extern int __cdecl sub_4c5530(void);
extern int __cdecl sub_4c4450(void);
extern int __cdecl sub_5373e0(void);
extern int __cdecl sub_51af00(void);
extern int __cdecl sub_471e30(void);
extern int __cdecl sub_52a2d0(void);
extern int __cdecl sub_5305a0(void);
extern int __cdecl sub_532ef0(void);

struct entry_s {
    unsigned char data[0x21c];
};

struct hand_s {
    unsigned char pad[0x170];
    void *a170;
    unsigned char pad2[0x14];
    void *a16c;
};

/* ADDRESS: GOLDTL 0x0058f6a0 */
int __cdecl fcn_0058f6a0(void *arg1, const unsigned char *arg2)
{
    unsigned char buf[0x350];
    struct hand_s *hdl;
    void *ebx;
    struct entry_s *found;
    unsigned long idx;
    unsigned long v;
    unsigned long w;
    int r;
    int i;

    for (i = 0; i < 0x14; i++)
        ((unsigned long *)&buf[0])[i] = 0;
    for (i = 0; i < 8; i++)
        ((unsigned long *)&buf[0])[i] = 0xffffffff;
    hdl = (struct hand_s *)sub_5cd440();
    if (!hdl) {
        return sub_532ef0();
    }
    ebx = (void *)sub_52a0c0(arg1);
    sub_470820(0, 0x6a96d8);
    sub_473a90(0, 0);
    sub_471b60((unsigned long)ebx);
    sub_4727a0((unsigned long)ebx, 0);
    sub_5340f0(dword_772514);
    sub_4727a0((unsigned long)ebx, 1);
    sub_519190(0x40a4, 0x40a3, (unsigned long)hdl[0].pad[0] & 0xffff, 4);
    sub_4727a0((unsigned long)ebx, 2);
    v = sub_519190(0x40a5);
    sub_472250((unsigned long)ebx, 2, v);
    w = sub_472250((unsigned long)ebx, 2, v + 1);
    dword_100f1dc = -1;
    for (;;) {
        if (dword_14ce8e0)
            goto L9dc;
        if (dword_100f1dc == -1)
            goto L9e2;
        if (dword_67d370 != (int)w)
            goto L9d6;
        idx = word_774970;
        sub_525f60(0x7f4ca0 + idx * 540, 4);
        found = 0;
        for (i = 0; (unsigned long)&byte_7f4e28[i * 540] < 0x85a228; i++) {
            if (byte_7f4e28[i * 540]) {
                found = (struct entry_s *)(0x7f4ca0 + i * 540);
                break;
            }
        }
        if (found) {
            for (i = 0; i < 0x3e; i++)
                ((unsigned long *)&buf[0x6c])[i] = 0;
            buf[0x70] = 0x89;
            buf[0xa2] = 1;
            ((unsigned long *)&buf[0xd0])[0] = 4;
            idx = arg2[0x27];
            v = ((unsigned long *)&found->data[0])[0] * 0;
            ((unsigned long *)&buf[0x78])[0] = *(unsigned long *)(arg2 + 1);
            ((unsigned long *)&buf[0x74])[0] =
                ((unsigned long *)(0x7f4ca0 + idx * 540))[1];
            ((unsigned long *)&buf[0x9c])[0] = dword_7f4c08;
            ((unsigned long *)&buf[0x94])[0] = dword_7f4c00;
            ((unsigned long *)&buf[0xcc])[0] = *(unsigned long *)(found->data + 4);
            ((unsigned long *)&buf[0xa4])[0] = *(unsigned long *)(found->data + 4);
            ((unsigned long *)&buf[0x98])[0] = dword_7f4c04;
            ((unsigned long *)&buf[0xc8])[0] = *(unsigned long *)(hdl->pad + 4);
            *(unsigned short *)&buf[0xa0] = word_7f4c0c;
            if (hdl->a170) {
                ((unsigned long *)&buf[0xc4])[0] =
                    *(unsigned long *)((unsigned char *)hdl->a170 + 1);
            } else if (hdl->a16c) {
                ((unsigned long *)&buf[0xc4])[0] =
                    *(unsigned long *)((unsigned char *)hdl->a16c + 1);
            } else {
                r = sub_4a5e60(0x7f4ca0 + word_774970 * 540, 0, 0,
                                0x7b4c4a0, 0x42c80000, &buf[0x10]);
                ((unsigned long *)&buf[0xc4])[0] = r;
            }
            r = sub_4c5530(&buf[0x6c]);
            while (r != -1) {
                if (sub_4c4450(r)) {
                    sub_5373e0(r, 0x20007);
                    continue;
                }
                break;
            }
            dword_7e46ac = 0x677c7;
            sub_51af00(&buf[0x164], 0x40a7, *(unsigned short *)&found->data[0]);
            sub_526120(&buf[0x17 + 1], 0);
            dword_774654 = 1;
        } else {
            sub_526120(dword_14b556c, (unsigned long)found);
        }
        goto L9e2;
L9d6:
        if (dword_67d370 != sub_4c4450(0))
            goto L9e2;
L9dc:
        dword_774654 = 1;
L9e2:
        if (sub_5373e0(0x58f6a0, 0x677c7))
            continue;
        sub_471e30((unsigned long)ebx);
        sub_52a2d0();
        sub_5305a0();
        break;
    }
    return sub_532ef0();
}
