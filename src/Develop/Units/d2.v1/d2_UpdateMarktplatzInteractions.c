

#include <string.h>

extern int sv_ClickedObjekt;
extern unsigned char gm_ActiveTownIndex;
extern char gm_TownTable[];
extern int g_14a7e50;
extern int g_14a7e58;
extern int g_14a7e60;
extern int g_14a7e68;
extern int g_14a7e70;
extern int g_14a7e78;
extern int g_14a9098;
extern int g_14a7e80;
extern int g_14a554c;
extern int g_14a7860;

char* __cdecl RegisterStatusText(char*, int, int);
void __cdecl d2_OpenMarktstandPanel(int, int);
void __cdecl d2_RunSchwarzesBrettDialog(void);
void __cdecl d2_ShowBardPoemDialog(void);

void __cdecl d2_UpdateMarktplatzInteractions(int buildingId)
{
	char* c;
	char* a;
	char* b;
	int q;

	a = 0;
	c = 0;
	b = 0;
	RegisterStatusText("ob_MARKTSTAND_TISCHLER_SCHMIEDE", g_14a7e50, 0x10);
	RegisterStatusText("ob_MARKTSTAND_STEINMETZ_WIRT", g_14a7e58, 0x10);
	RegisterStatusText("ob_MARKTSTAND_PARFUM_KRAEUTER", g_14a7e60, 0x10);
	RegisterStatusText("ob_MARKTSTAND_ROHSTOFFE", g_14a7e68, 0x10);
	RegisterStatusText("ob_MARKTSTAND_IMPORTEUR", g_14a7e70, 0x10);
	RegisterStatusText("ob_MARKTSTAND_KIRCHE", g_14a7e78, 0x10);
	RegisterStatusText("ob_MARKTSTAND_OKKULT", g_14a9098, 0x10);
	RegisterStatusText("ob_SCHWARZES_BRETT", g_14a7e80, 0x10);
	RegisterStatusText("ob_TRIBUENE", g_14a554c, 0x10);
	if (strcmp(((char(*)[0x2f4])gm_TownTable)[gm_ActiveTownIndex], "Nuernberg") == 0) {
		a = RegisterStatusText("contact_MARKTFLECKEN_01", g_14a7860, 0x10);
		b = RegisterStatusText("contact_MARKTFLECKEN_02", g_14a7860, 0x10);
		c = RegisterStatusText("contact_MARKTFLECKEN_03", g_14a7860, 0x10);
	}
	if (((char*)sv_ClickedObjekt) == 0) {
		return;
	}
	if (strcmp(((char*)sv_ClickedObjekt), "ob_MARKTSTAND_TISCHLER_SCHMIEDE") == 0) {
		d2_OpenMarktstandPanel(buildingId, 0x92);
	}
	else if (strcmp(((char*)sv_ClickedObjekt), "ob_MARKTSTAND_STEINMETZ_WIRT") == 0) {
		d2_OpenMarktstandPanel(buildingId, 0x93);
	}
	else if (strcmp(((char*)sv_ClickedObjekt), "ob_MARKTSTAND_PARFUM_KRAEUTER") == 0) {
		d2_OpenMarktstandPanel(buildingId, 0x94);
	}
	else if (strcmp(((char*)sv_ClickedObjekt), "ob_MARKTSTAND_ROHSTOFFE") == 0) {
		d2_OpenMarktstandPanel(buildingId, 0x95);
	}
	else if (strcmp(((char*)sv_ClickedObjekt), "ob_MARKTSTAND_IMPORTEUR") == 0) {
		d2_OpenMarktstandPanel(buildingId, 0x96);
	}
	else if (strcmp(((char*)sv_ClickedObjekt), "ob_MARKTSTAND_KIRCHE") == 0) {
		d2_OpenMarktstandPanel(buildingId, 0x97);
	}
	else if (strcmp(((char*)sv_ClickedObjekt), "ob_MARKTSTAND_OKKULT") == 0) {
		d2_OpenMarktstandPanel(buildingId, 0x2db);
	}
	else if (strcmp(((char*)sv_ClickedObjekt), "contact_ob_SCHWARZES_BRETT") == 0 || strcmp(((char*)sv_ClickedObjekt), "ob_SCHWARZES_BRETT") == 0) {
		d2_RunSchwarzesBrettDialog();
	}
	else if (strcmp(((char*)sv_ClickedObjekt), "ob_TRIBUENE") == 0) {
		d2_ShowBardPoemDialog();
	}
	else if (((char*)sv_ClickedObjekt) == a || ((char*)sv_ClickedObjekt) == b || ((char*)sv_ClickedObjekt) == c) {
		q = *(int*) (*(char**) (((char*)sv_ClickedObjekt) + 0x1f8) + 0x200);
		if (q != 0) {
			d2_OpenMarktstandPanel(q, 0x95);
		}
	}
}
