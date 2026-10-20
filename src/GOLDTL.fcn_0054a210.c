#pragma pack(push, 2)
/* SIZE 0xe */
typedef struct {
    int a;
    int b;
    int c;
    short d;
} Stamp_54a210;
#pragma pack(pop)

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern int g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern char g_7f4ca0[];
extern int g_773da8;
extern char g_6a5998[];

void __cdecl fcn_00546190(char*);
int __cdecl fcn_004c4450(int);
void __cdecl fcn_005015e0(char**, int, int, int);
void __cdecl fcn_00500bb0(Stamp_54a210*, int, int, int);
int __cdecl fcn_004c5620(int, char*);
char* __cdecl fcn_00502cd0(int, int, int, int, int);
int __cdecl fcn_00500d20(Stamp_54a210*, Stamp_54a210*);
void __cdecl fcn_00549c50(int, char*, char*, int);
int __cdecl fcn_0042e410(int);
void __cdecl fcn_004c4eb0(char*);
void __cdecl fcn_004c6900(int*);
void __cdecl fcn_004c4ef0(char*);

/* ADDRESS: GOLDTL 0x0054a210 */
void __cdecl fcn_0054a210(char* a0)
{
    char* o;
    char* sel;
    char* rec;
    int ev;
    int none;
    int loc[3];

    o = a0;
    none = -1;
    if (*(int*) (o + 0x70) == none || *(int*) (o + 0x70) == -2) {
        fcn_00546190(o);
        return;
    }
    if (*(unsigned char*) (o + 0x78) & 4) {
        return;
    }
    ev = *(int*) (o + 0x84);
    if (ev != none && fcn_004c4450(ev) == 0) {
        return;
    }
    *(int*) (o + 0x84) = none;
    fcn_005015e0(&a0, 0, 0, *(int*) (o + 0xac));
    if (a0 == 0) {
        fcn_00500bb0((Stamp_54a210*) (o + 0x52), 0, 5, 0);
        fcn_004c5620(none, o);
        return;
    }
    sel = fcn_00502cd0(*(int*) (a0 + 0x5d), 2, 6, 0, 0x12d);
    if (sel == 0) {
        fcn_00500bb0((Stamp_54a210*) (o + 0x52), 0, 5, 0);
        fcn_004c5620(none, o);
        return;
    }
    if (*(unsigned short*) (a0 + 0x27) != 0xffff) {
        rec = g_7f4ca0 + *(unsigned short*) (a0 + 0x27) * 0x21c;
        if (rec != 0 && rec != (char*) g_773da8 && *(char*) (rec + 8) != 0 && *(char*) (rec + 2) != 0xf) {
            if (*(int*) (o + 0xc0) != 1) {
                if (fcn_00500d20((Stamp_54a210*) 0x7f4c00, (Stamp_54a210*) (o + 0xb0)) > 0) {
                    fcn_00500bb0((Stamp_54a210*) (o + 0x52), 1, 0, 0);
                    fcn_004c5620(0, o);
                    return;
                }
                fcn_00549c50(0x65786563, a0, sel, -1);
                *(Stamp_54a210*) (o + 0x52) = (*(Stamp_54a210*) &g_7f4c00);
                fcn_00500bb0((Stamp_54a210*) (o + 0x52), 1, 0, 0);
                *(Stamp_54a210*) (o + 0xb0) = (*(Stamp_54a210*) &g_7f4c00);
            }
            else {
                fcn_00549c50(0x6e657720, a0, sel, -1);
                *(int*) (o + 0xc0) = *(int*) (o + 0xc0) - 1;
                *(Stamp_54a210*) (o + 0x52) = (*(Stamp_54a210*) &g_7f4c00);
                fcn_00500bb0((Stamp_54a210*) (o + 0x52), 1, 0, 0);
                *(Stamp_54a210*) (o + 0xb0) = (*(Stamp_54a210*) &g_7f4c00);
            }
            fcn_00500bb0((Stamp_54a210*) (o + 0xb0), 0x18, 0, 0);
            *(int*) (o + 0xb6) = 0;
            *(short*) (o + 0xb4) = fcn_0042e410(4) + 0x13;
            fcn_004c5620(0, o);
            return;
        }
    }
    if (*(int*) (o + 0xc0) == 0) {
        loc[0] = 0x636c6572;
        loc[1] = none;
        loc[2] = *(int*) (a0 + 1);
        fcn_004c4eb0(g_6a5998);
        fcn_004c6900(loc);
        fcn_004c4ef0(g_6a5998);
        *(int*) (o + 0xc0) = *(int*) (o + 0xc0) + 1;
    }
    *(Stamp_54a210*) (o + 0x52) = (*(Stamp_54a210*) &g_7f4c00);
    fcn_00500bb0((Stamp_54a210*) (o + 0x52), 1, 0, 0);
    *(Stamp_54a210*) (o + 0xb0) = (*(Stamp_54a210*) &g_7f4c00);
    fcn_00500bb0((Stamp_54a210*) (o + 0xb0), 0x18, 0, 0);
    *(int*) (o + 0xb6) = 0;
    *(short*) (o + 0xb4) = fcn_0042e410(4) + 0x13;
    fcn_004c5620(0, o);
}
