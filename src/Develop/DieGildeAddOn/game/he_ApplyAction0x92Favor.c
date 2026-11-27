extern unsigned char* lpGebaeudePROT;
extern float g_6652d8[];
#include "Develop/DieGildeAddOn/game/building_prototype.h"
// SIZE 0x21c
struct s_7f4ca0 {
	char pad[2];
	char kind;
	char pad2[0x219];
};

extern char g_7f4ca0[];




unsigned char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
char* __cdecl gm_LookupEntityRecordById(int);
void __cdecl gv_SendExtendProductionTime(char*, unsigned char*, int, int, short, int);
void __cdecl he_NotifyFriedhofEvent0x414f(struct s_7f4ca0*, char*, unsigned char*, int, int, int);

void __cdecl he_ApplyAction0x92Favor(char* o)
{
	unsigned char* e;
	char* x;
	struct s_7f4ca0* r;
	int a;
	int b;

	e = gm_StartFilteredEntitySearch(1, 1, *(int*) (o + 0xac));
	if (e != 0 && ((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*e].category == 0x1d) {
		x = gm_LookupEntityRecordById(*(int*) (o + 0xc));
		if (x != 0) {
			gv_SendExtendProductionTime(x, e, *(int*) (o + 0xb0), *(unsigned char*) (o + 0xb4),
			             *(short*) (o + 0xbc), *(int*) (o + 0xb8));
			r = &((struct s_7f4ca0*)g_7f4ca0)[*(unsigned short*) (e + 0x27)];
			if (x != (char*) r && (((struct s_7f4ca0*)g_7f4ca0)[*(unsigned short*) (e + 0x27)].kind == 6 ||
			                       ((struct s_7f4ca0*)g_7f4ca0)[*(unsigned short*) (e + 0x27)].kind == 7)) {
				a = *(int*) (o + 0xb0);
				b = *(int*) (o + 0xb8);
				he_NotifyFriedhofEvent0x414f(r, x, e, a, b, (int) (b * g_6652d8[a]));
			}
		}
	}
}
