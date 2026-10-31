typedef unsigned char u8;
typedef unsigned short u16;

int __cdecl fcn_004ec7d0(int a1);
int __cdecl fcn_00526010(void* tbl, int a2, char a3);
int __cdecl fcn_00526120(void* buf, int a2);
void __cdecl io_FormatTextBuffer(void* buf, int id, ...);
int __cdecl fcn_004ee220(int a1, int a2);
int __cdecl fcn_004c4450(int a1);
int __cdecl fcn_005373e0(int a1, int a2);
void __cdecl fcn_004ee080(int a1);
void __cdecl fcn_004c5150(int a1, int a2, char a3, int a4);

/* ADDRESS: GOLDTL 0x00584f00 */
int __cdecl fcn_00584f00(int a1, char* a2, int a3)
{
    char buf[0x200];
    int h;
    int r;

    h = fcn_004ec7d0(a1);
    if (fcn_00526010((void*) (540 * *(u16*) 0x774970 + 0x7f4ca0), a3,
                     *(u8*) 0x773d75) == 0)
        goto ret0;
    if (h == 0)
        goto main;
    fcn_00526120((void*) *(int*) 0x14b5440, 0x100);
ret0:
    return 0;
main:
    io_FormatTextBuffer(buf, 0x4044,
                 *(int*) (0x14b5908 + *(int*) (a2 + 0x10) * 4),
                 *(int*) (0x14b596c + *(int*) (a2 + 0x14) * 4));
    if (fcn_00526120(buf, 1) == 0)
        goto ret0;
    r = fcn_004ee220(a1, (int) a2);
    if (r != -1) {
        int q;

        while ((q = fcn_004c4450(r)) == 0)
            fcn_005373e0(q, 0x20007);
    }
    if (fcn_004c4450(r) != 1)
        goto ret0;
    fcn_004ee080((int) a2);
    fcn_004c5150(-1, *(int*) (0x7f4ca4 + 540 * *(u16*) 0x774970),
                 *(u8*) 0x773d75, a3);
    return 1;
}
