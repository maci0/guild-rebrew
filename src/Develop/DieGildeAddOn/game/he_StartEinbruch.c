#include "Develop/client_types.h"

extern pos14_7f4c00 gm_GameTime;

char* __cdecl he_StartHandlungSearch(int, int, int);
char* __cdecl he_fn_Handlung(void);
void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);

/* Finds a record other than the entity whose 0xac field matches the entity's,
 * flags that entity, then copies the current selection into it. */
/* ADDRESS: GOLDTL 0x00569f70 */
void __cdecl he_StartEinbruch(char* action)
{
	pos14_7f4c00* clockPtr;
	char* cur;

	cur = he_StartHandlungSearch(1, 0, 0x3f);
	if (cur != 0) {
		do {
			if (cur != action &&
			    *(int*) (cur + 0xac) == *(int*) (action + 0xac)) {
				break;
			}
			cur = he_fn_Handlung();
		} while (cur != 0);
		if (cur != 0) {
			*(int*) (action + 0x70) = -1;
		}
	}
	clockPtr = (pos14_7f4c00*) (action + 0x52);
	*clockPtr = gm_GameTime;
	gm_AddTime(clockPtr, 0, 0, 1);
}
