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


int __cdecl fcn_0048f660(char* e, char* home, Msg* m, Msg* out);
int __cdecl fcn_0048f850(char* e, char* home, Msg* m, Msg* out);
int __cdecl fcn_0048fa60(char* e, char* home, Msg* m, Msg* out);
int __cdecl fcn_0048fba0(char* e, char* home, Msg* m, Msg* out);

/* ADDRESS: GOLDTL 0x0048fdd0 */
int __cdecl fcn_0048fdd0(char* e, Msg* m, Msg* out)
{
	{
		char* home;

		gm_ResolveEntityById((void**) (&home), 0, 0, m->c);
		if (home != 0) {
			switch (m->d) {
			case 0:
				return fcn_0048f660(e, home, m, out);
			case 1:
				return fcn_0048f850(e, home, m, out);
			case 2:
				return fcn_0048fa60(e, home, m, out);
			case 3:
				return fcn_0048fba0(e, home, m, out);
			}
		}
	}
	return 0;
}
