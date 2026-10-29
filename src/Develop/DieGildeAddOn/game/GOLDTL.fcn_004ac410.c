extern unsigned char g_773d75;
extern char g_7f4ca0[];

void __cdecl fcn_004c5150(int, int, unsigned char, int);
void __cdecl fcn_004c5420(int, int, int, int, int);
int* __cdecl fcn_004ac1e0(int);
unsigned short __cdecl gm_RandomMod(unsigned short);
#include "client_packet_builder.h"
void __cdecl fcn_004c4670(int, int, short, char*);
void __cdecl fcn_004c5360(void);
#include "Develop/DieGildeAddOn/game/spiel.h"
void __cdecl fcn_004c54c0(int, int, int, int);


/* ADDRESS: GOLDTL 0x004ac410 */
void __cdecl fcn_004ac410(unsigned char* a1, int a2, int a3)
{
	int* p;
	char c;
	int i;
	char* rec;

	fcn_004c5150(-1, *(int*) (a1 + 4), g_773d75, a2);
	fcn_004c5420(*(int*) (a1 + 4), 0x1c8, 4, 0x20000, 0);
	p = fcn_004ac1e0(a3);
	if (p == 0)
		return;
	if (p[0] == 0 && *(unsigned short*) (p + 1) <= 4) {
		c = gm_RandomMod(8) + 8;
		c = (char)(c < 252.0f - a1[*(unsigned short*) (p + 1) + 0x80] ? c : 252.0f - a1[*(unsigned short*) (p + 1) + 0x80]);
		fcn_004c4510((char*) a1, *(int*) (a1 + 4));
		fcn_004c4670(1, 1, *(unsigned short*) (p + 1) + 0x80, &c);
		fcn_004c5360();
		return;
	}
	if (p[0] == 1) {
		for (i = 0; i < 768; i++) {
			rec = g_7f4ca0 + i * 540;
			if (*(int*) (rec + 4) != *(int*) (a1 + 4)
			    && gm_MapEntityStatRange(*(unsigned char*) (rec + 0x164)) == *(unsigned short*) (p + 1))
				fcn_004c54c0(*(int*) (a1 + 4), *(int*) (rec + 4), gm_RandomMod(4) + 3, 0);
		}
	}
}
