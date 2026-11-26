#include <string.h>




#include "client_types.h"
typedef Rec18_68da68 Rec18;
// SIZE 0x18

extern Rec18_68da68 g_68da68[];

int __cdecl amt_GetRoleTemplate(int role, Rec18* out)
{
	if (role >= 0x28) {
		*out = g_68da68[0];
		return 0;
	}
	*out = g_68da68[role];
	return 1;
}

extern int g_9a9620[10];
extern char g_7f4ca0[];

/* ADDRESS: GOLDTL 0x004e98d0 */
int* __cdecl amt_CountRolesByLevel(void)
{
	Rec18 tmpl;
	int p;
	unsigned char state;

	memset(g_9a9620, 0, sizeof(g_9a9620));
	for (p = (int) (g_7f4ca0 + 0x167); p < (int) (g_7f4ca0 + 0x167 + 0x65400); p += 0x21c) {
		state = *(unsigned char*) (p - 0x165);
		if (state >= 2 && state <= 7) {
			if (*(unsigned char*) p == 0) {
				g_9a9620[0]++;
			} else {
				amt_GetRoleTemplate(*(unsigned char*) p, &tmpl);
				g_9a9620[tmpl.type]++;
			}
		}
	}
	return g_9a9620;
}

extern Rec18 g_9a9228[];

/* ADDRESS: GOLDTL 0x004e9950 */
int __cdecl amt_ListRolesOfLevel(int level, int max, int* out)
{
	Rec18 tmpl;
	int p;
	int n;
	int id;

	if (max < 1) {
		return 0;
	}
	n = 0;
	for (p = (int) g_9a9228; p < (int) (g_9a9228 + 0x1c); p += sizeof(Rec18)) {
		if (n >= max) {
			break;
		}
		id = ((Rec18*) p)->id;
		amt_GetRoleTemplate(id, &tmpl);
		if (tmpl.type == level) {
			out[n] = id;
			n++;
		}
	}
	return n;
}
