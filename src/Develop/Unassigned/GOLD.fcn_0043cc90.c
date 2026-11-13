#include <string.h>
#include "client_scene_resources.h"
#include "Develop/Units/m_alloc/m_alloc.h"
typedef struct GOLD_RESET_COLOR { unsigned char a, b, c, d; } GOLD_RESET_COLOR;
void __cdecl fcn_0043d430(void*, void*, GOLD_RESET_COLOR);
void __cdecl fcn_00434b70(void*, int);

/* ADDRESS: GOLD 0x0043cc90 */
void __cdecl fcn_0043cc90(char* record)
{
    char* model;
    char** object;
    int i;

    if ((unsigned char) record[0x190] < 0xff || (record[0x192] & 1)) {
        GOLD_RESET_COLOR color;
        memset(&color, 0, sizeof(color));
        color.c = 0; color.a = 0xff;
        fcn_0043d430(*(void**) (record + 0x18), record, color);
    }
    if (*(int*) (record + 8) > 0 && *(void**) record != 0) {
        m_FreeTracked(*(void**) record);
        *(void**) record = 0;
        *(int*) (record + 8) = 0;
    }
    if (*(int*) (record + 0xc) > 0 && *(void**) (record + 4) != 0) {
        m_FreeTracked(*(void**) (record + 4));
        *(void**) (record + 4) = 0;
        *(int*) (record + 0xc) = 0;
    }
    if (*(void**) (record + 0x14) != 0) {
        if (*(char**) (record + 0x10) != 0) {
            for (i = 0; i < *(int*) (*(char**) (record + 0x10) + 0x1e0); i++) {
                if ((*(void***) (record + 0x14))[i] != 0) {
                    fcn_0045fbb0((*(void***) (record + 0x14))[i]);
                }
            }
        }
        m_FreeTracked(*(void**) (record + 0x14));
        *(void**) (record + 0x14) = 0;
    }
    model = *(char**) (record + 0x10);
    if (model != 0) {
        (*(void (__cdecl**)(char*)) (model + 0x1e8))(model);
        *(void**) (record + 0x10) = 0;
    }
    object = (char**) (record + 0x84);
    for (i = 3; i != 0; i--, object = (char**) ((char*) object + 0x7c)) {
        if (*object != 0) {
            fcn_00434b70(*object, 0);
            *object = 0;
        }
    }
}
