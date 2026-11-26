


#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;

double __cdecl fcn_004fc460(float*);
int __cdecl ai_FilterCandidateLimit(int, int, int);

int __cdecl fcn_004b4f30(int a1, int a2, char* a3)
{
	float buf[10];

	if ((*(int*)&gm_GameTime) < 10)
		return 0;
	fcn_004fc460(buf);
	if (*(int*) (a3 + 0x14) < buf[6])
		return ai_FilterCandidateLimit(a2, 0, *(int*) (a3 + 0x18));
	return ai_FilterCandidateLimit(a2, 1, *(int*) (a3 + 0x18));
}
