#include "Develop/DieGildeAddOn/game/entity_record.h"


typedef struct
{
	int id;
	int pad4;
	int kind;
	float f;
} Rec16;
// SIZE 0x10

typedef struct
{
	int n;
	int pad4;
	Rec16 recs[3];
} Set;
// SIZE 0x38

extern char gm_EntitySlotTable[];
#include "Develop/DieGildeAddOn/game/game_data.h"

char* __cdecl gm_StartFilteredEntitySearch(int a, int b, int kind);
void __cdecl he_NotifyDomizilStatus(char* e, char* r, int mode);

/* ADDRESS: GOLDDE 0x004db5c0 */
int __cdecl gm_NotifyDomizilCallback(Set* p)
{
	int i;
	int mode;
	char* r;
	char* e;

	for (i = 0; i < 3; i++) {
		if (p->n == i) {
			r = gm_StartFilteredEntitySearch(1, 1, p->recs[i].id);
			mode = 0;
			if (r != 0 && *(unsigned short*) (r + 0x27) != 0xffff) {
				e = ((char *)&((ENTITY_RECORD_VIEW *)gm_EntitySlotTable)[*(unsigned short*) (r + 0x27)]);
				if (p->recs[i].kind == 1) {
					mode = 2;
					if (!(p->recs[i].f > 25.0f)) {
						mode = 1;
					}
				}
				if ((*(char*)&((ENTITY_RECORD_VIEW*)e)->entity_type) == 6) {
					he_NotifyDomizilStatus(e, r, mode);
				}
			}
		}
	}
	return 0;
}
