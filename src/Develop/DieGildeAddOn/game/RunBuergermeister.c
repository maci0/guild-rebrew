#include <string.h>
#include "client_actions.h"
#include "Develop/rebrew_types.h"
#include "Develop/rebrew_globals.h"

void __cdecl cm_SendLogAction(char* name);
void __cdecl cm_SendTraceEnd(char* name);
int __cdecl gm_GetTypeProductValue(int id);
void __cdecl cm_RequestMoveCredits(int a, int b, char c, int preis);
void __cdecl cm_SendCopyEntityData(char* paket);
int __cdecl amt_ExecGebaeudeBauen(char* kontext, char* ziel, char* aktion);

int __cdecl RunBuergermeister(char* objekt, char* ziel, char* aktion)
{
    char paket[0xf8];
    char* spieler;

    spieler = gm_FindPublicTreasury(1);
    if (spieler == 0 || (unsigned char) objekt[0x166] != 0x0f) {
        goto out0;
    }
    if (*aktion == 4) {
        memset(paket, 0, sizeof(paket));
        paket[4] = 0x1e;
        *(int*) (paket + 8) = *(int*) (objekt + 4);
        *(int*) (paket + 0xc) = *(int*) (aktion + 4);
        paket[0x36] = 1;
        *(int*) (paket + 0x28) = g_current_year;
        *(int*) (paket + 0x2c) = g_7f4c04;
        *(int*) (paket + 0x30) = g_7f4c08;
        *(short*) (paket + 0x34) = g_7f4c0c;
        *(int*) (paket + 0x58) = *(int*) (aktion + 4);
        cm_SendLogAction("upgr_arbeiter_unterk");
        cm_RequestMoveCredits(-1, *(int*) (spieler + 2), (char) g_773d75,
            (int) (gm_GetTypeProductValue(*(int*) (ziel + 4)) * 0.3f));
        cm_SendCopyEntityData(paket);
        cm_SendTraceEnd("upgr_arbeiter_unterk");
        return 0x2e;
    } else {
        cm_SendLogAction("bau_arbeiter_unterk");
        if (amt_ExecGebaeudeBauen(gm_CityEntity, ziel, aktion)) {
            cm_RequestMoveCredits(-1, *(int*) (spieler + 2), (char) g_773d75,
                gm_GetTypeProductValue(*(int*) (ziel + 4)));
            cm_SendTraceEnd("bau_arbeiter_unterk");
            return 0x2e;
        } else {
            cm_SendTraceEnd("bau_arbeiter_unterk");
            return 0;
        }
    }
out0:
    return 0;
}
