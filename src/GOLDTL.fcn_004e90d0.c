


// SIZE 0x18
typedef struct {
	int a;
	int b;
	int c;
	int d;
	int e;
	int f;
} fcn_004e90d0_E;

#include "client_types.h"
extern Rec18_68da68 g_9a9220[42];
char* __cdecl fcn_00508e40(int);

char* __cdecl fcn_004e90d0(int a1)
{
	int i;
	int a;

	for (i = 0, a = (int) g_9a9220 + 8; a < (int) g_9a9220 + 0x3f8; a += 0x18, i++) {
		if (*(unsigned char*) a == a1) {
			return fcn_00508e40(((fcn_004e90d0_E*) ((int) g_9a9220 + 4))[i].a);
		}
	}
	return 0;
}
