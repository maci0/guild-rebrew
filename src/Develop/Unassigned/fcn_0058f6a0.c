#include <string.h>

extern int g_14b55a4;
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

extern int __cdecl sub_5cd440(char*, int, int, void*);
extern void __cdecl sub_52a0c0(int, char);
extern int __cdecl sub_470820(int, int, char*);
extern void __cdecl sub_473a90(int, int);
extern void __cdecl sub_471b60(int);
extern void __cdecl sub_4727a0(int, int);
extern void __cdecl sub_5340f0(int);
extern int __cdecl sub_519190(int, ...);
extern int __cdecl sub_472250(int, int, int);
extern int __cdecl sub_525f60(int, int);
extern int __cdecl sub_526120(char*, int);
extern int __cdecl sub_4a5e60(unsigned short*, int, int, int, float, float, int*);
extern int __cdecl sub_4c5530(char*);
extern int __cdecl sub_4c4450(int);
extern int __cdecl sub_5373e0(int, int);
extern int __cdecl sub_51af00(char*, int, ...);
extern void __cdecl sub_471e30(int);
extern void __cdecl sub_52a2d0(void);
extern void __cdecl sub_5305a0(void);
extern void __cdecl sub_532ef0(void);

struct entry_s {
    unsigned char data[0x21c];
};

struct hand_s {
    unsigned char pad[0x16c];
    void* a16c;
    void* a170;
};

/* ADDRESS: GOLDTL 0x0058f6a0 */
void __cdecl fcn_0058f6a0(const unsigned char* arg1)
{
    unsigned long query[20];
    char msg[0xf8];
    char text[0x1e0];
    struct hand_s* hdl;
    struct entry_s* found;
    int dlg;
    int ok;
    int cancel;
    int selected;
    int r;
    int i;
    int index;

    memset(query, 0, sizeof(query));
    memset(query + 7, 0xff, 8 * sizeof(*query));
    query[0] = 1;
    query[1] = 0x400;
    query[4] = 6;
    hdl = (struct hand_s*) sub_5cd440((char*) query, g_14b55a4, 0, 0);
    if (hdl == 0) {
        sub_532ef0();
        return;
    }
    sub_52a0c0((int) arg1, 0);
    dlg = sub_470820(0, 0, (char*) 0x6a96d8);
    sub_473a90(0, 0);
    sub_471b60(dlg);
    sub_4727a0(dlg, 0);
    sub_5340f0(dword_772514);
    sub_4727a0(dlg, 1);
    sub_519190(0x40a4, 0x40a3, *(unsigned short*) hdl, 4);
    sub_4727a0(dlg, 2);
    r = sub_519190(0x40a5);
    ok = sub_472250(dlg, 2, r);
    cancel = sub_472250(dlg, 2, r + 1);
    dword_100f1dc = -1;
    do {
        if (dword_14ce8e0 != 0) {
            dword_774654 = 1;
        } else if (dword_100f1dc != -1) {
            if (dword_67d370 == ok) {
                r = sub_525f60(0x7f4ca0 + word_774970 * 0x21c, 4);
                found = 0;
                for (i = 0; (unsigned long) &byte_7f4e28[i * 0x21c] < 0x85a228; i++) {
                    if (byte_7f4e28[i * 0x21c] != 0) {
                        found = (struct entry_s*) (0x7f4ca0 + i * 0x21c);
                        break;
                    }
                }
                if (r != 0) {
                    if (found != 0) {
                        memset(msg, 0, sizeof(msg));
                        msg[4] = 0x89;
                        msg[0x36] = 1;
                        *(int*) (msg + 0x64) = 4;
                        index = *(unsigned short*) (arg1 + 0x27);
                        *(int*) (msg + 0xc) = *(int*) (arg1 + 1);
                        *(int*) (msg + 8) = *(int*) (0x7f4ca4 + index * 0x21c);
                        *(int*) (msg + 0x30) = dword_7f4c08;
                        *(int*) (msg + 0x28) = dword_7f4c00;
                        *(int*) (msg + 0x60) = *(int*) (found->data + 4);
                        *(int*) (msg + 0x38) = *(int*) (found->data + 4);
                        *(int*) (msg + 0x2c) = dword_7f4c04;
                        *(int*) (msg + 0x5c) = *(int*) (hdl->pad + 4);
                        *(unsigned short*) (msg + 0x34) = word_7f4c0c;
                        if (hdl->a170 != 0) {
                            *(int*) (msg + 0x58) = *(int*) ((char*) hdl->a170 + 1);
                        } else if (hdl->a16c != 0) {
                            *(int*) (msg + 0x58) = *(int*) ((char*) hdl->a16c + 1);
                        } else {
                            selected = -1;
                            sub_4a5e60((unsigned short*) (0x7f4ca0 + word_774970 * 0x21c),
                                0, 0x7b4c4a0, 0, 0.0f, 100.0f, &selected);
                            *(int*) (msg + 0x58) = selected;
                        }
                        r = sub_4c5530(msg);
                        if (r != -1) {
                            while (sub_4c4450(r) == 0) {
                                sub_5373e0(0, 0x20007);
                            }
                        }
                        dword_7e46ac = 0x677c7;
                        sub_51af00(text, 0x40a7, *(unsigned short*) found->data);
                        sub_526120(text, 0);
                        dword_774654 = 1;
                    } else {
                        sub_526120((char*) dword_14b556c, 0);
                    }
                }
            } else if (dword_67d370 == cancel) {
                dword_774654 = 1;
            }
        }
    } while (sub_5373e0((int) fcn_0058f6a0, 0x677c7) != 0);
    sub_471e30(dlg);
    sub_52a2d0();
    sub_5305a0();
    sub_532ef0();
}
