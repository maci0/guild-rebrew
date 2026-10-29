#include <string.h>
#include "client_actions.h"
#include "Develop/rebrew_types.h"
#include "Develop/rebrew_globals.h"

void __cdecl fcn_004c4eb0(char* name);
void __cdecl fcn_004c4ef0(char* name);
int __cdecl fcn_0050d170(int id);
void __cdecl fcn_004c5150(int a, int b, char c, int preis);
void __cdecl fcn_004c5530(char* paket);
int __cdecl amt_ExecGebaeudeBauen(char* kontext, char* ziel, char* aktion);

int __cdecl RunBuergermeister(char* objekt, char* ziel, char* aktion)
{
    char paket[0xf8];
    char* spieler;

    spieler = fcn_00507ab0(1);
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
        fcn_004c4eb0("upgr_arbeiter_unterk");
        fcn_004c5150(-1, *(int*) (spieler + 2), (char) g_773d75,
            (int) (fcn_0050d170(*(int*) (ziel + 4)) * 0.3f));
        fcn_004c5530(paket);
        fcn_004c4ef0("upgr_arbeiter_unterk");
        return 0x2e;
    } else {
        fcn_004c4eb0("bau_arbeiter_unterk");
        if (amt_ExecGebaeudeBauen(g_773da8, ziel, aktion)) {
            fcn_004c5150(-1, *(int*) (spieler + 2), (char) g_773d75,
                fcn_0050d170(*(int*) (ziel + 4)));
            fcn_004c4ef0("bau_arbeiter_unterk");
            return 0x2e;
        } else {
            fcn_004c4ef0("bau_arbeiter_unterk");
            return 0;
        }
    }
out0:
    return 0;
}
