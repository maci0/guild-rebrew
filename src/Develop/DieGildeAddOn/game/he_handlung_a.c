extern char g_7f4ca0[];
#include "Develop/DieGildeAddOn/game/entity_record.h"
char* __cdecl he_StartHandlungSearch(int a, int b, int c);
char* __cdecl he_fn_Handlung(void);

char* __cdecl he_StartHandlungSearch(int a, int b, int c);
char* __cdecl he_fn_Handlung(void);
char* __cdecl gm_StartFilteredEntitySearch(int a, int b, int c);

/* ADDRESS: GOLD 0x0050a150 */
/* ADDRESS: GOLDTL 0x0050d5d0 */
int __cdecl he_GetActiveKrediteByBorrower(int id, char* owner, char** out)
{
	char* action;
	int count;

	count = 0;
	action = he_StartHandlungSearch(1, count, 0x23);
	while (action != 0) {
		if (count >= 9) {
			break;
		}
		if (*(int*) (action + 0xb0) == *(int*) (((char *)&((ENTITY_RECORD_VIEW *)g_7f4ca0)[id] + 4)) && (owner == 0 || *(int*) (action + 0xac) == *(int*) (owner + 1))) {
			out[count++] = action;
		}
		action = he_fn_Handlung();
	}
	return count;
}

/* ADDRESS: GOLD 0x0050a1c0 */
/* ADDRESS: GOLDTL 0x0050d640 */
int __cdecl he_GetActiveKrediteByLender(int key, char* obj, unsigned int id, char** out)
{
	char* action;
	char* lender;
	int count;

	count = 0;
	action = he_StartHandlungSearch(1, count, 0x23);
	while (action != 0) {
		if (count >= 9) {
			break;
		}
		lender = gm_StartFilteredEntitySearch(1, 1, *(int*) (action + 0xac));
		if (lender != 0 && *(unsigned short*) (lender + 0x27) == key && (obj == 0 || obj == lender)
		    && (id == 0xffff || *(int*) (((char *)&((ENTITY_RECORD_VIEW *)g_7f4ca0)[id] + 4)) == *(int*) (action + 0xb0))) {
			out[count++] = action;
		}
		action = he_fn_Handlung();
	}
	return count;
}
