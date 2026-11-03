void __cdecl fcn_00533a40(char *);
void __cdecl fcn_005b54b0(char *);
int __cdecl fcn_004bfe00(char *);
unsigned short * __cdecl fcn_00502cd0(int, int, ...);
float __cdecl fcn_004ff210(unsigned short, int);
void __cdecl fcn_004c5790(char, char *);

/* ADDRESS: GOLDTL 0x00535bd0 */
void __cdecl fcn_00535bd0(void)
{
    char *object_entry;
    int i;
    char dialog_buf[124];

    switch ((unsigned char)*(unsigned char *)0x14cf950) {
    case 37:
        object_entry = *(void **)0x7e2a9c;
        if (object_entry)
            fcn_005b54b0(object_entry);
        break;
    case 35:
        if (*(int *)0x6a3438 = (*(int *)0x6a3438 == 0)) {
            fcn_00533a40((char *)0x6a3330);
        } else
            fcn_00533a40((char *)0x6a3320);
        break;
    case 19:
        object_entry = *(void **)0x7e2a9c;
        if (object_entry)
            fcn_004bfe00(object_entry);
        else
            fcn_004bfe00((char *)fcn_00502cd0(0, 2, 7, 4, 0x1d));
        break;
    case 23:
        if (*(int *)0x6a3434 = (*(int *)0x6a3434 == 0)) {
            fcn_00533a40((char *)0x6a330c);
        } else
            fcn_00533a40((char *)0x6a32f8);
        break;
    case 30:
        if (*(int *)0x6a3430 = (*(int *)0x6a3430 == 0)) {
            fcn_00533a40((char *)0x6a32e4);
        } else
            fcn_00533a40((char *)0x6a32d0);
        break;
    case 32:
        if (*(int *)0x6a343c = (*(int *)0x6a343c == 0)) {
            fcn_00533a40((char *)0x6a32bc);
        } else
            fcn_00533a40((char *)0x6a32a8);
        break;
    case 46:
        if (*(int *)0x6a2c04 = (*(int *)0x6a2c04 == 0)) {
            fcn_00533a40((char *)0x6a3294);
        } else
            fcn_00533a40((char *)0x6a327c);
        break;
    case 20:
        fcn_004ff210(*(unsigned short *)0x774970, -1000);
        break;
    case 21:
        if (*(unsigned char *)0x7747b0 & 4) {
            for (i = 0; i < 31; i++)
                ((int *)dialog_buf)[i] = 0;
            *(int *)dialog_buf = -1;
            fcn_004c5790(0x11, dialog_buf);
        }
        break;
    case 18:
        if (*(int *)0x6a2c10 = (*(int *)0x6a2c10 == 0)) {
            fcn_00533a40((char *)0x6a3268);
        } else
            fcn_00533a40((char *)0x6a3254);
        break;
    case 4:
        if (*(int *)0x6a2c08 = (*(int *)0x6a2c08 == 0)) {
            fcn_00533a40((char *)0x6a3244);
        } else
            fcn_00533a40((char *)0x6a3234);
        break;
    case 25:
        if (*(int *)0x6a2c0c = (*(int *)0x6a2c0c == 0)) {
            fcn_00533a40((char *)0x6a3224);
        } else
            fcn_00533a40((char *)0x6a3210);
        break;
    default:
        break;
    }
}
