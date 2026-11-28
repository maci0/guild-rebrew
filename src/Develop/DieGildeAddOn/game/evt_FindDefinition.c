


#include <string.h>

// SIZE 0x14c
typedef struct {
	char name[0x14c];
} Def;

// SIZE 0x114
typedef struct {
	char pad0[0x10c];
	Def* defs;
	int count;
} Script;

extern char* evt_MemberScopeScript;

/* ADDRESS: GOLDDE 0x00420d80 */
Def* __cdecl evt_FindDefinition(Script* s, const char* name)
{
	Script* o;
	Def* defs;
	Def* p;
	int i;
	int n;

	o = ((Script*)evt_MemberScopeScript);
	if (o == 0) {
		o = s;
	}
	if (s->defs != 0) {
		n = o->count;
		i = 0;
		if (n > 0) {
			defs = o->defs;
			p = defs;
			do {
				if (strcmp(p->name, name) == 0) {
					return &defs[i];
				}
				i++;
				p++;
			} while (i < n);
		}
	}
	return 0;
}
