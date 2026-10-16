#include <string.h>

extern int g_68bfb8;
extern int g_7725c8;
extern char g_14cf950;
extern int g_7725d0;
extern int g_7747f0;
extern int g_772f54;

char* __cdecl fcn_00508e40(int);
#include "client_packet_builder.h"
void __cdecl fcn_004c4570(int, int, int, void*);
void __cdecl fcn_004c5360(void);
int __cdecl fcn_004e4ae0(char*, int);
void __cdecl fcn_004e4e90(char*);
void __cdecl fcn_004e4730(char*);
int __cdecl fcn_004e4470(char*);
int __cdecl fcn_004e4d00(int, int, int);
int __cdecl fcn_004e6cb0(int);
void __cdecl fcn_004e4b40(int, int, char*, int, int);
unsigned short __cdecl gm_RandomMod(int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
char* __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00472250(int, int, char*);
void __cdecl fcn_00472770(int, int);
void __cdecl fcn_00474cf0(int);
char* __cdecl fcn_00471f80(int);
int __cdecl fcn_005373e0(int, int);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_004e48b0(void);
void __cdecl fcn_004e4610(int);
void __cdecl fcn_004e44f0(int);
void __cdecl fcn_004c09b0(void);
void __cdecl fcn_004e4b00(int);
void __cdecl fcn_004e4910(void);
void __cdecl fcn_004e4eb0(void);

#include "Develop/DieGildeAddOn/game/event_callbacks.h"

/* ADDRESS: GOLD 0x004e0f70 */
/* ADDRESS: GOLDTL 0x004e2890 */

void __cdecl fcn_004e2890(char* m)
{
	char buf[0x10];
	char* a;
	char* b;
	int snd;
	int esc;
	int n;
	int sc;
	int w;

	a = fcn_00508e40(*(int*) (m + 0x34));
	b = fcn_00508e40(*(int*) (m + 0x38));
	if (a == 0 || b == 0)
		return;
	{
		int v;

		v = 8;
		fcn_004c4510(b, *(int*) (b + 4));
		fcn_004c4570(1, 1, 2, &v);
		fcn_004c5360();
	}
	g_68bfb8 = 0x702c6;
	g_7725c8 = 1;
	snd = fcn_004e4ae0("GEBURT.sbf", 0);
	fcn_004e4e90("cd2\\Geburt.mp3");
	fcn_004e4730("Geburt.ed3");
	esc = fcn_004e4470("cutscenes\\geburt\\enter_Geburt.esc");
	if (fcn_004e4d00(0x1964, 0, 0) == 0) {
		if (a[9] == 0) {
			if (b[9] == 0)
				fcn_004e4b40(-8, snd, "_GEBURT", fcn_004e6cb0(2), 0);
			else
				fcn_004e4b40(-8, snd, "_GEBURT", fcn_004e6cb0(2) + 2, 0);
		} else if (b[9] == 0) {
			fcn_004e4b40(-8, snd, "_GEBURT", fcn_004e6cb0(2) + 4, 0);
		} else {
			fcn_004e4b40(-8, snd, "_GEBURT", fcn_004e6cb0(2) + 6, 0);
		}
		if (fcn_004e4d00(1000, 0, 0) == 0) {
			for (n = fcn_004e6cb0(4) + 2; n > 0; n--)
				fcn_004e4b40(-8, snd, "_GEBURT_GESCHREI", fcn_004e6cb0(5), gm_RandomMod(0x800) + 1000);
			fcn_004e4d00(7000, 0, 0);
		}
	}
	sc = fcn_00470820(0, 0, "cutscenes\\geburt");
	fcn_00471b60(sc);
	fcn_004727a0(sc, 1);
	if (b[9] == 0)
		fcn_00519190(0x1aae);
	else
		fcn_00519190(0x1aaf);
	fcn_004727a0(sc, 2);
	w = fcn_00472250(sc, 2, fcn_00519190((int) "$L%t", b + 0x30));
	fcn_00472770(w, 0xf);
	fcn_00474cf0(w);
	for (;;) {
		if (g_14cf950 == 0x1c || g_7725d0 == 0) {
			strcpy(buf, fcn_00471f80(w));
			if (buf[0] != 0)
				break;
			fcn_00474cf0(w);
		}
		if (fcn_005373e0(0, g_68bfb8) == 0 || g_7747f0 != 0)
			break;
	}
	fcn_004c4510(b, *(int*) (b + 4));
	fcn_004c4570(1, 0x10, 0x30, buf);
	fcn_004c5360();
	fcn_00471e30(sc);
	fcn_004e48b0();
	fcn_004e4610(esc);
	fcn_004e44f0(esc);
	fcn_004c09b0();
	fcn_004e4b00(snd);
	g_772f54 = 0;
	fcn_004e4910();
	fcn_004e4eb0();
	g_7725c8 = 0;
}
