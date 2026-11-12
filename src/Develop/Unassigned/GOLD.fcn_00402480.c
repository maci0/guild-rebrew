char __cdecl fcn_00442d50(int model, unsigned char visible);
char __cdecl fcn_00442c00(char* model, char visible);
void __cdecl fcn_00453270(int model);
void __cdecl fcn_00402ba0(char* character);
void __cdecl ReportClientMessage(const char* message);

/* ADDRESS: GOLD 0x00402480 */
void __cdecl fcn_00402480(char* character, int visible)
{
    if (character == 0 || *(int*) (character + 0x34) == 0) {
        ReportClientMessage("ch_SetVisible(): invalid character");
        return;
    }
    fcn_00442d50(*(int*) (character + 0x34), visible);
    if (*(char**) (character + 0x64) != 0) {
        fcn_00442c00(*(char**) (character + 0x64), visible);
    }
    if (visible != 0) {
        fcn_00453270(*(int*) (character + 0x34));
    }
    if (*(int**) (character + 0x124) != 0) {
        fcn_00442d50(**(int**) (character + 0x124), visible);
        if (visible != 0) {
            fcn_00453270(**(int**) (character + 0x124));
        }
    }
    if (*(char**) (character + 0x22c) != 0) {
        fcn_00442c00(*(char**) (character + 0x22c), visible);
    }
    if (visible != 0) {
        character[0x8c] &= 0xdf;
        fcn_00402ba0(character);
        return;
    }
    character[0x8c] |= 0x20;
    fcn_00402ba0(character);
}
