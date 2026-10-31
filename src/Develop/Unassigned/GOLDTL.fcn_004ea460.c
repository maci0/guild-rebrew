


#include "client_types.h"
typedef Rec18_68da68 Rec18;
// SIZE 0x18

extern Rec18_68da68 g_9a9220[42];
extern Rec18_68da68 g_68da68[];

void* __cdecl gm_LookupEntityRecordById(int);

int __cdecl fcn_004ea460(void)
{
	int n;
	int i;

	n = 7;
	for (i = 36; i != 0; i--) {
		if (n == 0) {
			break;
		}
		if (g_68da68[g_9a9220[i].type].x4 == 7) {
			if (g_9a9220[i].x4 != -1) {
				if (gm_LookupEntityRecordById(g_9a9220[i].x4) != 0) {
					return 1;
				}
			} else {
				n--;
			}
		}
	}
	return 0;
}
