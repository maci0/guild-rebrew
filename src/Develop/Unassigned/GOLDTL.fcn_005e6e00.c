#include <stdio.h>
#include <string.h>
#define D(a) (*(int *)(a))
#define B(a) (*(unsigned char *)(a))
#define W(a) (*(unsigned short *)(a))
#define F(a) (*(float *)(a))
short *__cdecl gm_GetEntityTableEntry(char *);
int __cdecl gm_WalkEntityChain(unsigned short);
int __cdecl fcn_0050b710(int, unsigned char);
int __cdecl fcn_0050b750(int, int);
double __cdecl gm_RandomFloat01(void);
int __cdecl gm_RandomMod(unsigned short);
int __cdecl fcn_00470820(int, int, char *);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl io_FormatTextBuffer(char *, int, ...);
int __cdecl io_AppendText(char *, ...);
int __cdecl fcn_005373e0(void *, int);
void __cdecl fcn_00471e30(int);
int __cdecl fcn_005e6ba0(void);
int __cdecl fcn_004a6bb0(char *, void *);
void __cdecl fcn_005e6dd0(void);
short __cdecl fcn_004a6f50(void);
void __cdecl fcn_00472640(int, int);
void __cdecl fcn_005e6d10(int);
int __cdecl fcn_00526120(char *, int);
void __cdecl fcn_00471af0(int, int);
int __cdecl fcn_005e7e30(void);
void __cdecl fcn_005e7b70(int, int, void *);
int __cdecl d2_SetForm(int, int);
int __cdecl fcn_00471f80(int);
int __cdecl fcn_004a8750(int);

/* ADDRESS: GOLDTL 0x005e6e00 */
int __cdecl fcn_005e6e00(void)
{
    char text[256], prompt[256];
    char *entry, *owner;
    int money, dialog, flags, previous, clicked, choice, control;
    owner = (char *)(0x7f4ca0 + W(0x774970) * 0x21c);
    previous = -1;
    entry = (char *)gm_GetEntityTableEntry(owner);
    if (!entry) return 0;
    money = fcn_0050b710(gm_WalkEntityChain(W(0x774970)), B(0x773d75));
    if (!(gm_RandomFloat01() < *(float *)(entry + 0x60)) || W(0x7f4c04) <= 11 || money < 10000) {
        dialog = fcn_00470820(0, 0, (char *)0x6ad5f4);
        if (!dialog) return 0;
        d2_CenterDialogWindows(D(0x6ad568));
        io_FormatTextBuffer(text, 0x4239, 0x4238);
        io_AppendText(text);
        while (fcn_005373e0((void *)fcn_005e6e00, 0x777c7)) {
            if (D(0x14ce8e0) || B(0x14cf701)) D(0x774654) = 1;
        }
        fcn_00471e30(dialog);
        return 0;
    }
    *(float *)(entry + 0x60) = *(float *)(entry + 0x60) * F(0x664178) - F(0x662a3c);
    B(0x14cf71e) = 0;
    if (!fcn_005e6ba0()) return 0;
    if (!fcn_004a6bb0(owner, (void *)0x7765a0)) {
        fcn_005e6dd0();
        return 0;
    }
    flags = fcn_004a6f50();
    D(0x100f1dc) = -1;
    do {
        if (D(0x14ce8e0)) D(0x774654) = 1;
        fcn_00472640(D(0x6ad56c), flags & 1);
        fcn_00472640(D(0x6ad570), flags & 8);
        fcn_00472640(D(0x6ad578), flags & 0x10);
        fcn_005e6d10((flags & 1) && (flags & 0x20));
        clicked = D(0x67d370);
        if (D(0x100f1dc) != -1) {
            if (D(0x6ad570) == clicked) {
                io_FormatTextBuffer(prompt, 0x4263);
                if (fcn_00526120(prompt, 0x101)) D(0x774654) = 1;
                clicked = D(0x67d370);
            }
            if (D(0x6ad57c) == clicked) {
                fcn_00471af0(D(0x6ad568), 0);
                fcn_005e7e30();
                fcn_00471af0(D(0x6ad568), 1);
                clicked = D(0x67d370);
            }
        }
        switch (D(0x7765a0)) {
        case 1:
            if (previous != 1) {
                previous = 1;
                fcn_005e7b70(1, 0, 0); fcn_005e7b70(2, 0, 0); fcn_005e7b70(0, 0, 0);
            }
            d2_SetForm(D(0x6ad568), 4);
            if (D(0x776650)) {
                choice = D(0x7765a4 + D(0x776650) * 0x34);
                sprintf(text, (char *)D(0x14b5c5c), choice + 0x30, choice + 0x40);
                io_AppendText(text);
                io_FormatTextBuffer(text, 0x4251, D(0x776644)); io_AppendText(text);
                if (D(0x100f1dc) != -1 && D(0x6ad578) == D(0x67d370)) flags = fcn_004a6f50();
            } else {
                strcpy(text, (char *)D(0x14b5c60)); io_AppendText(text);
                if (D(0x100f1dc) != -1 && D(0x6ad56c) == D(0x67d370)) {
                    choice = fcn_00471f80(D(0x6ad580));
                    D(0x77664c) = fcn_0050b750(choice, B(0x773d75));
                    flags = fcn_004a6f50();
                }
            }
            break;
        case 2:
            d2_SetForm(D(0x6ad568), 4);
            io_FormatTextBuffer(text, 0x4252, D(0x776640)); io_AppendText(text);
            io_FormatTextBuffer(text, (unsigned short)gm_RandomMod(3) + 0x4253, 0x4256); io_AppendText(text);
            if (D(0x776650)) {
                io_FormatTextBuffer(text, 0x425a, D(0x77664c)); io_AppendText(text);
            } else io_AppendText((char *)D(0x14b5c84));
            fcn_005e7b70(1, 3, (void *)0x7765e0);
            fcn_005e7b70(2, 3, (void *)0x776614);
            fcn_005e7b70(0, 3, (void *)0x7765ac);
            flags = fcn_004a6f50();
            break;
        case 4:
        case 8:
            d2_SetForm(D(0x6ad568), 4);
            io_FormatTextBuffer(text, 0x4252, D(0x776640)); io_AppendText(text);
            choice = D(0x7765a0) == 2 ? 0x4256 : D(0x7765a0) == 4 ? 0x4257 : 0x4258;
            io_FormatTextBuffer(text, (unsigned short)gm_RandomMod(3) + 0x4253, choice); io_AppendText(text);
            if (D(0x776650)) {
                io_FormatTextBuffer(text, 0x425a, D(0x77664c)); io_AppendText(text);
            } else io_AppendText((char *)D(0x14b5c84));
            if (D(0x7765a0) != 4 || previous != 4) {
                if (D(0x7765a0) == 4) previous = 4;
                choice = D(0x7765a0) == 2 ? 3 : D(0x7765a0) == 4 ? 4 : 5;
                fcn_005e7b70(1, choice, (void *)0x7765e0);
                fcn_005e7b70(2, choice, (void *)0x776614);
                fcn_005e7b70(0, choice, (void *)0x7765ac);
            }
            flags = fcn_004a6f50();
            break;
        case 3:
        case 5:
        case 9:
            if (D(0x100f1dc) != -1) {
                if (D(0x6ad56c) == clicked) {
                    if (!D(0x776650)) {
                        choice = fcn_00471f80(D(0x6ad580));
                        D(0x77664c) = fcn_0050b750(choice, B(0x773d75));
                    }
                    flags = fcn_004a6f50();
                    choice = D(0x7765a0) == 9 ? 5 : 4;
                    fcn_005e7b70(0, choice, (void *)0x7765ac);
                    fcn_005e7b70(1, choice, (void *)0x7765e0);
                    fcn_005e7b70(2, choice, (void *)0x776614);
                } else if (D(0x6ad570) == clicked) D(0x774654) = 1;
            }
            break;
        case 6:
            d2_SetForm(D(0x6ad568), 4);
            io_FormatTextBuffer(text, 0x4252, D(0x776640)); io_AppendText(text);
            io_AppendText((char *)D(0x14b5c8c));
            D(D(0x1015ea0) + 0x60 + D(0x6ad588) * 0x2f4) = 0;
            D(D(0x1015ea0) + 0x60 + D(0x6ad58c) * 0x2f4) = 0;
            D(D(0x1015ea0) + 0x60 + D(0x6ad590) * 0x2f4) = 1;
            D(D(0x1015ea0) + 0x60 + D(0x6ad594) * 0x2f4) = 1;
            D(D(0x1015ea0) + 0x5c + D(0x6ad588) * 0x2f4) = 1;
            D(D(0x1015ea0) + 0x1d0 + D(0x6ad588) * 0x2f4) = 3;
            D(D(0x1015ea0) + 0x5c + D(0x6ad58c) * 0x2f4) = 1;
            D(D(0x1015ea0) + 0x1d0 + D(0x6ad58c) * 0x2f4) = 3;
            if (D(0x100f1dc) != -1) {
                if (clicked == D(0x6ad588) || clicked == D(0x6ad58c)) {
                    control = D(0x1015ea0) + 0x38 + clicked * 0x2f4;
                    D(control) = !D(control);
                    choice = clicked == D(0x6ad588) ? D(0x6ad58c) : D(0x6ad588);
                    D(D(0x1015ea0) + 0x38 + choice * 0x2f4) = 0;
                    fcn_00472640(D(0x6ad574), D(control) != 0);
                } else if (clicked == D(0x6ad574) || clicked == D(0x6ad578)) {
                    fcn_00472640(D(0x6ad574), 0);
                    if (clicked == D(0x6ad574)) {
                        if (D(D(0x1015ea0) + 0x38 + D(0x6ad588) * 0x2f4)) fcn_004a8750(0);
                        else if (D(D(0x1015ea0) + 0x38 + D(0x6ad58c) * 0x2f4)) fcn_004a8750(1);
                    }
                    flags = fcn_004a6f50();
                    fcn_005e7b70(0, 4, (void *)0x7765ac);
                    fcn_005e7b70(1, 4, (void *)0x7765e0);
                    fcn_005e7b70(2, 4, (void *)0x776614);
                } else if (clicked == D(0x6ad570)) D(0x774654) = 1;
            }
            break;
        case 7:
            D(D(0x1015ea0) + 0x60 + D(0x6ad588) * 0x2f4) = 1;
            D(D(0x1015ea0) + 0x60 + D(0x6ad58c) * 0x2f4) = 1;
            D(D(0x1015ea0) + 0x60 + D(0x6ad590) * 0x2f4) = 0;
            D(D(0x1015ea0) + 0x60 + D(0x6ad594) * 0x2f4) = 0;
            D(D(0x1015ea0) + 0x5c + D(0x6ad588) * 0x2f4) = 0;
            D(D(0x1015ea0) + 0x1d0 + D(0x6ad588) * 0x2f4) = 0;
            D(D(0x1015ea0) + 0x5c + D(0x6ad58c) * 0x2f4) = 0;
            D(D(0x1015ea0) + 0x1d0 + D(0x6ad58c) * 0x2f4) = 0;
            d2_SetForm(D(0x6ad568), 4);
            io_FormatTextBuffer(text, 0x4252, D(0x776640)); io_AppendText(text);
            sprintf(text, (char *)D(D(0x7765fc) != -1 ? 0x14b5c90 : 0x14b5c94), D(0x7765d8) + 0x30, D(0x7765d8) + 0x40); io_AppendText(text);
            sprintf(text, (char *)D(D(0x776630) != -1 ? 0x14b5c90 : 0x14b5c94), D(0x77660c) + 0x30, D(0x77660c) + 0x40); io_AppendText(text);
            if (D(0x100f1dc) != -1 && D(0x6ad578) == D(0x67d370)) flags = fcn_004a6f50();
            break;
        case 10:
            fcn_004a6f50();
            fcn_005e7b70(0, 5, (void *)0x7765ac); fcn_005e7b70(1, 5, (void *)0x7765e0); fcn_005e7b70(2, 5, (void *)0x776614);
            d2_SetForm(D(0x6ad568), 4);
            if (W(0x776658)) {
                choice = D(0x7765a4 + W(0x776658) * 0x34);
                io_FormatTextBuffer(text, 0x4264, choice + 0x30, choice + 0x40, D(0x77665c) + 0x4266, D(0x776640));
            } else io_FormatTextBuffer(text, 0x4265, D(0x77665c) + 0x4266, D(0x776640));
            io_AppendText(text);
            break;
        case 11:
            if (D(0x100f1dc) != -1 && D(0x6ad578) == clicked) D(0x774654) = 1;
            break;
        }
    } while (fcn_005373e0((void *)fcn_005e6e00, 0x777c7));
    fcn_005e6dd0();
    return 1;
}
