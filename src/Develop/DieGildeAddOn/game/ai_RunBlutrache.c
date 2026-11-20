#include "Develop/DieGildeAddOn/game/spiel.h"
void *__cdecl gm_LookupEntityRecordById(int);
void __cdecl fcn_005100f0(int, int);
void __cdecl fcn_004c5420(int, int, int, int, int);
int __cdecl _ftol(void);
void __cdecl fcn_004c54c0(int, int, int, int);
void __cdecl he_ShowZigeunerGroupMessage(void *, int, int *);

/* ADDRESS: GOLDTL 0x004ab7d0 */
int __cdecl ai_RunBlutrache(int actor, char *a2, char *a3)
{
	int h;
	void *entity;
	int participants[4];
	int count;
	int i;
	int t;

	h = *(int *) (a2 + 0x10);
	if (a3 == 0 || actor == 0)
		return 0;
	entity = gm_LookupEntityRecordById(*(int *) (a2 + 4));
	if (entity == 0)
		return 0;
	participants[0] = (int) gm_LookupEntityRecordById(*(int *) (a2 + 0xc));
	if (participants[0] == 0)
		return 0;
	count = 1;
	participants[1] = (int) gm_LookupEntityRecordById(*(int *) (a2 + 8));
	if (participants[1] == 0)
		count = 2;
	participants[count] = (int) gm_LookupEntityRecordById(*(int *) (a3 + 0xc));
	if (participants[count] == 0)
		count++;
	participants[count] = (int) gm_LookupEntityRecordById(*(int *) (a3 + 8));
	if (participants[count] == 0)
		count++;
	fcn_005100f0(*(int *) (actor + 4), -h);
	fcn_004c5420(*(int *) (actor + 4), 0x1cc, 4, 8, 0);
	for (i = 0; i < count; i++) {
		t = 0x32 - (int) (fcn_00507e70((char *) actor, (char *) participants[i], 4) * -50.0f);
		fcn_004c54c0(*(unsigned short *) entity, *(unsigned short *) participants[i], -t, 1);
	}
	he_ShowZigeunerGroupMessage(entity, count, participants);
	return 0x44;
}
