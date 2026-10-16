#include <string.h>
#include "client_scene_transform.h"
#include "client_placement.h"

#ifdef REBREW_GOLD
void __cdecl fcn_00458a10(char* object, float* position, float* result);
#else
void __cdecl fcn_00455350(char* object, float* position, float* result);
#endif

/* ADDRESS: GOLD 0x0058fc80 */
/* ADDRESS: GOLDTL 0x00598550 */
char __cdecl fcn_00598550(char* object, void* context)
{
	float position[4];
	LC_GEBAEUDE_BAUPLATZ* result;
	char* name;

	result = context;
	if (_strnicmp(object, "bk_", 3) == 0 || _strnicmp(object + 1, "bk_", 3) == 0) {
#ifdef REBREW_GOLD
		fcn_00458a10(object, (float*) (object + 0x4c), position);
#else
		fcn_00455350(object, (float*) (object + 0x4c), position);
#endif
		if (fcn_00451840(result->position, position, 100.0f)) {
			result->node = object;
			name = strstr(object, "bk_");
			if (name != 0) {
				strcpy(result->name, name);
			}
			return 0;
		}
	}
	return 1;
}
