#include "Develop/DieGildeAddOn/game/spiel.h"
#include <string.h>

unsigned short* __cdecl gm_LookupEntityRecordById(int);
char* __cdecl he_StartHandlungSearch(int, int, int);
char* __cdecl he_fn_Handlung(void);

int __cdecl gm_CheckEntityType(char*);
unsigned short __cdecl gm_RandomMod(unsigned short);
void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl he_PostEntityMessage(int, int, char*, int, int, int);


/* ADDRESS: GOLDTL 0x004b99e0 */
int __cdecl gm_HandleMsg27PostTradeNews(int* request)
{
	char* x2;
	char* x1;
	char* y;
	char* ys[8];
	char* ss[8];
	char buf[0x200];
	unsigned short* entity;
	char* action;
	int count;
	int days;
	int index;

	count = 0;
	entity = gm_LookupEntityRecordById(request[0]);
	if (entity == 0)
		return 1;
	for (action = he_StartHandlungSearch(1, 0, 0xf); action != 0 && count < 8; action = he_fn_Handlung()) {
		gm_ResolveEntityById(0, (void**) (&y), 0, *(int*) (action + 0xac));
		if (y != 0 && *(int*) (y + 0xa) == *entity) {
			gm_ResolveEntityById((void**) (&x1), 0, 0, *(int*) (action + 0xb4));
			gm_ResolveEntityById((void**) (&x2), 0, 0, *(int*) (action + 0xb0));
			if ((x1 != 0 && gm_CheckEntityType(x1) != 0) || (x2 != 0 && gm_CheckEntityType(x2) != 0)) {
				if (*x2 != 'G' || *x1 != 'G') {
					ss[count] = action;
					ys[count] = y;
					count++;
				}
			}
		}
	}
	if (count == 0)
		return 0x400;
	days = gm_RandomMod(3) + 2;
	index = gm_RandomMod(count);
	action = ss[index];
	y = ys[index];
	gm_ResolveEntityById((void**) (&x2), 0, 0, *(int*) (action + 0xb0));
	gm_ResolveEntityById((void**) (&x1), 0, 0, *(int*) (action + 0xb4));
	if (x2 != 0 && x1 != 0) {
		io_FormatTextBuffer(buf, *(unsigned short*) (request + 1) + 0x12e7, x2, x1, days);
		he_PostEntityMessage(*(int*) (entity + 2), *(int*) (entity + 2), buf, strlen(buf) > 0x100, 0x5ef, 0);
	}
	return 0;
}
