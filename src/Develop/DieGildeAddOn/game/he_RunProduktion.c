#include <string.h>
#include "client_types.h"
#include "client_actions.h"
#include "Develop/DieGildeAddOn/game/spiel.h"
#include "Develop/DieGildeAddOn/game/object_prototype.h"
extern pos14_7f4c00 gm_GameTime;
#include "Develop/DieGildeAddOn/game/entity_record.h"
extern unsigned char* lpGebaeudePROT;
extern COMMAND_STATUS_SLOT g_fb5760[0x8000];
#include "Develop/DieGildeAddOn/game/building_prototype.h"
struct unit;
void* __cdecl gm_SearchTable67(int id);
int __cdecl gm_GetMsgField(char* objekt, char* eintrag);
void __cdecl io_FormatTextBuffer(char* text, int format, ...);
int __cdecl cm_GetCommandStatus(int id);
unsigned short* __cdecl fcn_00502cd0(int container_id, int arg_count, ...);
char* __cdecl gm_FindBuildingPrimarySlot(char* objekt);
char* __cdecl gm_FindBuildingOwner(int objekt);
int __cdecl gm_eval_SlotVoll(char* objekt, int ware, int menge);
void __cdecl gm_AddTime(pos14_7f4c00* zeit, int a, int b, int c);
int __cdecl gm_CompareGameTime(pos14_7f4c00* a, pos14_7f4c00* b);
int __cdecl fcn_0050c830(pos14_7f4c00* a, pos14_7f4c00* b, int modus);
int __cdecl gm_GetBuildingTechEffect(unsigned char* objekt, int art, int modus);
void __cdecl cm_RequestCopyEntityData(int besitzer, int objekt, int menge, int modus);
char* __cdecl gm_LookupEntityRecordById(int id);
float __cdecl gm_GetEntityHealthRatio(void* objekt);
float __cdecl ahm_CalcRecipeProductivityBonus(char* objekt, int ware);
int __cdecl gm_HasActiveSpecialObject(char* objekt, int id);
int __cdecl gm_HasActiveSpecialObjectOnEntity(char* objekt, int id);
int __cdecl he_HasZigeunerAction0x9f(char* objekt);
void __cdecl gm_CountBuildingWorkers(char* objekt);
float __cdecl gm_CalcAvgEntityFavor(int besitzer, int anzahl, int* ids);
struct unit* __cdecl he_StartHandlungSearch(int anzahl, ...);
void __cdecl he_FreeAction(struct unit* objekt);
void __cdecl d3_FreeEventGfxSlot(int* objekt);
int __cdecl cm_SendSellObjekt(int a, int b, short ware, int menge, char besitzer, int modus);
int __cdecl cm_SendProdObjekt(int objekt, unsigned short ware, int menge);
int __cdecl he_MessageBoxQuickjump(int id, int arg, char* text, unsigned char flags,
    int typ, int x, int y, char* name, char* bild);
void __cdecl cm_RequestUpdateBuildingSmoke(int id);
void __cdecl he_AssignActionSlot(char* objekt, int a, int besitzer, char* ereignis);

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
    char bild[260];
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
    if (*(unsigned short*) (e + 8) == 0xffff) {
        gebaeude = gm_SearchTable67(*(int*) (e + 0xbc));
        if (gebaeude != 0) {
            io_FormatTextBuffer(debug, (int) "he_RunProduktion(): geb:%G", gebaeude);
        }
    } else {
    switch (*(int*) (e + 0x70)) {
    case 1:
        if (*(int*) (e + 0x14) <= 0 && *(int*) (e + 0x18) <= 0) {
            *(int*) (e + 0x70) = *(int*) (e + 0x70) + 1;
            return;
        }
        if (*(int*) (e + 0xc4) != -1) {
            if (!cm_GetCommandStatus(*(int*) (e + 0xc4))) {
                return;
            }
            gm_ResolveEntityById((void**) &gebaeude, 0, 0, *(int*) (e + 0xbc));
            if (gebaeude == 0) {
                *(int*) (e + 0x70) = -1;
                return;
            }
            typ = (unsigned char*)&((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*(unsigned char*)gebaeude];
            if (cm_GetCommandStatus(*(int*) (e + 0xc4)) == 2) {
                haushalt = 0;
                bild[0] = 0;
                haus = gm_FindBuildingOwner((int) gebaeude);
                for (arbeiter = g_7f4ca0; (int) arbeiter < (int) ((char*)&((ENTITY_RECORD*)g_7f4ca0)[768]); arbeiter += sizeof(ENTITY_RECORD)) {
                    if (*(char**) (arbeiter + 0x17c) == e) {
                        haushalt = arbeiter;
                    }
                }
                if (haushalt == 0 || (haus != 0 && (haus[0x1b4] & 1)) || *(int*) (e + 0xc8)) {
                    goto warten;
                }
                gm_ResolveEntityById(0, (void**) &lager, 0, *(int*) (e + 0xc0));
                haushalt = gm_FindBuildingPrimarySlot(gebaeude);
                if (fcn_00502cd0(*(int*) (lager + 0x14), 1, 0, *(unsigned short*) (e + 0xac)) != 0 &&
                    !gm_eval_SlotVoll(lager, *(unsigned short*) (e + 0xac), 1)) {
                    io_FormatTextBuffer(text, 0x1bb3, gebaeude, *(unsigned short*) (e + 0xac) * 2 + 0x9a8);
                    strcpy(bild, "_NACHRICHTEN_HS_04");
                } else if (!gm_eval_SlotVoll(lager, *(unsigned short*) (e + 0xac), 1)) {
                    io_FormatTextBuffer(text, 0x1bb4, gebaeude, *(unsigned short*) (e + 0xac) * 2 + 0x9a8);
                    strcpy(bild, "_NACHRICHTEN_HS_05");
                } else {
                    if (g_fb5760[*(int*) (e + 0xc4)].f1 != 8) {
                        goto warten;
                    }
                    io_FormatTextBuffer(text, 0x1bb2, gebaeude, *(unsigned short*) (e + 0xac) * 2 + 0x9a8);
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
                }
                if (*(unsigned char*) ((char*)&((ENTITY_RECORD*)g_7f4ca0)[*(unsigned short*) (gebaeude + 0x27)] + 2) == 6 ||
                    *(unsigned char*) ((char*)&((ENTITY_RECORD*)g_7f4ca0)[*(unsigned short*) (gebaeude + 0x27)] + 2) == 7) {
                    nachricht_typ = 0x5f1;
                    haus = gm_FindBuildingOwner((int) gebaeude);
                    if (haus != 0 && (haus[0x1b4] & 1)) {
                        nachricht_typ = 0x60d;
                    }
                    if (bild[0]) {
                        he_MessageBoxQuickjump(*(int*) ((char*)&((ENTITY_RECORD*)g_7f4ca0)[*(unsigned short*) (gebaeude + 0x27)] + 4),
                            *(int*) (e + 4), text, 0, nachricht_typ,
                            *(int*) (gebaeude + 1), *(int*) (haushalt + 2), 0, bild);
                    } else {
                        he_MessageBoxQuickjump(*(int*) ((char*)&((ENTITY_RECORD*)g_7f4ca0)[*(unsigned short*) (gebaeude + 0x27)] + 4),
                            *(int*) (e + 4), text, 0, nachricht_typ,
                            *(int*) (gebaeude + 1), *(int*) (haushalt + 2), 0, 0);
                    }
                }
                if (gebaeude != 0 && *(int*) (gebaeude + 0x95) != -1) {
                    cm_RequestUpdateBuildingSmoke(*(int*) (gebaeude + 1));
                }
                *(int*) (e + 0xc8) = 1;
warten:
                *(int*) (e + 0xc4) = -1;
                gm_AddTime((pos14_7f4c00*) (e + 0x52), 0, 5, 0);
                return;
            }
        }
        gm_ResolveEntityById((void**) &gebaeude, 0, 0, *(int*) (e + 0xbc));
        if (gebaeude == 0) {
            *(int*) (e + 0x70) = -1;
            return;
        }
        if (*(int*) (gebaeude + 0x95) == -1) {
            cm_RequestUpdateBuildingSmoke(*(int*) (gebaeude + 1));
        }
        typ = (unsigned char*)&((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*(unsigned char*)gebaeude];
        leistung = gm_GetBuildingTechEffect((unsigned char*) gebaeude, 1, 1) * 0.01 + 1.0;
        haus = gm_FindBuildingOwner((int) gebaeude);
        if (haus == 0) {
            haus = (char*)&((ENTITY_RECORD*)g_7f4ca0)[*(unsigned short*) (gebaeude + 0x27)];
        }
        leistung = leistung + ((haus[2] == 6 || haus[2] == 7)
            ? (float) (*(unsigned char*) (haus + 0x81) * (1.0 / 1008.0)) : 0.0f);
        if ((gebaeude[0x5a] & 0x20) && gm_HasActiveSpecialObjectOnEntity(gebaeude, 0x178)) {
            leistung *= 0.5;
        }
        if (*(unsigned char*) (e + 0xd0) >= 60) {
            anzahl = 0;
            summe = 0.0f;
            arbeiter_id = (int*) (e + 0x8c);
            for (i = 8; i != 0; --i, ++arbeiter_id) {
                if (*arbeiter_id != -1) {
                    if (*(int*) (gebaeude + 0x41) != 2) {
                        cm_RequestCopyEntityData(*(int*) ((char*)&((ENTITY_RECORD*)g_7f4ca0)[*(unsigned short*) (gebaeude + 0x27)] + 4),
                            *arbeiter_id, 2 - *(int*) (gebaeude + 0x41), 0);
                    }
                    arbeiter = gm_LookupEntityRecordById(*arbeiter_id);
                    if (arbeiter != 0) {
                        arbeitsleistung = gm_GetEntityHealthRatio(arbeiter);
                        if (arbeiter[0x165] == 27 || arbeiter[0x165] == 28) {
                            arbeitsleistung = (gm_GetEntitySkill(arbeiter, 1) + 0.5) * arbeitsleistung;
                            if (arbeiter[0x1b4] & 1) {
                                arbeitsleistung = 0.01f;
                            }
                        }
                        if (arbeiter[0x1cc] & 4) {
                            arbeitsleistung = ahm_CalcRecipeProductivityBonus(arbeiter, *(unsigned short*) (e + 0xac)) * arbeitsleistung;
                        }
                        if (gm_HasActiveSpecialObject((char*)&((ENTITY_RECORD*)g_7f4ca0)[*(unsigned short*) (gebaeude + 0x27)], 0x2ba)) {
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
                if (he_HasZigeunerAction0x9f((char*)&((ENTITY_RECORD*)g_7f4ca0)[*(unsigned short*) (gebaeude + 0x27)])) {
                    *(float*) (e + 0xd4) *= 0.9f;
                }
            }
            gm_CountBuildingWorkers(e);
            *(float*) (e + 0xcc) = (gm_CalcAvgEntityFavor(*(unsigned short*) (gebaeude + 0x27), 8, (int*) (e + 0x8c)) - 0.5) * 0.25;
            e[0xd0] = 0;
        }
        letzte_zeit = (pos14_7f4c00*) (e + 0x60);
        differenz = fcn_0050c830(letzte_zeit, &gm_GameTime, 0);
        if (differenz > 0) {
            e[0xd0] += differenz;
        }
        if (gebaeude[0x5b] & 0x10) {
            leistung += 0.1f;
        }
        leistung = (leistung + *(float*) (e + 0xcc) + (*(int*) (gebaeude + 0x41) - 2) * 0.1) * *(float*) (e + 0xd4);
        if (!gm_ResolveEntityById(0, (void**) &lager, 0, *(int*) (e + 0xc0)) ||
            (*(short*) lager != 0x2a && *(short*) lager != 0x116)) {
            break;
        }
        if (fcn_00502cd0(*(int*) (lager + 0x14), 1, 0, *(unsigned short*) (e + 0xac)) != 0 &&
            !gm_eval_SlotVoll(lager, *(unsigned short*) (e + 0xac), 1)) {
            io_FormatTextBuffer(text, 0x1bb3, gebaeude, *(unsigned short*) (e + 0xac) * 2 + 0x9a8);
            strcpy(bild, "_NACHRICHTEN_HS_04");
        } else if (!gm_eval_SlotVoll(lager, *(unsigned short*) (e + 0xac), 1)) {
            io_FormatTextBuffer(text, 0x1bb4, gebaeude, *(unsigned short*) (e + 0xac) * 2 + 0x9a8);
            strcpy(bild, "_NACHRICHTEN_HS_05");
        } else {
            rohstoff = (unsigned short*) (((char *)&((OBJECT_PROTOTYPE *)lpObjektePROT)[*(unsigned short*) (e + 0xac)]) + 0x2e);
            for (i = 0; i < 4; ++i, ++rohstoff) {
                if (*rohstoff != 0) {
                    eintrag = fcn_00502cd0(*(int*) (lager + 0x14), 1, 0, *rohstoff);
                    if (eintrag == 0 || gm_GetMsgField(lager, (char*) eintrag) < rohstoff[-4]) {
                        io_FormatTextBuffer(text, 0x1bb2, gebaeude, *(unsigned short*) (e + 0xac) * 2 + 0x9a8);
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
                nachricht = he_StartHandlungSearch(2, 0, 0x11, 3, *(int*) (e + 4));
                if (nachricht != 0) {
                    he_FreeAction(nachricht);
                }
                *(int*) (e + 0xc8) = 0;
                if (*(int**) (e + 0x88) != 0) {
                    d3_FreeEventGfxSlot(*(int**) (e + 0x88));
                    *(int**) (e + 0x88) = 0;
                }
                *letzte_zeit = *(pos14_7f4c00*) (e + 0x52);
            }
            naechste_zeit = (pos14_7f4c00*) (e + 0x52);
            if (gm_CompareGameTime(naechste_zeit, &gm_GameTime) >= 0) {
                return;
            }
            do {
                rezept = ((char *)&((OBJECT_PROTOTYPE *)lpObjektePROT)[*(unsigned short*) (e + 0xac)]);
                differenz = fcn_0050c830(letzte_zeit, naechste_zeit, 0);
                produziert = 0;
                *(float*) (e + 0xb4) -= (*(int*) (e + 0x14) * 1.3f + *(int*) (e + 0x18)) * (float) differenz * leistung;
                if (*(float*) (e + 0xb4) <= 0.0f) {
                    do {
                        ++produziert;
                        *(float*) (e + 0xb4) += (double) ((OBJECT_PROTOTYPE *)rezept)->value_022;
                        *(float*) (e + 0xb8) = *(float*) (e + 0xb4);
                    } while (*(float*) (e + 0xb4) <= 0.0f);
                    if (produziert != 0) {
                        *(int*) (e + 0xc4) = cm_SendProdObjekt(*(int*) (e + 0xc0), *(unsigned short*) (e + 0xac), produziert);
                        goto lager_done;
                    }
                }
                if (*(int*) (e + 0xc4) == -1 &&
                    fcn_00502cd0(*(int*) (lager + 0x14), 1, 0, *(unsigned short*) (e + 0xac)) == 0) {
                    *(int*) (e + 0xc4) = cm_SendSellObjekt(*(int*) (lager + 2), -1, *(unsigned short*) (e + 0xac), 0, g_773d75, 0);
                }
lager_done:
                *letzte_zeit = *naechste_zeit;
                gm_AddTime(naechste_zeit, 0, 1, 0);
            } while (gm_CompareGameTime(naechste_zeit, &gm_GameTime) < 0);
            return;
        }
mangel:
        haushalt = gm_FindBuildingPrimarySlot(gebaeude);
        if (!*(int*) (e + 0xc8) &&
            (*(unsigned char*) ((char*)&((ENTITY_RECORD*)g_7f4ca0)[*(unsigned short*) (gebaeude + 0x27)] + 2) == 6 ||
             *(unsigned char*) ((char*)&((ENTITY_RECORD*)g_7f4ca0)[*(unsigned short*) (gebaeude + 0x27)] + 2) == 7)) {
            nachricht_typ = 0x5f1;
            haus = gm_FindBuildingOwner((int) gebaeude);
            if (haus != 0 && (haus[0x1b4] & 1)) {
                nachricht_typ = 0x60d;
            }
            if (haushalt != 0) {
                he_MessageBoxQuickjump(*(int*) ((char*)&((ENTITY_RECORD*)g_7f4ca0)[*(unsigned short*) (gebaeude + 0x27)] + 4),
                    *(int*) (e + 4), text, 0, nachricht_typ,
                    *(int*) (gebaeude + 1), *(int*) (haushalt + 2), 0, bild);
            } else {
                he_MessageBoxQuickjump(*(int*) ((char*)&((ENTITY_RECORD*)g_7f4ca0)[*(unsigned short*) (gebaeude + 0x27)] + 4),
                    *(int*) (e + 4), text, 0, nachricht_typ,
                    *(int*) (gebaeude + 1), -1, 0, bild);
            }
        }
        if (gebaeude != 0 && !*(int*) (e + 0xc8) && *(int*) (gebaeude + 0x95) != -1) {
            cm_RequestUpdateBuildingSmoke(*(int*) (gebaeude + 1));
        }
        *(int*) (e + 0xc8) = 1;
        *(int*) (e + 0xc4) = -1;
        gm_AddTime((pos14_7f4c00*) (e + 0x52), 0, 5, 0);
        *letzte_zeit = *(pos14_7f4c00*) (e + 0x52);
        return;
    case 0:
        *(int*) (e + 0x70) = *(int*) (e + 0x70) + 1;
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
        for (arbeiter = g_7f4ca0; (int) arbeiter < (int) ((char*)&((ENTITY_RECORD*)g_7f4ca0)[768]); arbeiter += sizeof(ENTITY_RECORD)) {
            if (*(char**) (arbeiter + 0x17c) == e) {
                he_AssignActionSlot(gebaeude, 0, *(unsigned short*) arbeiter, 0);
            }
        }
        if (gebaeude != 0) {
            cm_RequestUpdateBuildingSmoke(*(int*) (gebaeude + 1));
        }
        he_FreeAction((struct unit*) e);
        return;
    case -2:
    case -1:
        gm_ResolveEntityById((void**) &gebaeude, 0, 0, *(int*) (e + 0xbc));
        if (gebaeude != 0) {
            cm_RequestUpdateBuildingSmoke(*(int*) (gebaeude + 1));
        }
        for (arbeiter = g_7f4ca0; (int) arbeiter < (int) ((char*)&((ENTITY_RECORD*)g_7f4ca0)[768]); arbeiter += sizeof(ENTITY_RECORD)) {
            if (*(char**) (arbeiter + 0x17c) == e) {
                he_AssignActionSlot(0, 0, *(unsigned short*) arbeiter, 0);
            }
        }
        break;
    default:
        return;
    }
    }
    he_FreeAction((struct unit*) e);
}
