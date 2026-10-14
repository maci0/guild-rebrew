

#include <string.h>

extern int g_7746a0;
extern unsigned char g_773d75;
extern char g_868060[];
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

char* __cdecl fcn_005338d0(char*, int, int);
void __cdecl fcn_005a3a40(int, int);
void __cdecl fcn_005c1110(void);
void __cdecl fcn_005c1490(void);

void __cdecl fcn_005a3b30(int arg)
{
	char* c;
	char* a;
	char* b;
	int q;

	a = 0;
	c = 0;
	b = 0;
	fcn_005338d0("ob_MARKTSTAND_TISCHLER_SCHMIEDE", g_14a7e50, 0x10);
	fcn_005338d0("ob_MARKTSTAND_STEINMETZ_WIRT", g_14a7e58, 0x10);
	fcn_005338d0("ob_MARKTSTAND_PARFUM_KRAEUTER", g_14a7e60, 0x10);
	fcn_005338d0("ob_MARKTSTAND_ROHSTOFFE", g_14a7e68, 0x10);
	fcn_005338d0("ob_MARKTSTAND_IMPORTEUR", g_14a7e70, 0x10);
	fcn_005338d0("ob_MARKTSTAND_KIRCHE", g_14a7e78, 0x10);
	fcn_005338d0("ob_MARKTSTAND_OKKULT", g_14a9098, 0x10);
	fcn_005338d0("ob_SCHWARZES_BRETT", g_14a7e80, 0x10);
	fcn_005338d0("ob_TRIBUENE", g_14a554c, 0x10);
	if (strcmp(((char(*)[0x2f4])g_868060)[g_773d75], "Nuernberg") == 0) {
		a = fcn_005338d0("contact_MARKTFLECKEN_01", g_14a7860, 0x10);
		b = fcn_005338d0("contact_MARKTFLECKEN_02", g_14a7860, 0x10);
		c = fcn_005338d0("contact_MARKTFLECKEN_03", g_14a7860, 0x10);
	}
	if (((char*)g_7746a0) == 0) {
		return;
	}
	if (strcmp(((char*)g_7746a0), "ob_MARKTSTAND_TISCHLER_SCHMIEDE") == 0) {
		fcn_005a3a40(arg, 0x92);
	}
	else if (strcmp(((char*)g_7746a0), "ob_MARKTSTAND_STEINMETZ_WIRT") == 0) {
		fcn_005a3a40(arg, 0x93);
	}
	else if (strcmp(((char*)g_7746a0), "ob_MARKTSTAND_PARFUM_KRAEUTER") == 0) {
		fcn_005a3a40(arg, 0x94);
	}
	else if (strcmp(((char*)g_7746a0), "ob_MARKTSTAND_ROHSTOFFE") == 0) {
		fcn_005a3a40(arg, 0x95);
	}
	else if (strcmp(((char*)g_7746a0), "ob_MARKTSTAND_IMPORTEUR") == 0) {
		fcn_005a3a40(arg, 0x96);
	}
	else if (strcmp(((char*)g_7746a0), "ob_MARKTSTAND_KIRCHE") == 0) {
		fcn_005a3a40(arg, 0x97);
	}
	else if (strcmp(((char*)g_7746a0), "ob_MARKTSTAND_OKKULT") == 0) {
		fcn_005a3a40(arg, 0x2db);
	}
	else if (strcmp(((char*)g_7746a0), "contact_ob_SCHWARZES_BRETT") == 0 || strcmp(((char*)g_7746a0), "ob_SCHWARZES_BRETT") == 0) {
		fcn_005c1110();
	}
	else if (strcmp(((char*)g_7746a0), "ob_TRIBUENE") == 0) {
		fcn_005c1490();
	}
	else if (((char*)g_7746a0) == a || ((char*)g_7746a0) == b || ((char*)g_7746a0) == c) {
		q = *(int*) (*(char**) (((char*)g_7746a0) + 0x1fc) + 0x204);
		if (q != 0) {
			fcn_005a3a40(q, 0x95);
		}
	}
}
