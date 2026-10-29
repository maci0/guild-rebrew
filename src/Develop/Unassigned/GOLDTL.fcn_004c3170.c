#include <string.h>

extern unsigned char* lpGebaeudePROT;
extern int g_772e6c;
extern int g_772e70;
extern int g_772e74;
extern int g_772e7c;

int __cdecl fcn_004c3100(char*, int);


/* Loads the worker comment and greeting sound banks for the building type
 * of the given building. */
/* ADDRESS: GOLDTL 0x004c3170 */
void __cdecl fcn_004c3170(unsigned char* b)
{
	char greet[256] = "";
	char cmd[256];
	char click[256];
	unsigned char* t;

	t = lpGebaeudePROT + *b * 0x24d;
	if (*t == 4) {
		strcpy(cmd, "ARBEITER_KOMMENTARE_BEFEHL_DIEBE.sbf");
		strcpy(click, "ARBEITER_KOMMENTARE_KLICK_DIEBE.sbf");
	} else if (*t == 0x10) {
		strcpy(cmd, "ARBEITER_KOMMENTARE_BEFEHL_RAEUBER.sbf");
		strcpy(click, "ARBEITER_KOMMENTARE_KLICK_RAEUBER.sbf");
	} else if (*t == 0x13) {
		strcpy(cmd, "ARBEITER_KOMMENTARE_BEFEHL_SOELDNER.sbf");
		strcpy(click, "ARBEITER_KOMMENTARE_KLICK_SOELDNER.sbf");
	} else if (*t == 0x1d) {
		strcpy(cmd, "ADDON\\ARBEITERKOMMENTARE_BEFEHL_GEHILFEN.sbf");
		strcpy(click, "ADDON\\ARBEITERKOMMENTARE_KLICK_GEHILFEN.sbf");
		strcpy(greet, "ADDON\\BEGRUESSUNG_FRIEDHOF.sbf");
	} else if (*t == 0x20) {
		strcpy(cmd, "ADDON\\ARBEITERKOMMENTARE_BEFEHL_SCHNEIDER.sbf");
		strcpy(click, "ADDON\\ARBEITERKOMMENTARE_KLICK_SCHNEIDER.sbf");
		strcpy(greet, "ADDON\\BEGRUESSUNG_SCHNEIDER.sbf");
	} else if (*t == 0x1f) {
		strcpy(cmd, "ADDON\\ARBEITERKOMMENTARE_BEFEHL_ZIGEUNER.sbf");
		strcpy(click, "ADDON\\ARBEITERKOMMENTARE_KLICK_ZIGEUNER.sbf");
		strcpy(greet, "ADDON\\BEGRUESSUNG_ZIGEUNER.sbf");
	} else if (*t == 0x1e) {
		strcpy(cmd, "ADDON\\ARBEITER_KOMMENTARE_BEFEHL_ALCHIMIST.sbf");
		click[0] = 0;
		greet[0] = 0;
	} else {
		strcpy(cmd, "ARBEITER_KOMMENTARE_BEFEHL_HANDWERK.sbf");
		strcpy(click, "ARBEITER_KOMMENTARE_KLICK_HANDWERK.sbf");
		if (*t == 7) {
			strcpy(greet, "BEGRUESSUNG_KIRCHE.sbf");
		} else if (*t == 5) {
			strcpy(greet, "BEGRUESSUNG_GELDLEIHE.sbf");
		} else if (*t == 8 || *t == 0xe) {
			strcpy(greet, "BEGRUESSUNG_KRAEUTERLADEN_PARFUEMERIE.sbf");
		} else if (*t == 9) {
			strcpy(greet, "BEGRUESSUNG_LAGERHAUS.sbf");
		} else if (*t == 0x15 || *t == 0x14 || *t == 0x12) {
			strcpy(greet, "BEGRUESSUNG_SCHMIEDE_STEIMETZ_TISCHLER.sbf");
		} else if (*t == 0xb || *t == 0xc || *t == 0xd) {
			strcpy(greet, "BEGRUESSUNG_WALDSTUECK_STEINBRUCH_MINE.sbf");
		} else if (*t == 0x16) {
			strcpy(greet, "BEGRUESSUNG_WIRTSHAUS.sbf");
		} else if (*t == 0x1e) {
			strcpy(greet, "ADDON\\BEGRUESSUNG_DOMIZIL.sbf");
		}
	}
	if (cmd[0] != 0) {
		g_772e6c = fcn_004c3100(cmd, 0);
	}
	if (click[0] != 0) {
		g_772e70 = fcn_004c3100(click, 0);
	}
	if (*t != 0x1d && *t != 0x1e) {
		g_772e74 = fcn_004c3100("ARBEITER_KOMMENTARE_KLICK_GERAEUSCHE.sbf", 0);
	} else {
		g_772e74 = 0;
	}
	if (greet[0] != 0) {
		g_772e7c = fcn_004c3100(greet, 0);
	}
}
