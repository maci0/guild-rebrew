#include <string.h>

#pragma pack(push, 2)
/* SIZE 0xe */
typedef struct {
    int a;
    int b;
    int c;
    short d;
} Stamp_54fd60;
#pragma pack(pop)

/* SIZE 0x8 */
typedef struct {
    unsigned short slot;
    unsigned char type;
    char pad3;
    int id;
} Entity_54fd60;

/* SIZE 0xb8 */
typedef struct {
    char pad0[0x52];
    Stamp_54fd60 stamp;
    char pad60[0x10];
    int state;
    char pad74[4];
    unsigned char flags;
    char pad79[0xb];
    int event;
    char pad88[0x24];
    int actor;
    int target;
    int mode;
} Order_54fd60;

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern int g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern unsigned short g_774970;
extern char g_7f4ca4[];

Entity_54fd60* __cdecl gm_LookupEntityRecordById(int);
void __cdecl fcn_004c5420(int, int, int, int, int);
int __cdecl fcn_004c5620(int, Order_54fd60*);
void __cdecl fcn_00500bb0(Stamp_54fd60*, int, int, int);
void __cdecl fcn_00546190(Order_54fd60*);
int __cdecl fcn_004c5980(void*);
int __cdecl fcn_004c4450(int);

/* ADDRESS: GOLDTL 0x0054fd60 */
void __cdecl fcn_0054fd60(Order_54fd60* o)
{
    char msg[0x114];
    Entity_54fd60* a;
    Entity_54fd60* b;

    if (o->event != -1 && fcn_004c4450(o->event) == 0) {
        return;
    }
    o->event = -1;
    switch (o->state) {
    case 2:
        if ((o->flags & 2) == 0) {
            return;
        }
        a = gm_LookupEntityRecordById(o->actor);
        b = gm_LookupEntityRecordById(o->target);
        if (a != 0) {
            if (b != 0) {
                memset(msg, 0, sizeof(msg));
                *(int*) (msg + 0x34) = a->id;
                *(int*) (msg + 0x1c) = g_7f4c04;
                msg[8] = 4;
                msg[0x26] = 0xa2;
                *(int*) (msg + 0x14) = -1;
                msg[0x30] = 2;
                *(int*) (msg + 0xc) = *(int*) (g_7f4ca4 + (unsigned short) g_774970 * 0x21c);
                *(int*) (msg + 0x38) = b->id;
                *(int*) (msg + 0x18) = (*(int*) &g_7f4c00);
                msg[0x7c] = 0;
                *(int*) (msg + 0x20) = g_7f4c08;
                *(short*) (msg + 0x24) = g_7f4c0c;
                fcn_00500bb0((Stamp_54fd60*) (msg + 0x18), 0, 0x1e, 0);
                fcn_004c5980(msg);
            }
            fcn_004c5420(a->id, 0x1c8, 4, 0, 0x400);
        }
        if (b != 0) {
            fcn_004c5420(b->id, 0x1c8, 4, 0, 0x400);
        }
        o->stamp = (*(Stamp_54fd60*) &g_7f4c00);
        fcn_00500bb0(&o->stamp, 0, 2, 0);
        o->event = fcn_004c5620(-1, o);
        return;
    case 1:
        if ((o->flags & 2) == 0) {
            return;
        }
        a = gm_LookupEntityRecordById(o->actor);
        b = gm_LookupEntityRecordById(o->target);
        if (a != 0) {
            fcn_004c5420(a->id, 0x1c8, 4, 0, 0x400);
        }
        if (b != 0) {
            fcn_004c5420(b->id, 0x1c8, 4, 0, 0x400);
        }
        o->stamp = (*(Stamp_54fd60*) &g_7f4c00);
        fcn_00500bb0(&o->stamp, 0, 2, 0);
        o->event = fcn_004c5620(-1, o);
        return;
    case -1:
    case -2:
        if ((o->flags & 2) != 0) {
            a = gm_LookupEntityRecordById(o->actor);
            b = gm_LookupEntityRecordById(o->target);
            if (a != 0) {
                fcn_004c5420(a->id, 0x1c8, 4, 0, 0x400);
            }
            if (b != 0) {
                fcn_004c5420(b->id, 0x1c8, 4, 0, 0x400);
            }
            o->stamp = (*(Stamp_54fd60*) &g_7f4c00);
            fcn_00500bb0(&o->stamp, 0, 2, 0);
            o->event = fcn_004c5620(-1, o);
        }
        fcn_00546190(o);
        return;
    }
}
