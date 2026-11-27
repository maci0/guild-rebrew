char __cdecl d3_SetSubtreeVisible(int model, unsigned char visible);
char __cdecl d3_SetObjectVisible(char* model, char visible);
void __cdecl d3_UpdateObjectLighting(int model);
void __cdecl ch_Updatelowpoly(char* character);
void __cdecl ReportClientMessage(const char* message);

/* ADDRESS: GOLD 0x00402480 */
void __cdecl ch_SetVisible(char* character, int visible)
{
    if (character == 0 || *(int*) (character + 0x34) == 0) {
        ReportClientMessage("ch_SetVisible(): invalid character");
        return;
    }
    d3_SetSubtreeVisible(*(int*) (character + 0x34), visible);
    if (*(char**) (character + 0x64) != 0) {
        d3_SetObjectVisible(*(char**) (character + 0x64), visible);
    }
    if (visible != 0) {
        d3_UpdateObjectLighting(*(int*) (character + 0x34));
    }
    if (*(int**) (character + 0x124) != 0) {
        d3_SetSubtreeVisible(**(int**) (character + 0x124), visible);
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
