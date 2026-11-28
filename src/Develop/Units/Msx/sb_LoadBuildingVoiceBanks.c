#include <string.h>
#include "Develop/DieGildeAddOn/game/building_prototype.h"
extern unsigned char* lpGebaeudePROT;
extern int g_772e6c;
extern int g_772e70;
extern int g_772e74;
extern int g_772e7c;

int __cdecl sb_LoadLocalizedSampleBank(char*, int);


/* Loads the worker comment and greeting sound banks for the building type
 * of the given building. */
/* ADDRESS: GOLDTL 0x004c3170 */
void __cdecl sb_LoadBuildingVoiceBanks(unsigned char* b)
{
	char greet[256] = "";
	char cmd[256];
	char click[256];
	unsigned char* t;

	t = (unsigned char*)&((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*b];
	if ((((BUILDING_PROTOTYPE*)t)->category) == 4) {
		strcpy(cmd, "ARBEITER_KOMMENTARE_BEFEHL_DIEBE.sbf");
		strcpy(click, "ARBEITER_KOMMENTARE_KLICK_DIEBE.sbf");
	} else if ((((BUILDING_PROTOTYPE*)t)->category) == 0x10) {
		strcpy(cmd, "ARBEITER_KOMMENTARE_BEFEHL_RAEUBER.sbf");
		strcpy(click, "ARBEITER_KOMMENTARE_KLICK_RAEUBER.sbf");
	} else if ((((BUILDING_PROTOTYPE*)t)->category) == 0x13) {
		strcpy(cmd, "ARBEITER_KOMMENTARE_BEFEHL_SOELDNER.sbf");
		strcpy(click, "ARBEITER_KOMMENTARE_KLICK_SOELDNER.sbf");
	} else if ((((BUILDING_PROTOTYPE*)t)->category) == 0x1d) {
		strcpy(cmd, "ADDON\\ARBEITERKOMMENTARE_BEFEHL_GEHILFEN.sbf");
		strcpy(click, "ADDON\\ARBEITERKOMMENTARE_KLICK_GEHILFEN.sbf");
		strcpy(greet, "ADDON\\BEGRUESSUNG_FRIEDHOF.sbf");
	} else if ((((BUILDING_PROTOTYPE*)t)->category) == 0x20) {
		strcpy(cmd, "ADDON\\ARBEITERKOMMENTARE_BEFEHL_SCHNEIDER.sbf");
		strcpy(click, "ADDON\\ARBEITERKOMMENTARE_KLICK_SCHNEIDER.sbf");
		strcpy(greet, "ADDON\\BEGRUESSUNG_SCHNEIDER.sbf");
	} else if ((((BUILDING_PROTOTYPE*)t)->category) == 0x1f) {
		strcpy(cmd, "ADDON\\ARBEITERKOMMENTARE_BEFEHL_ZIGEUNER.sbf");
		strcpy(click, "ADDON\\ARBEITERKOMMENTARE_KLICK_ZIGEUNER.sbf");
		strcpy(greet, "ADDON\\BEGRUESSUNG_ZIGEUNER.sbf");
	} else if ((((BUILDING_PROTOTYPE*)t)->category) == 0x1e) {
		strcpy(cmd, "ADDON\\ARBEITER_KOMMENTARE_BEFEHL_ALCHIMIST.sbf");
		click[0] = 0;
		greet[0] = 0;
	} else {
		strcpy(cmd, "ARBEITER_KOMMENTARE_BEFEHL_HANDWERK.sbf");
		strcpy(click, "ARBEITER_KOMMENTARE_KLICK_HANDWERK.sbf");
		if ((((BUILDING_PROTOTYPE*)t)->category) == 7) {
			strcpy(greet, "BEGRUESSUNG_KIRCHE.sbf");
		} else if ((((BUILDING_PROTOTYPE*)t)->category) == 5) {
			strcpy(greet, "BEGRUESSUNG_GELDLEIHE.sbf");
		} else if ((((BUILDING_PROTOTYPE*)t)->category) == 8 || (((BUILDING_PROTOTYPE*)t)->category) == 0xe) {
			strcpy(greet, "BEGRUESSUNG_KRAEUTERLADEN_PARFUEMERIE.sbf");
		} else if ((((BUILDING_PROTOTYPE*)t)->category) == 9) {
			strcpy(greet, "BEGRUESSUNG_LAGERHAUS.sbf");
		} else if ((((BUILDING_PROTOTYPE*)t)->category) == 0x15 || (((BUILDING_PROTOTYPE*)t)->category) == 0x14 || (((BUILDING_PROTOTYPE*)t)->category) == 0x12) {
			strcpy(greet, "BEGRUESSUNG_SCHMIEDE_STEIMETZ_TISCHLER.sbf");
		} else if ((((BUILDING_PROTOTYPE*)t)->category) == 0xb || (((BUILDING_PROTOTYPE*)t)->category) == 0xc || (((BUILDING_PROTOTYPE*)t)->category) == 0xd) {
			strcpy(greet, "BEGRUESSUNG_WALDSTUECK_STEINBRUCH_MINE.sbf");
		} else if ((((BUILDING_PROTOTYPE*)t)->category) == 0x16) {
			strcpy(greet, "BEGRUESSUNG_WIRTSHAUS.sbf");
		} else if ((((BUILDING_PROTOTYPE*)t)->category) == 0x1e) {
			strcpy(greet, "ADDON\\BEGRUESSUNG_DOMIZIL.sbf");
		}
	}
	if (cmd[0] != 0) {
		g_772e6c = sb_LoadLocalizedSampleBank(cmd, 0);
	}
	if (click[0] != 0) {
		g_772e70 = sb_LoadLocalizedSampleBank(click, 0);
	}
	if ((((BUILDING_PROTOTYPE*)t)->category) != 0x1d && (((BUILDING_PROTOTYPE*)t)->category) != 0x1e) {
		g_772e74 = sb_LoadLocalizedSampleBank("ARBEITER_KOMMENTARE_KLICK_GERAEUSCHE.sbf", 0);
	} else {
		g_772e74 = 0;
	}
	if (greet[0] != 0) {
		g_772e7c = sb_LoadLocalizedSampleBank(greet, 0);
	}
}
