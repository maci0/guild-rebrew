extern void __cdecl fcn_004c6ae0(int, int);
extern void __cdecl fcn_004c5530(void *);

typedef struct tagS495F80 {
    unsigned char gap_00[4];
    unsigned char f04;
    unsigned char gap_05[3];
    int f08;
    int f0c;
    unsigned char gap_10[0x26];
    unsigned char f36;
    unsigned char gap_37[0x23];
    unsigned char f5a;
    unsigned char gap_5b[0x9d];
} S495F80;

/* ADDRESS: GOLDTL 0x00495f80 */
int __cdecl fcn_00495f80(int *p, int *q)
{
    S495F80 s;

    fcn_004c6ae0(p[1], -q[4]);
    s.f36 = 1;
    s.f04 = 0x60;
    s.f08 = p[1];
    s.f0c = -1;
    s.f5a = *((unsigned char *)q + 4);
    fcn_004c5530(&s);
    return 4;
}
