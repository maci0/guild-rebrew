void __cdecl sub_533a40(void *);
void __cdecl sub_5b54b0(void *);
void __cdecl sub_4bfe00(void *);
void * __cdecl sub_502cd0(int, int, int, int, int);
void __cdecl sub_4ff210(int, int);
void __cdecl sub_4c5790(int, void *);

/* ADDRESS: GOLDTL 0x00535bd0 */
void __cdecl fcn_00535bd0(void)
{
    int i;
    char buf[124];

    switch ((unsigned char)*(unsigned char *)0x14cf950) {
    case 4:
        if (*(void **)0x7e2a9c)
            sub_5b54b0(*(void **)0x7e2a9c);
        break;
    case 12:
        if (*(int *)0x6a3438 == 0) {
            *(int *)0x6a3438 = 1;
            sub_533a40((void *)0x6a3330);
        } else
            sub_533a40((void *)0x6a3320);
        break;
    case 13:
        if (*(void **)0x7e2a9c)
            sub_4bfe00(*(void **)0x7e2a9c);
        else
            sub_4bfe00(sub_502cd0(0, 2, 7, 4, 0x1d));
        break;
    case 14:
        sub_4ff210(*(short *)0x774970, 0xfffffc18);
        break;
    case 15:
        if (*(unsigned char *)0x7747b0 & 4) {
            for (i = 0; i < 31; i++)
                ((int *)buf)[i] = 0;
            *(int *)buf = -1;
            sub_4c5790(0x11, buf);
        }
        break;
    case 17:
        if (*(int *)0x6a3434 == 0) {
            *(int *)0x6a3434 = 1;
            sub_533a40((void *)0x6a330c);
        } else
            sub_533a40((void *)0x6a32f8);
        break;
    case 19:
        if (*(int *)0x6a2c0c == 0) {
            *(int *)0x6a2c0c = 1;
            sub_533a40((void *)0x6a3224);
        } else
            sub_533a40((void *)0x6a3210);
        break;
    case 22:
        if (*(int *)0x6a3430 == 0) {
            *(int *)0x6a3430 = 1;
            sub_533a40((void *)0x6a32e4);
        } else
            sub_533a40((void *)0x6a32d0);
        break;
    case 24:
        if (*(int *)0x6a343c == 0) {
            *(int *)0x6a343c = 1;
            sub_533a40((void *)0x6a32bc);
        } else
            sub_533a40((void *)0x6a32a8);
        break;
    case 27:
        if (*(int *)0x6a2c10 == 0) {
            *(int *)0x6a2c10 = 1;
            sub_533a40((void *)0x6a3268);
        } else
            sub_533a40((void *)0x6a3254);
        break;
    case 29:
        if (*(int *)0x6a2c08 == 0) {
            *(int *)0x6a2c08 = 1;
            sub_533a40((void *)0x6a3244);
        } else
            sub_533a40((void *)0x6a3234);
        break;
    case 30:
        if (*(int *)0x6a2c04 == 0) {
            *(int *)0x6a2c04 = 1;
            sub_533a40((void *)0x6a3294);
        } else
            sub_533a40((void *)0x6a327c);
        break;
    default:
        break;
    }
}
