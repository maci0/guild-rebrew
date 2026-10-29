typedef unsigned char u8;
typedef unsigned short u16;

extern char g_7f4ca0[];
extern int g_6b8010;
extern char g_6b5c60[];
extern char g_6a80c0[];

int __cdecl fcn_004c4450(int);
char* __cdecl gm_SearchTable67(int);
int __cdecl fcn_00502cd0(int, int, int, int);
int __cdecl fcn_00500bb0(char*, int, int, int);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl he_MessageBoxQuickjump(int, int, char*, int, int, int, int, char*,
                          char*);
int __cdecl fcn_00515540(int);
void __cdecl fcn_004432d0(int, int);
void* __cdecl fcn_00426fd0(char*);
void __cdecl fcn_00428340(void*, int, int);
void __cdecl fcn_00546190(char*);
void __cdecl fcn_0057c9f0(char*);
int __cdecl fcn_004c5620(char*, int);

/* ADDRESS: GOLDTL 0x0057cbc0 */
void __cdecl fcn_0057cbc0(char* p)
{
    char buf[0x400];
    char* s;
    char* wnd;
    char* e;
    char* tbl;
    int w;

    if (*(int*) (p + 0x84) != -1 && fcn_004c4450(*(int*) (p + 0x84)) == 0)
        return;
    if (*(int*) (p + 0x70) == -1 || *(int*) (p + 0x70) == -2) {
        fcn_00546190(p);
        return;
    }
    if (*(int*) (p + 0x70) == 0) {
        wnd = 0;
        s = gm_SearchTable67(*(int*) (p + 0x10));
        if (s != 0)
            wnd = (char*) fcn_00502cd0(*(int*) (s + 0x5d), 1, 0, 0x27f);
        fcn_00500bb0(p + 0x52, 2, 0, 0);
        if (wnd != 0) {
            w = *(unsigned short*) (s + 0x27);
            tbl = g_7f4ca0 + w * 0x21c;
            fcn_0051af00(buf, 0x4205, s);
            he_MessageBoxQuickjump(*(int*) (tbl + 4), *(int*) (tbl + 4), buf, 0, 0x5fc,
                         *(int*) (s + 1), *(int*) (wnd + 2), g_6b5c60,
                         g_6b5c60);
            fcn_004432d0(fcn_00515540((int) wnd), 1);
            e = (char*) fcn_00426fd0(g_6a80c0);
            if (e != 0) {
                *(int*) (e + 0xc8c) = 1;
                *(int*) (e + 0x104) = *(int*) (wnd + 2);
                fcn_00428340(e, 1, *(int*) (p + 0xac));
            }
            fcn_004432d0(g_6b8010, 1);
        }
        *(int*) (p + 0x58) = 0;
        *(int*) (p + 0x70) = 1;
        return;
    }
    if (*(int*) (p + 0x70) == 1 && (*(u8*) (p + 0x78) & 4) == 0) {
        fcn_0057c9f0(p);
        *(int*) (p + 0x84) = fcn_004c5620(p, -1);
    }
}
