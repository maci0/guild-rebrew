#include <string.h>

extern char* g_7ea360;
extern char* g_7746a0;
extern char* g_7746a4;
extern char* g_7746a8;
extern char* g_7746ac;
extern char* g_7746b0;
extern char* g_7746b4;
extern int g_7746b8;
extern int g_7746bc;
extern char* g_7746c0;
extern char* g_7746c4;
extern char* g_7746c8;
extern char* g_7746cc;
extern int g_7746f0;
extern char g_7746f4;
extern char* g_7e431c;
extern char* g_7e4320;
extern int g_7e4318;
extern int g_7e2700;
extern char* g_7e2704;
extern char* g_7e2708;
extern char g_7e2714[];
extern char* g_7e2a9c;
extern char* g_7e2aa0;
extern int g_14ce8cc;
extern int g_6b5cc0;
extern short g_14ce8c0;
extern short g_14ce8c2;
extern int g_6a3764;
extern int g_6a376c;
extern int g_6a3768;
extern int g_6a3770;
extern int g_100f894;
extern int g_67d8d4;
extern char* g_99ec10;
extern char* g_77479c;
extern int g_774650;
extern int g_77465c;
extern int g_6b5c48;
extern unsigned short g_774970;
extern char g_7f4ca0[];
extern char s_6a3004[];
extern char s_6a301c[];
extern int g_6a256c;

extern char* __cdecl fcn_00445600(int, int, int, char*);
extern int __cdecl fcn_0064d41a(char*, char*, ...);
extern void __cdecl fcn_00412e50(char*, int);
extern int __cdecl fcn_00506380(int, int, int, void*);
extern void __cdecl fcn_0052ae70(void);
extern void __cdecl fcn_004c3540(char*);
extern void __cdecl fcn_00530510(void);

typedef int (__cdecl* Fn_5305d0)(char*, int, char*, int);

/* ADDRESS: GOLDTL 0x005305d0 */

/* Aktualisiert die Szenenauswahl aus den Quickjump-Kontaktfeldern; die
 * Auswahl wird auf die Objektliste abgebildet und neu gezeichnet. */
void __cdecl sv_HandleObjects(void)
{
	char buf[0x6c];
	char* v5;
	char* v7;
	char* p;
	char* list;
	int created;
	int match;
	int r;
	int i;

	created = 0;
	match = 0;
	v5 = 0;
	list = 0;
	if (g_7ea360 != 0 && *(char*) (g_7ea360 + 0x188) == 0) {
		g_7ea360 = 0;
	}
	g_7e4318 = 0;
	g_7e431c = 0;
	g_7746a0 = 0;
	g_7e4320 = 0;
	g_7746b8 = 0;
	v5 = g_7746a4;
	if (g_7e2700 == 0) {
		goto L744;
	}
	v7 = g_7746c4;
	if (v7 == 0) {
		v7 = g_7746c8;
	}
	if (v7 != g_7e2704) {
		goto L744;
	}
	if (g_7746cc == g_7e2708) {
		goto L66a;
	}
	if (g_7746c8 == 0 || g_7746cc != 0 || g_7e2708 == 0) {
		goto L6cd;
	}
	if (*(short*) g_7e2708 != 0xfd) {
		goto L6cd;
	}
L66a:
	if (g_7e2714[0] != 0) {
		p = fcn_00445600(0, 0x60, 0, g_7e2714);
		if (p != 0) {
			v5 = p;
			g_7746a4 = p;
			created = 1;
			g_7e2700 = 0;
			goto L6d3;
		}
		fcn_0064d41a(buf, s_6a301c, g_7e2714);
	}
	v5 = g_7746a4;
	g_7e2700 = 0;
	goto L6d3;
L6cd:
	v5 = g_7746a4;
L6d3:
	if (v7 != g_7e2704) {
		goto L744;
	}
	if (g_7e2708 != 0 && *(short*) g_7e2708 != 0xfd) {
		goto L744;
	}
	if (g_7e2714[0] != 0) {
		p = fcn_00445600(0, 0x60, 0, g_7e2714);
		if (p != 0) {
			v5 = p;
			created = 1;
			g_7746a4 = p;
			g_7e2700 = 0;
			goto L744;
		}
		fcn_0064d41a(buf, s_6a301c, g_7e2714);
		v5 = g_7746a4;
	}
	g_7e2700 = 0;
L744:
	if (g_14ce8cc == 0 || g_6b5cc0 != 0
	    || g_14ce8c0 <= g_6a3764 || g_14ce8c0 >= g_6a376c
	    || g_14ce8c2 <= g_6a3768 || g_14ce8c2 >= g_6a3770
	    || g_100f894 != -1 || g_67d8d4 != -1) {
		if (created == 0) {
			return;
		}
	}
	if (v5 == 0) {
		if (g_7746f4 != 0) {
			return;
		}
		fcn_00530510();
		return;
	}
	list = g_7746ac;
	if (list != 0) {
		p = g_99ec10 + (unsigned int) (unsigned short) *(unsigned short*) list * 0x41;
	} else {
		p = 0;
	}
	if (memcmp(v5, s_6a3004, 8) != 0) {
		if ((p != 0 && *p == 6) || g_7746bc != 0) {
			match = 1;
		}
	} else {
		match = 1;
	}
	g_7e4318 = (int) g_7746b0;
	g_7e431c = g_7746ac;
	g_7e4320 = g_7746b4;
	g_7746b8 = g_7746bc;
	g_7746a0 = v5;
	if ((*(unsigned char*) (v5 + 0x214) & 0x40) != 0 && match == 0) {
		fcn_00412e50(v5, g_6a256c);
		g_7746a8 = g_7746a4;
		v5 = g_7746a4;
		if (v5 != 0) {
			p = *(char**) (v5 + 0x1d4);
			if (p != 0 && *(Fn_5305d0*) (p + 0x108) != 0) {
				(*(Fn_5305d0*) (p + 0x108))(v5, 2, p + 0x10c, 0);
				v5 = g_7746a4;
			}
		}
		g_77465c = g_774650;
		list = g_7746ac;
	}
	g_77479c = v5;
	if (g_7746b4 != 0 && *(char*) (g_7746b4 + 8) != 0) {
		r = fcn_00506380((int) g_774970, 0, 0, g_7746b4);
		fcn_0052ae70();
		p = g_7746b4;
		if ((r & 0x800) != 0
		    && (*(char*) (p + 0x165) != 0x1c || (*(unsigned char*) (p + 0x1b4) & 1) == 0)) {
			g_7ea360 = p;
			*(char*) (g_7f4ca0 + (unsigned short) *(unsigned short*) p * 0x21c + 0x188) = 1;
			g_7746f0 = 1;
			g_6b5c48 = *(int*) (g_7f4ca0 + (unsigned short) *(unsigned short*) p * 0x21c + 0x184);
			fcn_004c3540(p);
			p = g_7746b4;
		}
		g_6b5c48 = *(int*) (g_7f4ca0 + (unsigned short) *(unsigned short*) p * 0x21c + 0x184);
		v5 = g_7746a4;
	}
	if (g_7746f0 == 0 && g_7746f4 == 0 && g_7746b0 != 0 && g_7e2a9c == 0) {
		g_7746c0 = v5;
	}
	g_7e2aa0 = g_7746b0;
	g_7e2a9c = g_7746ac;
	if (g_7746b0 != 0) {
		g_7746c0 = v5;
	}
	if (list == 0) {
		g_7e2aa0 = g_7746b0;
		return;
	}
	if (*(char*) (g_99ec10 + (unsigned int) (unsigned short) *(unsigned short*) list * 0x41) == 0x1d) {
		g_7746c0 = v5;
		fcn_0052ae70();
		return;
	}
	g_7746c0 = v5;
	g_7e2aa0 = g_7746b0;
}
