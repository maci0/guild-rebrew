#include <string.h>

// SIZE 0x30
struct var_425d90 {
	unsigned int type : 4;
	char name[0x20];
	int valid;
	int flags;
	void* ptr;
};

extern void* evt_GlobalVariables;
extern int evt_GlobalVariableCount;
extern unsigned int g_14cb8e8;

void* __cdecl m_alloc(int size, const char* tag);
void __cdecl m_FreeTracked(void*);


/* Registers a named script variable bound to a C variable. */
/* ADDRESS: GOLD 0x00427570 */
/* ADDRESS: GOLDTL 0x00425d90 */
struct var_425d90* __cdecl evt_RegisterVariable(char* name, void* ptr, int type)
{
	struct var_425d90* vars;

	if (g_14cb8e8 < (unsigned int) (evt_GlobalVariableCount + 0x30)) {
		vars = m_alloc((evt_GlobalVariableCount + 0x10) * sizeof(struct var_425d90), "evt:t");
		if ((*(struct var_425d90**)&evt_GlobalVariables) != 0) {
			memcpy(vars, (*(struct var_425d90**)&evt_GlobalVariables), evt_GlobalVariableCount * sizeof(struct var_425d90));
			m_FreeTracked((*(struct var_425d90**)&evt_GlobalVariables));
		}
		(*(struct var_425d90**)&evt_GlobalVariables) = vars;
		g_14cb8e8 += 0x300;
	}
	strcpy((*(struct var_425d90**)&evt_GlobalVariables)[evt_GlobalVariableCount].name, name);
	(*(struct var_425d90**)&evt_GlobalVariables)[evt_GlobalVariableCount].type = type;
	(*(struct var_425d90**)&evt_GlobalVariables)[evt_GlobalVariableCount].flags = 0;
	(*(struct var_425d90**)&evt_GlobalVariables)[evt_GlobalVariableCount].ptr = ptr;
	(*(struct var_425d90**)&evt_GlobalVariables)[evt_GlobalVariableCount].valid = 1;
	evt_GlobalVariableCount++;
	return &(*(struct var_425d90**)&evt_GlobalVariables)[evt_GlobalVariableCount - 1];
}
