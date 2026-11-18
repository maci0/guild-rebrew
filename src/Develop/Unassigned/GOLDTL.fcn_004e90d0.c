


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
char* __cdecl gm_LookupEntityRecordById(int);

char* __cdecl fcn_004e90d0(int value)
{
	int index;
	int cursor;

	for (index = 0, cursor = (int) g_9a9220 + 8; cursor < (int) g_9a9220 + 0x3f8; cursor += 0x18, index++) {
		if (*(unsigned char*) cursor == value) {
			return gm_LookupEntityRecordById(((fcn_004e90d0_E*) ((int) g_9a9220 + 4))[index].a);
		}
	}
	return 0;
}
