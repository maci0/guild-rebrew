#include "Develop/DieGildeAddOn/game/spiel.h"
typedef struct Msg {
	unsigned char type;
	char pad[3];
	int a;
	int b;
	int c;
	int d;
	float f;
} Msg;
// SIZE 0x18


int __cdecl ai_SendHeimsuchung(char* e, char* home, Msg* m, Msg* out);
int __cdecl ai_SendNecromancerFog(char* e, char* home, Msg* m, Msg* out);
int __cdecl ai_SendHauchDesVerfalls(char* e, char* home, Msg* m, Msg* out);
int __cdecl ai_RunDeathPact(char* e, char* home, Msg* m, Msg* out);

/* ADDRESS: GOLDTL 0x0048fdd0 */
int __cdecl ai_RunGraveyardOwner(char* e, Msg* m, Msg* out)
{
	{
		char* home;

		gm_ResolveEntityById((void**) (&home), 0, 0, m->c);
		if (home != 0) {
			switch (m->d) {
			case 0:
				return ai_SendHeimsuchung(e, home, m, out);
			case 1:
				return ai_SendNecromancerFog(e, home, m, out);
			case 2:
				return ai_SendHauchDesVerfalls(e, home, m, out);
			case 3:
				return ai_RunDeathPact(e, home, m, out);
			}
		}
	}
	return 0;
}
