#include "Develop/DieGildeAddOn/game/ch_motion.h"



extern char g_675328[];
void __cdecl d3_SetSubtreeVisible(void* p, int on);
void __cdecl d3_SetObjectVisible(void* p, int on);
#include "Develop/Units/Error/error_message.h"

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
