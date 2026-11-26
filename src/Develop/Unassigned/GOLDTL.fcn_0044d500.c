typedef struct Rec38 {
	char pad0[0x24];
	int a;
	int b;
	char pad2c[0xc];
} Rec38;
// SIZE 0x38

#include "Develop/DieGildeAddOn/game/game_data.h"

char* __cdecl fcn_0064f026(char* s, const char* delim);
int __cdecl atoi(const char* s);

/* ADDRESS: GOLDTL 0x0044d500 */
void __cdecl fcn_0044d500(int unused, char* s)
{
	char* t;

	t = fcn_0064f026(0, " ");
	(*(Rec38**) (s + 0x20))[*(int*) (s + 0x18)].a = -1;
	(*(Rec38**) (s + 0x20))[*(int*) (s + 0x18)].b = atoi(t);
	*(int*) (s + 0x18) += 1;
}
