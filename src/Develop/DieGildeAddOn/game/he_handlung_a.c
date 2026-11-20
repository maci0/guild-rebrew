extern char g_7f4ca0[];
#include "Develop/DieGildeAddOn/game/entity_record.h"
char* __cdecl he_StartHandlungSearch(int a, int b, int c);
char* __cdecl he_fn_Handlung(void);

char* __cdecl he_StartHandlungSearch(int a, int b, int c);
char* __cdecl he_fn_Handlung(void);
char* __cdecl gm_StartFilteredEntitySearch(int a, int b, int c);

/* ADDRESS: GOLD 0x0050a150 */
/* ADDRESS: GOLDTL 0x0050d5d0 */
int __cdecl fcn_0050d5d0(int id, char* owner, char** out)
{
	char* p;
	int n;

	n = 0;
	p = he_StartHandlungSearch(1, n, 0x23);
	while (p != 0) {
		if (n >= 9) {
			break;
		}
		if (*(int*) (p + 0xb0) == *(int*) (((char *)&((ENTITY_RECORD_VIEW *)g_7f4ca0)[id] + 4)) && (owner == 0 || *(int*) (p + 0xac) == *(int*) (owner + 1))) {
			out[n++] = p;
		}
		p = he_fn_Handlung();
	}
	return n;
}

/* ADDRESS: GOLD 0x0050a1c0 */
/* ADDRESS: GOLDTL 0x0050d640 */
int __cdecl fcn_0050d640(int key, char* obj, unsigned int id, char** out)
{
	char* p;
	char* r;
	int n;

	n = 0;
	p = he_StartHandlungSearch(1, n, 0x23);
	while (p != 0) {
		if (n >= 9) {
			break;
		}
		r = gm_StartFilteredEntitySearch(1, 1, *(int*) (p + 0xac));
		if (r != 0 && *(unsigned short*) (r + 0x27) == key && (obj == 0 || obj == r)
		    && (id == 0xffff || *(int*) (((char *)&((ENTITY_RECORD_VIEW *)g_7f4ca0)[id] + 4)) == *(int*) (p + 0xb0))) {
			out[n++] = p;
		}
		p = he_fn_Handlung();
	}
	return n;
}
