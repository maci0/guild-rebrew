typedef unsigned char u8;

/* Partial reconstruction: the entry guard, the prefetch and the top of the
 * selection dispatcher are recovered from the native body; the remaining
 * branches are listed in the row blocker. */

int __cdecl fcn_00502cd0();
int __cdecl fcn_00472640();
int __cdecl fcn_00504bd0();
int __cdecl fcn_00506380();
int __cdecl fcn_0057ec20();
int __cdecl fcn_0057e880();
int __cdecl fcn_005cd440();
int __cdecl fcn_005ba910();
int __cdecl fcn_00525ef0();
int __cdecl fcn_0059aa10();
int __cdecl fcn_005c3f10();
int __cdecl fcn_005c49e0();

/* ADDRESS: GOLDTL 0x0052f7b0 */
void __cdecl fcn_0052f7b0(void)
{
    void* sel;
    char* base;
    int kind;
    int flags;

    if (*(int*) 0x6a25b4 != -1 || *(u8*) 0x774964 == 0)
        return;
    sel = *(void**) 0x7e2aa0;
    if (sel != 0 && fcn_00502cd0(*(int*) ((char*) sel + 0x5d), 2, 6, 0) == 0)
        fcn_00502cd0(*(int*) ((char*) sel + 0x5d), 2, 6, 42);
    fcn_00472640(*(int*) 0x6a25e4, 1);
    flags = *(int*) 0x7e46ac & 0x2000;
    if (flags == 0) {
        if (*(int*) 0x100f1dc != -1) {
            if (*(int*) 0x6a25e4 == -1 ||
                *(int*) 0x67d370 != *(int*) 0x6a25e4) {
                if (*(int*) 0x6a25e0 != -1 &&
                    *(int*) 0x67d370 == *(int*) 0x6a25e0) {
                    if (fcn_0057ec20() == 1) {
                        fcn_0057e880(0, 0);
                        fcn_005cd440();
                        fcn_0057e880();
                    }
                }
            } else {
                sel = *(void**) 0x7e2aa0;
                if (sel != 0 && *(char*) sel != 0x47) {
                    kind = fcn_00504bd0(*(u8*) sel);
                    base = (char*) *(int*) 0x868050 + *(u8*) sel * 0x93;
                    if (kind == 1 || kind == 2 || kind == 4 || kind == 7 ||
                        kind == 8 || *base == 0x10 || *base == 0x1e) {
                        if (fcn_0057ec20() == 1) {
                            *(int*) 0x7746d8 = fcn_00506380();
                            fcn_0057e880();
                            fcn_005ba910();
                            fcn_0057e880();
                            *(void**) 0x7e2aa0 = sel;
                            fcn_00525ef0();
                        }
                    }
                }
            }
        }
    } else {
        if (*(int*) 0x100f1dc == -1)
            return;
        if (*(int*) 0x6a25ec == -1 ||
            *(int*) 0x67d370 != *(int*) 0x6a25ec)
            return;
        if (*(int*) 0x7746c4 == 0 && *(int*) 0x7746c8 == 0) {
            if (*(void**) 0x7e2aa0 == 0)
                return;
        }
        *(int*) 0x7746dc = fcn_00506380();
        sel = *(void**) 0x7e2aa0;
        if (sel != 0) {
            kind = fcn_00504bd0(*(u8*) sel);
            *(int*) 0x7746dc = fcn_00506380();
            if ((kind == 3 || kind == 5) && (*(int*) 0x7746dc & 0x10) != 0)
                fcn_005c49e0();
            else
                fcn_005c3f10();
        }
    }
}
