#include <string.h>

// SIZE 0x30
struct var_425d90 {
	unsigned int type : 4;
	char name[0x20];
	int valid;
	int flags;
	void* ptr;
};

extern struct var_425d90* g_14cb8e0;
extern int g_14cb8e4;
extern unsigned int g_14cb8e8;

void* __cdecl fcn_0041db70(int size, const char* tag);
void __cdecl fcn_0041ddd0(void*);

// FUNCTION: GOLDTL 0x425d90
// SIZE: 293

/* Registers a named script variable bound to a C variable. */
struct var_425d90* __cdecl fcn_00425d90(char* name, void* ptr, int type)
{
	struct var_425d90* vars;

	if (g_14cb8e8 < (unsigned int) (g_14cb8e4 + 0x30)) {
		vars = fcn_0041db70((g_14cb8e4 + 0x10) * sizeof(struct var_425d90), "evt:t");
		if (g_14cb8e0 != 0) {
			memcpy(vars, g_14cb8e0, g_14cb8e4 * sizeof(struct var_425d90));
			fcn_0041ddd0(g_14cb8e0);
		}
		g_14cb8e0 = vars;
		g_14cb8e8 += 0x300;
	}
	strcpy(g_14cb8e0[g_14cb8e4].name, name);
	g_14cb8e0[g_14cb8e4].type = type;
	g_14cb8e0[g_14cb8e4].flags = 0;
	g_14cb8e0[g_14cb8e4].ptr = ptr;
	g_14cb8e0[g_14cb8e4].valid = 1;
	g_14cb8e4++;
	return &g_14cb8e0[g_14cb8e4 - 1];
}
