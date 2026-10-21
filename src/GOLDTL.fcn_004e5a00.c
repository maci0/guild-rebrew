#include <stdio.h>
#include <string.h>

#include "Develop/DieGildeAddOn/game/event_callbacks.h"

#pragma intrinsic(memset)

extern double dbl_6640e8;
extern double dbl_6629c8;

int __cdecl fcn_00508e40(int id);
void __cdecl fcn_004cfe00(void);
void __cdecl fcn_005373e0(int a, int b);
int __cdecl fcn_004730c0(int a, int b, int c, int d, char* e, int f, int g);
void __cdecl fcn_004e5980(void);
void __cdecl fcn_0042de90(char* a, int b);
void __cdecl fcn_00473a90(int a, int b);
void __cdecl fcn_005305a0(void);
void __cdecl ResetDisplayCounters(void);
void __cdecl fcn_00525ef0(void);
void __cdecl fcn_00469e70(void);
void __cdecl fcn_004da190(void);
void __cdecl fcn_00438da0(float a, float b, float c, float d, int e, int f,
    int g, int h, int i);
void __cdecl fcn_005270c0(int a);
int __cdecl fcn_00470820(int a, int b, char* c);
void __cdecl fcn_00471d80(int a, int b);
void __cdecl fcn_00471af0(int a, int b);
void __cdecl fcn_004e6c60(int a);
void __cdecl fcn_00471e30(int a);
void __cdecl fcn_004da280(void);
void __cdecl fcn_004e59c0(void);
void __cdecl fcn_0042def0(char* a);
void __cdecl fcn_00528fd0(void);
void __cdecl fcn_004432d0(int a, int b);
void __cdecl fcn_00459710(int a, int b);
void __cdecl fcn_004463f0(int a, int b, int c);
void __cdecl fcn_00516de0(int a, int b);
void __cdecl fcn_00443230(int a);
void __cdecl fcn_00473150(int a);
void __cdecl fcn_004c4510(int a, int b);
void __cdecl fcn_004c4700(int a, int b, char* c, int* d);
void __cdecl fcn_004c53a0(void);

#pragma optimize("y", off)

/* ADDRESS: GOLDTL 0x004e5a00 */
void __cdecl fcn_004e5a00(int* event)
{
    unsigned char* e;
    int flag;
    int ready;
    int saved_675308;
    int count;
    int saved_6b8061;
    int saved_6b5c34;
    int g480c;
    int g4808;
    int g4804;
    int g4800;
    float t;
    int s3a48;
    int s3a44;
    int s3a40;
    int s3a58;
    int s3a54;
    int s3a50;
    char text[0x200];
    char* fmt;
    int obj;
    int index;
    int i;
    int n;
    int q;
    int w;
    int saved_68bfc0;
    int id1;
    int id2;
    int a;
    int b;
    int flags;
    int* slot;
    int* record;
    int* unit;
    int* hop;

    e = (unsigned char*) event;
    saved_675308 = *(int*) 0x675308;
    saved_6b5c34 = *(int*) 0x6b5c34;
    sprintf(text, (char*) 0x68d604, e[8], *(int*) e);
    g4800 = *(int*) 0x1040480;
    g4804 = *(int*) 0x1040484;
    g4808 = *(int*) 0x1040488;
    g480c = *(int*) 0x104048c;
    *(int*) 0x9a9648 = *(int*) 0x6b8010;
    *(int*) 0x9b0e00 = *(int*) 0x6791c8;
    *(int*) 0x772f2c = 0;
    fcn_004cfe00();
    memset((void*) 0x9b0940, 0, 0x480);
    *(int*) 0x772f3c = 0;
    e[0x26] = (unsigned char) (e[0x26] | 4);
    if (*(int*) 0x7e46ac & 0x200000)
        e[0x26] = (unsigned char) (e[0x26] | 0x40);
    *(int*) 0x68bfb8 = 0x717c6;
    if (e[0x26] & 0x40)
        *(int*) 0x68bfb8 = 0x716c6;
    if (*(unsigned char*) 0x7747b0 & 8) {
        flag = 1;
        for (i = 0; i < (int) e[0x30]; i++) {
            slot = (int*) (e + 0x34 + i * 4);
            if (*slot != -1) {
                record = (int*) fcn_00508e40(*slot);
                if (record != 0 && *((unsigned char*) record + 2) == 6) {
                    flag = 0;
                    break;
                }
            }
        }
        for (i = 0; i < (int) e[0x30]; i++) {
            slot = (int*) (e + 0x34 + i * 4);
            if (*slot != -1) {
                record = (int*) fcn_00508e40(*slot);
                if (record != 0 && *((unsigned char*) record + 2) == 6) {
                    flag = 0;
                    break;
                }
            }
        }
        if (flag != 0) {
            if ((e[0x26] == 0) & 2)
                return;
        }
    }
    if (e[0x26] & 2) {
        if (*(unsigned char*) 0x7747b0 & 8) {
            if (flag != 0)
                goto mark;
        } else if (*(unsigned char*) 0x7747b0 & 4) {
            n = *(unsigned short*) 0x774970;
            if (fcn_004e6200(((int*) 0x7f4ca0)[n * 135 + 1], e) == 0)
                goto mark;
        }
    }
    if (*(int*) 0x772f3c != 0)
        goto resume;
    a = *(int*) 0x1040490;
    b = *(int*) 0x1040494;
    flags = (*(int*) 0x7e46ac & ~8) | 0x110080;
    *(int*) 0x772f50 = fcn_004730c0(0, 0, b, a, (char*) 0x67d67c, 0x5a, 1);
    while ((*(unsigned char*) *(int*) 0x772f50 & 4) == 0)
        fcn_005373e0(0, flags);
    s3a40 = *(int*) 0x7e3a40;
    s3a44 = *(int*) 0x7e3a44;
    s3a48 = *(int*) 0x7e3a48;
    s3a50 = *(int*) 0x7e3a50;
    s3a54 = *(int*) 0x7e3a54;
    s3a58 = *(int*) 0x7e3a58;
    if (*(unsigned char*) 0x7747b0 & 8)
        fcn_004e5980();
    fcn_0042de90((char*) 0x4e4a60, 0x46);
    saved_6b8061 = *(unsigned char*) 0x6b8061;
    *(unsigned char*) 0x6b8061 = 0;
    *(float*) 0x675308 = 0.6f;
    *(float*) 0x67a964 = 1.0f;
    *(int*) 0x6b5c34 = 0;
    fcn_00473a90(0, 0);
    fcn_005305a0();
    ResetDisplayCounters();
    fcn_00525ef0();
    unit = (int*) *(int*) 0x1015ea0;
    count = 0;
    *(unsigned char*) 0x100f8c0 = 0;
    for (i = 0; i < 0x400; i++) {
        if (*(int*) ((char*) unit + i * 0x2f4 + 0x20) != 0
            && *(int*) ((char*) unit + i * 0x2f4 + 0x48) == 0) {
            *(unsigned short*) (0x9b0020 + count * 2) = (unsigned short) i;
            *(int*) ((char*) unit + i * 0x2f4 + 0x48) = 1;
            unit = (int*) *(int*) 0x1015ea0;
            count++;
        }
    }
    fcn_00469e70();
    fcn_004da190();
    if (e[0x26] & 0x20) {
        q = *(int*) 0x1040490;
        w = *(int*) 0x1040494;
        *(int*) 0x68bfb8 &= 0xfffffeff;
        t = *(float*) 0x67d368 * *(float*) 0x66291c;
        fcn_00438da0((float) w,
            (float) q - *(float*) 0x67d368 * *(float*) 0x662d98, 0.0f, t,
            *(int*) 0x10529c8, *(int*) 0x10421a0, *(int*) 0x10432a4, w, q);
        *(int*) 0x1040488 = 0;
        *(int*) 0x1040480 = w;
        *(int*) 0x1040484 = (int) t;
        *(int*) 0x104048c = (int) ((float) q - t);
        if (*(int*) 0x6a2be0 != 0) {
            fcn_005270c0(0);
            ready = 1;
        } else {
            ready = 0;
        }
    }
    goto resume;

mark:
    *(int*) 0x772f3c = 1;
resume:
    if (*(int*) 0x772f40 == 0)
        fcn_004e4f10(event);
    saved_68bfc0 = *(int*) 0x68bfc0;
    if (e[8] == 2)
        fmt = (char*) 0x68d5ec;
    else if (e[0x26] & 0x20)
        fmt = (char*) 0x68d5c8;
    else
        fmt = (char*) 0x68d5b0;
    obj = fcn_00470820(0, 0, fmt);
    *(int*) (e + 0x2c) = obj;
    *(int*) 0x68bfc0 = obj;
    fcn_00471d80(obj, 3);
    if (*(int*) 0x772f3c != 0)
        fcn_00471af0(obj, 0);
    fcn_004e6c60(*(int*) (e + 0x78));
    sprintf(text, (char*) 0x68d58c, e[8]);
    *(int*) 0x772f40 = (int) e;
    (*(void (__cdecl**) (int*)) (g_9b0840 + e[8] * 20)) (event);
    fcn_00471e30(*(int*) (e + 0x2c));
    *(int*) 0x68bfc0 = saved_68bfc0;
    if (*(int*) 0x772f3c != 0)
        goto tail;
    fcn_004da280();
    *(int*) 0x6b5c34 = saved_6b5c34;
    if (*(unsigned char*) 0x7747b0 & 8)
        fcn_004e59c0();
    *(int*) 0x68bfbc = 0xa;
    fcn_0042def0((char*) 0x4e4a60);
    for (i = 0; i < count; i++) {
        index = *(unsigned short*) (0x9b0020 + i * 2);
        *(int*) ((char*) *(int*) 0x1015ea0 + index * 0x2f4 + 0x48) = 0;
    }
    if (e[0x26] & 0x20) {
        if (!(e[0x26] & 0x40) || (e[0x26] & 1)) {
            fcn_00438da0((float) (*(int*) 0x6a376c - *(int*) 0x6a3764),
                (float) (*(int*) 0x6a3770 - *(int*) 0x6a3768),
                (float) *(int*) 0x6a3764, (float) *(int*) 0x6a3768,
                *(int*) 0x10529c8, *(int*) 0x10421a0, *(int*) 0x10432a4,
                *(int*) 0x1040494, *(int*) 0x1040490);
            *(int*) 0x1040480 = g4800;
            *(int*) 0x1040484 = g4804;
            *(int*) 0x1040488 = g4808;
            *(int*) 0x104048c = g480c;
            if (ready != 0 && !(e[0x26] & 0x40)) {
                fcn_005270c0(1);
                fcn_00528fd0();
            }
        }
    }
tail:
    fcn_004432d0(*(int*) 0x9a9648, 0);
    if (*(int*) 0x6b89c0 != 0)
        fcn_00459710(*(int*) 0x6b89c0, 1);
    *(int*) 0x7e3a40 = s3a40;
    *(int*) 0x7e3a44 = s3a44;
    *(int*) 0x7e3a48 = s3a48;
    *(int*) 0x7e3a50 = s3a50;
    *(int*) 0x7e3a54 = s3a54;
    *(int*) 0x7e3a58 = s3a58;
    fcn_004463f0(0, 1, 0);
    if (*(int*) 0x7746c4 == 0 && *(int*) 0x7746c8 == 0)
        *(float*) 0x67a964 = (float) (dbl_6629c8
            - (double) (*(int*) 0x77666c & 0xff) * dbl_6640e8);
    *(unsigned char*) 0x6b8061 = (unsigned char) saved_6b8061;
    *(int*) 0x675308 = saved_675308;
    fcn_00516de0(*(int*) 0x6b8300, 0);
    fcn_00443230(1);
    if (*(int*) 0x772f50 != 0) {
        fcn_00473150(*(int*) 0x772f50);
        q = *(int*) 0x1040490;
        w = *(int*) 0x1040494;
        *(int*) 0x772f50 = 0;
        fcn_004730c0(0, 0, w, q, (char*) 0x67d67c, 0x5a, 0xa);
    }
    fcn_004e4f10(event);
    n = *(unsigned short*) 0x774970;
    if (*(int*) (e + 0xc) == ((int*) 0x7f4ca0)[n * 135 + 1]) {
        unit = (int*) (e + 0x34);
        for (hop = (int*) 0x9b0e20; hop < (int*) 0x9b43e0;
            hop = (int*) ((char*) hop + 0x35c)) {
            hop[1] = 0;
            hop[0] = 0;
            hop[2] = 0;
            if (*unit != -1) {
                record = (int*) fcn_00508e40(*unit);
                if (record != 0) {
                    id1 = -1;
                    fcn_004c4510((int) record, record[1]);
                    fcn_004c4700(4, 1,
                        (char*) record + 0x20c - *(int*) 0xaed32c, &id1);
                    fcn_004c53a0();
                }
            }
            unit++;
        }
    }
    n = *(int*) (e + 0xc);
    if (n != -1) {
        record = (int*) fcn_00508e40(n);
        if (record != 0) {
            id2 = -1;
            fcn_004c4510((int) record, record[1]);
            fcn_004c4700(4, 1, (char*) record + 0x20c - *(int*) 0xaed32c,
                &id2);
            fcn_004c53a0();
        }
    }
    *(int*) 0x772f40 = 0;
    *(int*) 0x6791c8 = *(int*) 0x9b0e00;
}
