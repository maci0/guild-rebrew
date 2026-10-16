#include <string.h>
#include "Develop/DieGildeAddOn/game/game_data.h"

/* Inferred byte view: native stride and flag, without a string-capacity claim. */
typedef struct D3_UNIVERSE_VIEW {
    char unbekannt_000[0x3d5];
    unsigned char verwendet;
#ifdef REBREW_GOLD
    char unbekannt_3d6[10];
#else
    char unbekannt_3d6[6];
#endif
} D3_UNIVERSE_VIEW;

extern char g_7f3b40[];
extern char* g_7746cc;
extern char g_10432c0[];
#ifdef REBREW_GOLD
#define fcn_00413160 fcn_00411bb0
#define fcn_00510c90 fcn_0050d7f0
#endif
int __cdecl fcn_00413160(void);
void __cdecl fcn_00510c90(int object_type);

/* ADDRESS: GOLDTL 0x00515540 */
/* ADDRESS: GOLD 0x00511df0 */
int __cdecl fcn_00515540(char* object)
{
    int index;

    if (((signed char*) g_7f3b40)[*(unsigned short*) object] == -1) {
        if (object == g_7746cc) {
            fcn_00510c90(*(unsigned short*) object);
        } else {
            index = fcn_00413160();
            if (index == -1) {
                return index;
            }
            ((signed char*) g_7f3b40)[*(unsigned short*) object] = (signed char) index;
            ((D3_UNIVERSE_VIEW*) g_10432c0)[index].verwendet = 1;
            strcpy((char*) &((D3_UNIVERSE_VIEW*) g_10432c0)[index],
                g_item_def_table + *(unsigned short*) object * 0x41 + 1);
        }
    }
    return ((signed char*) g_7f3b40)[*(unsigned short*) object];
}
