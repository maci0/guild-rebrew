


extern char g_7f4ca4[];
extern float g_662910;

void* __cdecl fcn_0050e4a0(int);
void* __cdecl fcn_00502cd0(int, int, int, int, int);
int __cdecl fcn_0064eeec(char*);
int __cdecl fcn_004ae130(int);
#include "Develop/DieGildeAddOn/game/spiel.h"
void __cdecl fcn_004c51a0(int, int, int, int);

int __cdecl fcn_004b03e0(int a1, int a2, char* arg)
{
	void* e;
	char* obj;
	float scale;
	int i;

	e = fcn_0050e4a0(1);
	if (e == 0)
		return 0;
	obj = fcn_00502cd0(*(int*) ((char*) e + 0x5d), 2, 6, 0, 0x115);
	if (obj == 0)
		return 0;
	if (*arg != '-')
		return 0;
	scale = (float) fcn_0064eeec(arg + 1) * g_662910;
	for (i = 0; i < 0x300; i++) {
		if (fcn_004ae130(i) != 0) {
			fcn_004c51a0(*(int*) (obj + 2), *(int*) (g_7f4ca4 + i * 0x21c), 0,
			    (int) ((float) gm_WalkEntityChain(*(unsigned short*) (g_7f4ca4 + i * 0x21c - 4)) * scale));
		}
	}
	return 1;
}
