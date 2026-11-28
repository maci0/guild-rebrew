#include "Develop/DieGildeAddOn/game/ch_motion.h"
#include "Develop/Units/Error/error_message.h"

extern char g_675328[];
char __cdecl d3_SetSubtreeVisible(void* model, int visible);
char __cdecl d3_SetObjectVisible(void* model, int visible);
void __cdecl d3_UpdateObjectLighting(int model);

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x00402480 */
void __cdecl ch_SetVisible(char* character, int visible)
{
    if (character == 0 || *(int*) (character + 0x34) == 0) {
        ReportClientMessage("ch_SetVisible(): invalid character");
        return;
    }
    d3_SetSubtreeVisible(*(void**) (character + 0x34), visible);
    if (*(char**) (character + 0x64) != 0) {
        d3_SetObjectVisible(*(char**) (character + 0x64), visible);
    }
    if (visible != 0) {
        d3_UpdateObjectLighting(*(int*) (character + 0x34));
    }
    if (*(int**) (character + 0x124) != 0) {
        d3_SetSubtreeVisible((void*) **(int**) (character + 0x124), visible);
        if (visible != 0) {
            d3_UpdateObjectLighting(**(int**) (character + 0x124));
        }
    }
    if (*(char**) (character + 0x22c) != 0) {
        d3_SetObjectVisible(*(char**) (character + 0x22c), visible);
    }
    if (visible != 0) {
        *(unsigned short*) (character + 0x8c) &= 0xffdf;
    } else {
        *(unsigned short*) (character + 0x8c) |= 0x20;
    }
    ch_Updatelowpoly(character);
}
#else
/* ADDRESS: GOLDTL 0x00402a00 */
/* ADDRESS: GOLDDE 0x004022c0 */
void __cdecl ch_SetVisible(char* e, int on)
{
	if (e != 0 && *(void**) (e + 0x34) != 0) {
		d3_SetSubtreeVisible(*(void**) (e + 0x34), on);
		if (*(void**) (e + 0x64) != 0) {
			d3_SetObjectVisible(*(void**) (e + 0x64), on);
		}
		if (*(void***) (e + 0x124) != 0) {
			d3_SetSubtreeVisible(**(void***) (e + 0x124), on);
		}
		if (*(void**) (e + 0x22c) != 0) {
			d3_SetObjectVisible(*(void**) (e + 0x22c), on);
		}
		if (on) {
			*(short*) (e + 0x8c) &= ~0x20;
		} else {
			*(short*) (e + 0x8c) |= 0x20;
		}
		ch_Updatelowpoly(e);
		return;
	}
	ReportClientMessage(g_675328);
}
#endif
