

#include <string.h>

char* __cdecl sbs_FindSet(int id);

char* __cdecl fcn_00423c50(int id, const char* name)
{
	char* r;
	char* e;

	r = 0;
	e = sbs_FindSet(id);
	if (e != 0) {
		for (r = *(char**) (e + 0x38); r != 0; r = *(char**) (r + 0x104)) {
			if (strcmp(r, name) == 0) {
				break;
			}
		}
	}
	return r;
}
