#include <string.h>
extern int g_773d40;
extern char* g_773d44;

// SIZE 0x44
typedef struct HeadSet {
	char pad0[4];
	char name[0x30];
	int head[4];
} HeadSet;

char* __cdecl fcn_0064d1a0(char* s, int c);
int __cdecl fcn_0064d41a(char* buf, const char* fmt, ...);
int __cdecl fcn_0065f220(const char* a, const char* b);

/* ADDRESS: GOLDTL 0x004fdd70 */
void __cdecl fcn_004fdd70(HeadSet* hs)
{
	char base[0x80];
	char kind[0x80];
	char icon[0x80];
	char* p;
	int j;
	int i;
	int* slot;

	if (hs->head[0] != 0xff) {
		return;
	}
	strcpy(base, hs->name);
	p = fcn_0064d1a0(base, '_');
	if (p != 0) {
		strcpy(kind, p + 1);
		*p = 0;
	}
	for (slot = hs->head, i = 0; i < 4; i++, slot++) {
		fcn_0064d41a(icon, (char*) 0x69649c, base, i, kind);
		*slot = 0xff;
		for (j = 0; j < g_773d40; j++) {
			p = g_773d44 + j * 0x30;
			if (*p == 0) {
				break;
			}
			if (fcn_0065f220(icon, p) == 0) {
				goto found;
			}
		}
		fcn_0064d41a(icon, (char*) 0x696488, base, i);
		*slot = 0xff;
		for (j = 0; j < g_773d40; j++) {
			p = g_773d44 + j * 0x30;
			if (*p == 0) {
				break;
			}
			if (fcn_0065f220(icon, p) == 0) {
				goto found;
			}
		}
		continue;
	found:
		*slot = j;
	}
}
