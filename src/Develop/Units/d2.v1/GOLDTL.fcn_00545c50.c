extern int g_6a476c;
extern unsigned char g_7747b0;
extern int g_6b7fc0;

// SIZE 0xc
struct ev_545c50 {
	unsigned char* e;
	int s;
	int h;
};

extern unsigned char** g_7749e4;




#include "Develop/Units/d2.v1/d2_gui.h"
void __cdecl fcn_00471af0(int, int);
void __cdecl fcn_004707d0(int);

void __cdecl fcn_00545c50(struct ev_545c50* ne)
{
	unsigned char* e;

	if (g_6a476c == -1) {
		return;
	}
	if ((*(struct ev_545c50**)&g_7749e4) != 0) {
		if ((*(struct ev_545c50**)&g_7749e4)->s != -1) {
			d2_SetElementValue((*(struct ev_545c50**)&g_7749e4)->s, 0);
		}
		fcn_00471af0((*(struct ev_545c50**)&g_7749e4)->h, 0);
		e = (*(struct ev_545c50**)&g_7749e4)->e;
		if (e != 0 && ((e[0] == 0x11 && (e[0xf0] & 0x40) != 0) || e[0] == 0x87) &&
		    (g_7747b0 & 4) == 0) {
			g_6b7fc0 = 0;
		}
		(*(struct ev_545c50**)&g_7749e4) = 0;
	}
	if (ne != 0 && ne->h != -1) {
		if (ne->s != -1) {
			d2_SetElementValue(ne->s, 1);
		}
		fcn_00471af0(ne->h, 1);
		fcn_004707d0(ne->h);
		e = ne->e;
		if (e != 0 && ((e[0] == 0x11 && (e[0xf0] & 0x40) != 0) || e[0] == 0x87) &&
		    (g_7747b0 & 4) == 0) {
			g_6b7fc0 = 1;
		}
	}
	(*(struct ev_545c50**)&g_7749e4) = ne;
}
