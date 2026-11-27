#include <stdarg.h>
#include <stdio.h>
#include "client_types.h"
void* __cdecl m_alloc(unsigned int, const char*);
void __cdecl m_FreeTracked(void*);
int __cdecl d3_FindSceneObjectByName(int, int);
char __cdecl d3_SetObjectVisible(char*, char);
char* __cdecl fcn_00446e10(char*, float*, float*, char*);
void __cdecl d3_UpdateObjectLighting(char*);
int __cdecl fcn_00474b20(int, int, int);
void __cdecl fcn_00474d80(int, void*, void*);
void __cdecl fcn_00474e70(int);
void __cdecl fcn_004754c0(int, int);
void __cdecl fcn_00437060(int);
SOUND_VOICE* __cdecl sb_PlayVoice(char*, const char*, int, int, int, int, int);

/* ADDRESS: GOLD 0x0052f390 */
char* __cdecl fcn_0052f390(int model, char* parent, signed char count, ...)
{
    char* book;
    char* object;
    char upper[96];
    char lower[96];
    int i;
    int page;
    va_list ap;

    book = (char*)m_alloc(0x274, "f3_sv:OpenBook:b");
    if (book == 0) {
        return 0;
    }
    object = (char*)d3_FindSceneObjectByName(model, 1);
    *(char**)book = object;
    if (object == 0) {
        m_FreeTracked(book);
        return 0;
    }
    if (parent != 0) {
        d3_SetObjectVisible(object, 0);
        *(char**)(book + 4) = *(char**)book;
        object = *(char**)book;
        *(char**)book = fcn_00446e10(*(char**)(object + 0x1f8), (float*)(object + 0x4c), (float*)(object + 0x84), parent);
    } else {
        *(int*)(book + 4) = 0;
    }
    *(unsigned char*)(*(char**)book + 0x210) &= 0xdf;
    d3_UpdateObjectLighting(*(char**)book);
    book[0x271] = count;
    book[0x270] = 0;
    *(int*)(book + 0x268) = -1;
    *(int*)(book + 0x26c) = -1;
    va_start(ap, count);
    for (i = 0; i < count; i++) {
        page = fcn_00474b20(0, 0, va_arg(ap, int));
        ((int*)(book + 0x228))[i] = page;
        if (page == 0) {
            va_end(ap);
            m_FreeTracked(book);
            return 0;
        }
        sprintf(upper, "Buch_Seite%i_oben_ns_nm", i + 1);
        sprintf(lower, "Buch_Seite%i_unten_ns_nm", i + 1);
        fcn_00474d80(((int*)(book + 0x228))[i], upper, lower);
        fcn_00474e70(((int*)(book + 0x228))[i]);
        if (i > 2) {
            fcn_004754c0(((int*)(book + 0x228))[i], 0);
        }
    }
    va_end(ap);
    {
        char flag;

        flag = *(char*)0x63342d;
        if (flag != 0) {
            book[0x272] = flag;
            fcn_00437060(0);
        }
    }
    sb_PlayVoice(*(char**)0x6f240c, "Aufklappen_s", 1, 0x3f, 0x7f, 0, 0);
    return book;
}
