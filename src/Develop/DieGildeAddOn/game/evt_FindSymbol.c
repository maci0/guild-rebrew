#include <string.h>

// SIZE 0x30
struct sym_4260f0 {
	int kind;
	char name[0x2c];
};

extern char* evt_MemberScopeScript;
extern void* evt_GlobalVariables;
extern int evt_GlobalVariableCount;

/* ADDRESS: GOLDTL 0x004260f0 */
void* __cdecl evt_FindSymbol(char* ctx, char* name)
{
	char* scope;
	char** locals;
	int i;

	scope = evt_MemberScopeScript != 0 ? evt_MemberScopeScript : ctx;
	i = 0;
	locals = *(char***) (ctx + 0xc28);
	if (locals != 0) {
		while (1) {
			if (i >= 8) {
				break;
			}
			if (locals[i + 4] != 0 && strcmp(locals[i + 4] + 4, name) == 0) {
				return locals[i + 4];
			}
			i++;
		}
	}
	for (i = 0; i < *(int*) (scope + 0x114); i++) {
		if (strcmp((*(struct sym_4260f0**) (scope + 0x108))[i].name, name) == 0) {
			return &(*(struct sym_4260f0**) (scope + 0x108))[i];
		}
	}
	for (i = 0; i < evt_GlobalVariableCount; i++) {
		if (strcmp(((struct sym_4260f0*)evt_GlobalVariables)[i].name, name) == 0) {
			return &((struct sym_4260f0*)evt_GlobalVariables)[i];
		}
	}
	return 0;
}
