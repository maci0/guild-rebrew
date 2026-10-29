int __cdecl sub_545510(void);
int __cdecl sub_5218f0(void *, int, int, void *);
void * __cdecl sub_41db70(int, int);

/* ADDRESS: GOLDTL 0x00524b50 */
int __cdecl fcn_00524b50(unsigned char *S)
{
    unsigned char *rec, *p;
    int cnt, c2, i, j;

    sub_545510();
    if (!sub_5218f0(&cnt, 4, 1, S))
        return 0;
    if (!sub_5218f0(&c2, 4, 1, S))
        return 0;
    if (cnt > 0) {
        for (i = 0; i < cnt; i++) {
            rec = (unsigned char *)0x77e980 + i * 0x14c;
            if (!sub_5218f0(rec + 0x00, 4, 1, S))
                return 0;
            if (!sub_5218f0(rec + 0x04, 4, 1, S))
                return 0;
            if (!sub_5218f0(rec + 0x08, 2, 1, S))
                return 0;
            if (!sub_5218f0(rec + 0x0c, 4, 1, S))
                return 0;
            if (!sub_5218f0(rec + 0x10, 4, 1, S))
                return 0;
            if (!sub_5218f0(rec + 0x14, 0x30, 1, S))
                return 0;
            if (!sub_5218f0(rec + 0x44, 0x0e, 1, S))
                return 0;
            if (!sub_5218f0(rec + 0x52, 0x0e, 1, S))
                return 0;
            if (!sub_5218f0(rec + 0x60, 0x0e, 1, S))
                return 0;
            if (!sub_5218f0(rec + 0x70, 4, 1, S))
                return 0;
            if (!sub_5218f0(rec + 0x78, 1, 1, S))
                return 0;
            if (*(int *)0x6a23ac >= 0x1002f) {
                for (j = 0; j < 8; j++)
                    if (!sub_5218f0(rec + 0x8c + 4 * j, 4, 1, S))
                        return 0;
            }
            *(int *)(rec + 0x7c) = 0;
            *(int *)(rec + 0x80) = 0;
            if (!sub_5218f0(rec + 0x80, 4, 1, S))
                return 0;
            if (*(int *)(rec + 0x80) != 0) {
                p = (unsigned char *)sub_41db70(0x400, 0x68af74);
                *(unsigned char **)(rec + 0x7c) = p;
                if (!sub_5218f0(p, *(int *)(rec + 0x80), 1, S))
                    return 0;
            }
            if (*(unsigned char *)(rec + 0x00) == 0x0c) {
                if (!sub_5218f0(rec + 0xac, 4, 1, S))
                    return 0;
                *(unsigned char **)(rec + 0xbc) =
                    (unsigned char *)sub_41db70(0x58, 0x6a24b4);
            } else if (*(unsigned char *)(rec + 0x00) == 0x0d) {
                if (!sub_5218f0(rec + 0xac, 4, 1, S))
                    return 0;
                *(int *)(rec + 0xbc) = -1;
                if (*(int *)(rec + 0x70) == 6)
                    *(unsigned char *)(rec + 0xd0) = 0;
            } else {
                if (!sub_5218f0(rec + 0xac, 4, 1, S))
                    return 0;
            }
            if (*(unsigned char *)(rec + 0x78) & 8) {
                *(unsigned char **)(0x7d1980 + 4 * *(int *)0x7749d8) = rec;
                *(int *)0x7749d8 += 1;
            }
        }
    }
    *(int *)0x7749d4 = cnt;
    if (!sub_5218f0(&cnt, 4, 1, S))
        return 0;
    if (cnt > 0) {
        for (i = 0; i < cnt; i++) {
            rec = (unsigned char *)0x7d2020 + i * 0xa4;
            *(int *)rec = 0;
            if (!sub_5218f0(rec + 0x00, 4, 1, S))
                return 0;
            if (!sub_5218f0(rec + 0x04, 1, 1, S))
                return 0;
            if (!sub_5218f0(rec + 0x08, 4, 1, S))
                return 0;
            if (!sub_5218f0(rec + 0x0c, 4, 1, S))
                return 0;
            if (!sub_5218f0(rec + 0x10, 4, 1, S))
                return 0;
            if (!sub_5218f0(rec + 0x14, 0x0e, 1, S))
                return 0;
            if (!sub_5218f0(rec + 0x22, 0x80, 1, S))
                return 0;
        }
    }
    if (!sub_5218f0(&cnt, 4, 1, S))
        return 0;
    if (cnt > 0) {
        for (i = 0; i < cnt; i++) {
            rec = (unsigned char *)0x7dcae4 + i * 0x50;
            if (!sub_5218f0(rec - 4, 1, 1, S))
                return 0;
            if (!sub_5218f0(rec + 0x00, 4, 1, S))
                return 0;
            if (!sub_5218f0(rec + 0x04, 4, 1, S))
                return 0;
            if (!sub_5218f0(rec + 0x08, 4, 1, S))
                return 0;
            if (!sub_5218f0(rec + 0x0c, 0x40, 1, S))
                return 0;
        }
    }
    return 1;
}
