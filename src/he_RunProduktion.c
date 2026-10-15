#include <string.h>
#include "client_types.h"
#include "client_actions.h"
#include "Develop/DieGildeAddOn/game/spiel.h"

extern pos14_7f4c00 g_7f4c00;
extern char g_7f4ca0[];
extern unsigned char* g_868050;
extern cell10_fb5760 g_fb5760[0x8000];

struct unit;
void* __cdecl gm_SearchTable67(int id);
int __cdecl gm_GetMsgField(char* objekt, char* eintrag);
void __cdecl fcn_0051af00(char* text, int format, ...);
int __cdecl fcn_004c4450(int id);
unsigned short* __cdecl fcn_00502cd0(int container_id, int arg_count, ...);
char* __cdecl fcn_005049a0(char* objekt);
char* __cdecl fcn_0050dc90(int objekt);
int __cdecl gm_eval_SlotVoll(char* objekt, int ware, int menge);
void __cdecl fcn_00500bb0(pos14_7f4c00* zeit, int a, int b, int c);
int __cdecl fcn_00500cb0(pos14_7f4c00* a, pos14_7f4c00* b);
int __cdecl fcn_0050c830(pos14_7f4c00* a, pos14_7f4c00* b, int modus);
int __cdecl fcn_0050c710(unsigned char* objekt, int art, int modus);
void __cdecl fcn_004c54c0(int besitzer, int objekt, int menge, int modus);
char* __cdecl fcn_00508e40(int id);
float __cdecl fcn_004ff040(void* objekt);
float __cdecl fcn_004eceb0(char* objekt, int ware);
int __cdecl fcn_005c6270(char* objekt, int id);
int __cdecl fcn_005c62c0(char* objekt, int id);
int __cdecl fcn_005743b0(char* objekt);
void __cdecl fcn_005290d0(char* objekt);
float __cdecl fcn_0050fdb0(int besitzer, int anzahl, int* ids);
struct unit* __cdecl fcn_005463a0(int anzahl, ...);
void __cdecl fcn_00546190(struct unit* objekt);
void __cdecl fcn_005467e0(int* objekt);
int __cdecl fcn_004c51f0(int a, int b, short ware, int menge, char besitzer, int modus);
int __cdecl fcn_004c5250(int objekt, unsigned short ware, int menge);
int __cdecl fcn_00545e80(int id, int arg, char* text, unsigned char flags,
    int typ, int x, int y, char* name, char* bild);
void __cdecl fcn_004c6300(int id);
void __cdecl fcn_00529160(char* objekt, int a, int besitzer, char* ereignis);

/* Field offsets and names below are inferred from the complete native body.
 * The original event type and its complete allocation remain unresolved. */
void __cdecl he_RunProduktion(char* e)
{
    char* gebaeude;
    char* lager;
    char* haus;
    char* haushalt;
    char* arbeiter;
    unsigned char* typ;
    unsigned short* rohstoff;
    unsigned short* eintrag;
    char* rezept;
    struct unit* nachricht;
    pos14_7f4c00* letzte_zeit;
    pos14_7f4c00* naechste_zeit;
    char bild[256];
    char text[1024];
    char debug[512];
    float leistung;
    float arbeitsleistung;
    float summe;
    int anzahl;
    int i;
    int* arbeiter_id;
    int differenz;
    int produziert;
    int nachricht_typ;

    bild[0] = 0;
    if (*(short*) (e + 8) == -1) {
        gebaeude = gm_SearchTable67(*(int*) (e + 0xbc));
        if (gebaeude != 0) {
            fcn_0051af00(debug, (int) "he_RunProduktion(): geb:%G", gebaeude);
        }
        fcn_00546190((struct unit*) e);
        return;
    }
    switch (*(int*) (e + 0x70)) {
    case 0:
        *(int*) (e + 0x70) = *(int*) (e + 0x70) + 1;
        return;
    case 1:
        if (*(int*) (e + 0x14) <= 0 && *(int*) (e + 0x18) <= 0) {
            *(int*) (e + 0x70) = *(int*) (e + 0x70) + 1;
            return;
        }
        if (*(int*) (e + 0xc4) != -1) {
            if (!fcn_004c4450(*(int*) (e + 0xc4))) {
                return;
            }
            gm_ResolveEntityById((void**) &gebaeude, 0, 0, *(int*) (e + 0xbc));
            if (gebaeude == 0) {
                *(int*) (e + 0x70) = -1;
                return;
            }
            typ = g_868050 + *(unsigned char*) gebaeude * 0x24d;
            if (fcn_004c4450(*(int*) (e + 0xc4)) == 2) {
                haushalt = 0;
                bild[0] = 0;
                haus = fcn_0050dc90((int) gebaeude);
                for (arbeiter = g_7f4ca0; arbeiter < g_7f4ca0 + 768 * 0x21c; arbeiter += 0x21c) {
                    if (*(char**) (arbeiter + 0x17c) == e) {
                        haushalt = arbeiter;
                    }
                }
                if (haushalt == 0 || (haus != 0 && (haus[0x1b4] & 1)) || *(int*) (e + 0xc8)) {
                    goto warten;
                }
                gm_ResolveEntityById(0, (void**) &lager, 0, *(int*) (e + 0xc0));
                haushalt = fcn_005049a0(gebaeude);
                if (fcn_00502cd0(*(int*) (lager + 0x14), 1, 0, *(unsigned short*) (e + 0xac)) != 0 &&
                    !gm_eval_SlotVoll(lager, *(unsigned short*) (e + 0xac), 1)) {
                    fcn_0051af00(text, 0x1bb3, gebaeude, *(unsigned short*) (e + 0xac) * 2 + 0x9a8);
                    strcpy(bild, "_NACHRICHTEN_HS_04");
                } else if (gm_eval_SlotVoll(lager, *(unsigned short*) (e + 0xac), 1)) {
                    if (g_fb5760[*(int*) (e + 0xc4)].f1 != 8) {
                        goto warten;
                    }
                    fcn_0051af00(text, 0x1bb2, gebaeude, *(unsigned short*) (e + 0xac) * 2 + 0x9a8);
                    if (*typ == 7) strcpy(bild, "_NACHRICHTEN_ROHSTOFFMANGEL_HS_01");
                    else if (*typ == 8) strcpy(bild, "_NACHRICHTEN_ROHSTOFFMANGEL_HS_03");
                    else if (*typ == 11) strcpy(bild, "_NACHRICHTEN_ROHSTOFFMANGEL_HS_05");
                    else if (*typ == 12) strcpy(bild, "_NACHRICHTEN_ROHSTOFFMANGEL_HS_07");
                    else if (*typ == 13) strcpy(bild, "_NACHRICHTEN_ROHSTOFFMANGEL_HS_09");
                    else if (*typ == 14) strcpy(bild, "_NACHRICHTEN_ROHSTOFFMANGEL_HS_11");
                    else if (*typ == 18) strcpy(bild, "_NACHRICHTEN_ROHSTOFFMANGEL_HS_13");
                    else if (*typ == 20) strcpy(bild, "_NACHRICHTEN_ROHSTOFFMANGEL_HS_15");
                    else if (*typ == 21) strcpy(bild, "_NACHRICHTEN_ROHSTOFFMANGEL_HS_17");
                    else if (*typ == 22) strcpy(bild, "_NACHRICHTEN_ROHSTOFFMANGEL_HS_19");
                    else if (*typ == 30) strcpy(bild, "_NACHRICHTEN_DOMIZIL_02");
                    else if (*typ == 32 || *typ == 31 || *typ == 29) strcpy(bild, "_NACHRICHTEN_ROHSTOFFMANGEL_HS_20");
                } else {
                    fcn_0051af00(text, 0x1bb4, gebaeude, *(unsigned short*) (e + 0xac) * 2 + 0x9a8);
                    strcpy(bild, "_NACHRICHTEN_HS_05");
                }
                arbeiter = g_7f4ca0 + *(unsigned short*) (gebaeude + 0x27) * 0x21c;
                if (arbeiter[2] == 6 || arbeiter[2] == 7) {
                    nachricht_typ = 0x5f1;
                    haus = fcn_0050dc90((int) gebaeude);
                    if (haus != 0 && (haus[0x1b4] & 1)) nachricht_typ = 0x60d;
                    fcn_00545e80(*(int*) (g_7f4ca0 + *(unsigned short*) (gebaeude + 0x27) * 0x21c + 4),
                        *(int*) (e + 4), text, 0, nachricht_typ,
                        *(int*) (gebaeude + 1), *(int*) (haushalt + 2), 0, bild[0] ? bild : 0);
                }
                if (gebaeude != 0 && *(int*) (gebaeude + 0x95) != -1) {
                    fcn_004c6300(*(int*) (gebaeude + 1));
                }
                *(int*) (e + 0xc8) = 1;
warten:
                *(int*) (e + 0xc4) = -1;
                fcn_00500bb0((pos14_7f4c00*) (e + 0x52), 0, 5, 0);
                return;
            }
        }
        gm_ResolveEntityById((void**) &gebaeude, 0, 0, *(int*) (e + 0xbc));
        if (gebaeude == 0) {
            *(int*) (e + 0x70) = -1;
            return;
        }
        if (*(int*) (gebaeude + 0x95) == -1) fcn_004c6300(*(int*) (gebaeude + 1));
        typ = g_868050 + *(unsigned char*) gebaeude * 0x24d;
        leistung = fcn_0050c710((unsigned char*) gebaeude, 1, 1) * 0.01 + 1.0;
        haus = fcn_0050dc90((int) gebaeude);
        if (haus == 0) haus = g_7f4ca0 + *(unsigned short*) (gebaeude + 0x27) * 0x21c;
        leistung += (haus[2] == 6 || haus[2] == 7) ? *(unsigned char*) (haus + 0x81) * (1.0 / 1008.0) : 0.0f;
        if ((gebaeude[0x5a] & 0x20) && fcn_005c62c0(gebaeude, 0x178)) leistung *= 0.5;
        if (*(unsigned char*) (e + 0xd0) >= 60) {
            anzahl = 0;
            summe = 0.0f;
            arbeiter_id = (int*) (e + 0x8c);
            for (i = 8; i != 0; --i, ++arbeiter_id) {
                if (*arbeiter_id != -1) {
                    if (*(int*) (gebaeude + 0x41) != 2) {
                        fcn_004c54c0(*(int*) (g_7f4ca0 + *(unsigned short*) (gebaeude + 0x27) * 0x21c + 4),
                            *arbeiter_id, 2 - *(int*) (gebaeude + 0x41), 0);
                    }
                    arbeiter = fcn_00508e40(*arbeiter_id);
                    if (arbeiter != 0) {
                        arbeitsleistung = fcn_004ff040(arbeiter);
                        if (arbeiter[0x165] == 27 || arbeiter[0x165] == 28) {
                            arbeitsleistung = (fcn_00507f10(arbeiter, 1) + 0.5) * arbeitsleistung;
                            if (arbeiter[0x1b4] & 1) arbeitsleistung = 0.01f;
                        }
                        if (arbeiter[0x1cc] & 4) arbeitsleistung = fcn_004eceb0(arbeiter, *(unsigned short*) (e + 0xac)) * arbeitsleistung;
                        if (fcn_005c6270(g_7f4ca0 + *(unsigned short*) (gebaeude + 0x27) * 0x21c, 0x2ba)) {
                            summe += arbeitsleistung * 1.25f;
                        } else {
                            summe += arbeitsleistung;
                        }
                    }
                    ++anzahl;
                }
            }
            if (anzahl != 0) {
                *(float*) (e + 0xd4) = summe / anzahl;
                if (fcn_005743b0(g_7f4ca0 + *(unsigned short*) (gebaeude + 0x27) * 0x21c)) {
                    *(float*) (e + 0xd4) *= 0.9f;
                }
            }
            fcn_005290d0(e);
            *(float*) (e + 0xcc) = (fcn_0050fdb0(*(unsigned short*) (gebaeude + 0x27), 8, (int*) (e + 0x8c)) - 0.5) * 0.25;
            e[0xd0] = 0;
        }
        letzte_zeit = (pos14_7f4c00*) (e + 0x60);
        differenz = fcn_0050c830(letzte_zeit, &g_7f4c00, 0);
        if (differenz > 0) e[0xd0] += (char) differenz;
        if (gebaeude[0x5b] & 0x10) leistung += 0.1f;
        leistung = (leistung + *(float*) (e + 0xcc) + (*(int*) (gebaeude + 0x41) - 2) * 0.1) * *(float*) (e + 0xd4);
        if (!gm_ResolveEntityById(0, (void**) &lager, 0, *(int*) (e + 0xc0)) ||
            (*(short*) lager != 0x2a && *(short*) lager != 0x116)) {
            break;
        }
        if (fcn_00502cd0(*(int*) (lager + 0x14), 1, 0, *(unsigned short*) (e + 0xac)) != 0 &&
            !gm_eval_SlotVoll(lager, *(unsigned short*) (e + 0xac), 1)) {
            fcn_0051af00(text, 0x1bb3, gebaeude, *(unsigned short*) (e + 0xac) * 2 + 0x9a8);
            strcpy(bild, "_NACHRICHTEN_HS_04");
        } else if (gm_eval_SlotVoll(lager, *(unsigned short*) (e + 0xac), 1)) {
            rohstoff = (unsigned short*) (g_99ec10 + *(unsigned short*) (e + 0xac) * 0x41 + 0x2e);
            for (i = 0; i < 4; ++i, ++rohstoff) {
                if (*rohstoff != 0) {
                    eintrag = fcn_00502cd0(*(int*) (lager + 0x14), 1, 0, *rohstoff);
                    if (eintrag == 0 || gm_GetMsgField(lager, (char*) eintrag) < rohstoff[-4]) {
                        fcn_0051af00(text, 0x1bb2, gebaeude, *(unsigned short*) (e + 0xac) * 2 + 0x9a8);
                        if (*typ == 7) strcpy(bild, "_NACHRICHTEN_ROHSTOFFMANGEL_HS_01");
                        else if (*typ == 8) strcpy(bild, "_NACHRICHTEN_ROHSTOFFMANGEL_HS_03");
                        else if (*typ == 11) strcpy(bild, "_NACHRICHTEN_ROHSTOFFMANGEL_HS_05");
                        else if (*typ == 12) strcpy(bild, "_NACHRICHTEN_ROHSTOFFMANGEL_HS_07");
                        else if (*typ == 13) strcpy(bild, "_NACHRICHTEN_ROHSTOFFMANGEL_HS_09");
                        else if (*typ == 14) strcpy(bild, "_NACHRICHTEN_ROHSTOFFMANGEL_HS_11");
                        else if (*typ == 18) strcpy(bild, "_NACHRICHTEN_ROHSTOFFMANGEL_HS_13");
                        else if (*typ == 20) strcpy(bild, "_NACHRICHTEN_ROHSTOFFMANGEL_HS_15");
                        else if (*typ == 21) strcpy(bild, "_NACHRICHTEN_ROHSTOFFMANGEL_HS_17");
                        else if (*typ == 22) strcpy(bild, "_NACHRICHTEN_ROHSTOFFMANGEL_HS_19");
                        else if (*typ == 32 || *typ == 31 || *typ == 29) strcpy(bild, "_NACHRICHTEN_ROHSTOFFMANGEL_HS_20");
                        goto mangel;
                    }
                }
            }
            if (*(int*) (e + 0xc8)) {
                nachricht = fcn_005463a0(2, 0, 0x11, 3, *(int*) (e + 4));
                if (nachricht != 0) fcn_00546190(nachricht);
                *(int*) (e + 0xc8) = 0;
                if (*(int**) (e + 0x88) != 0) {
                    fcn_005467e0(*(int**) (e + 0x88));
                    *(int**) (e + 0x88) = 0;
                }
                *letzte_zeit = *(pos14_7f4c00*) (e + 0x52);
            }
            naechste_zeit = (pos14_7f4c00*) (e + 0x52);
            if (fcn_00500cb0(naechste_zeit, &g_7f4c00) >= 0) return;
            do {
                rezept = g_99ec10 + *(unsigned short*) (e + 0xac) * 0x41;
                differenz = fcn_0050c830(letzte_zeit, naechste_zeit, 0);
                produziert = 0;
                *(float*) (e + 0xb4) -= (*(int*) (e + 0x14) * 1.3f + *(int*) (e + 0x18)) * differenz * leistung;
                if (*(float*) (e + 0xb4) <= 0.0f) {
                    do {
                        ++produziert;
                        *(float*) (e + 0xb4) += *(unsigned int*) (rezept + 0x22);
                        *(float*) (e + 0xb8) = *(float*) (e + 0xb4);
                    } while (*(float*) (e + 0xb4) <= 0.0f);
                    if (produziert != 0) {
                        *(int*) (e + 0xc4) = fcn_004c5250(*(int*) (e + 0xc0), *(unsigned short*) (e + 0xac), produziert);
                    }
                } else if (*(int*) (e + 0xc4) == -1 &&
                    fcn_00502cd0(*(int*) (lager + 0x14), 1, 0, *(unsigned short*) (e + 0xac)) == 0) {
                    *(int*) (e + 0xc4) = fcn_004c51f0(*(int*) (lager + 2), -1, *(unsigned short*) (e + 0xac), 0, g_773d75, 0);
                }
                *letzte_zeit = *naechste_zeit;
                fcn_00500bb0(naechste_zeit, 0, 1, 0);
            } while (fcn_00500cb0(naechste_zeit, &g_7f4c00) < 0);
            return;
        } else {
            fcn_0051af00(text, 0x1bb4, gebaeude, *(unsigned short*) (e + 0xac) * 2 + 0x9a8);
            strcpy(bild, "_NACHRICHTEN_HS_05");
        }
mangel:
        haushalt = fcn_005049a0(gebaeude);
        arbeiter = g_7f4ca0 + *(unsigned short*) (gebaeude + 0x27) * 0x21c;
        if (!*(int*) (e + 0xc8) && (arbeiter[2] == 6 || arbeiter[2] == 7)) {
            nachricht_typ = 0x5f1;
            haus = fcn_0050dc90((int) gebaeude);
            if (haus != 0 && (haus[0x1b4] & 1)) nachricht_typ = 0x60d;
            fcn_00545e80(*(int*) (g_7f4ca0 + *(unsigned short*) (gebaeude + 0x27) * 0x21c + 4),
                *(int*) (e + 4), text, 0, nachricht_typ,
                *(int*) (gebaeude + 1), haushalt != 0 ? *(int*) (haushalt + 2) : -1, 0, bild);
        }
        if (gebaeude != 0 && !*(int*) (e + 0xc8) && *(int*) (gebaeude + 0x95) != -1) {
            fcn_004c6300(*(int*) (gebaeude + 1));
        }
        *(int*) (e + 0xc8) = 1;
        *(int*) (e + 0xc4) = -1;
        fcn_00500bb0((pos14_7f4c00*) (e + 0x52), 0, 5, 0);
        *letzte_zeit = *(pos14_7f4c00*) (e + 0x52);
        return;
    case 2:
        if (*(int*) (e + 0x14) > 0 || *(int*) (e + 0x18) > 0) {
            *(int*) (e + 0x70) = 1;
            return;
        }
        gm_ResolveEntityById((void**) &gebaeude, 0, 0, *(int*) (e + 0xbc));
        if (gebaeude == 0) {
            *(int*) (e + 0x70) = -1;
            return;
        }
        for (arbeiter = g_7f4ca0; arbeiter < g_7f4ca0 + 768 * 0x21c; arbeiter += 0x21c) {
            if (*(char**) (arbeiter + 0x17c) == e) fcn_00529160(gebaeude, 0, *(unsigned short*) arbeiter, 0);
        }
        if (gebaeude != 0) {
            fcn_004c6300(*(int*) (gebaeude + 1));
            fcn_00546190((struct unit*) e);
            return;
        }
        break;
    case -2:
    case -1:
        gm_ResolveEntityById((void**) &gebaeude, 0, 0, *(int*) (e + 0xbc));
        if (gebaeude != 0) fcn_004c6300(*(int*) (gebaeude + 1));
        for (arbeiter = g_7f4ca0; arbeiter < g_7f4ca0 + 768 * 0x21c; arbeiter += 0x21c) {
            if (*(char**) (arbeiter + 0x17c) == e) fcn_00529160(0, 0, *(unsigned short*) arbeiter, 0);
        }
        break;
    default:
        return;
    }
    fcn_00546190((struct unit*) e);
}
