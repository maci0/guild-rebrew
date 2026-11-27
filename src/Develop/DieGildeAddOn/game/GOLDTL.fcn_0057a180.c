extern char g_773d75;

char* __cdecl gm_LookupEntityRecordById(int a1);
int __cdecl gm_GetSeasonTreasury(char* entity, char season);
void __cdecl cm_RequestMoveCredits(int a1, int a2, char a3, int a4);
void __cdecl he_FreeAction(void* u);
float __cdecl gm_ApplyEntityHealthDelta(unsigned short id, int delta);

/* Releases every played sound of the behaviour when its counter ran out. */
/* ADDRESS: GOLDTL 0x0057a180 */
void __cdecl he_RunDeathPactCollection(char* action)
{
	char* entity;
	char* sound;
	int* p;
	int i;
	int found;
	int count;

	if (*(int*) (action + 0x70) < -2) {
		return;
	}
	if (*(int*) (action + 0x70) > 0) {
		return;
	}
	entity = gm_LookupEntityRecordById(*(int*) (action + 0xc));
	if (entity != 0) {
		count = gm_GetSeasonTreasury(entity, g_773d75);
		if (count > *(int*) (action + 0xac)) {
			cm_RequestMoveCredits(-1, *(int*) (entity + 4), g_773d75, *(int*) (action + 0xac));
			he_FreeAction(action);
			return;
		}
		found = 0;
		p = (int*) (entity + 0x68);
		for (i = 0; i < 5; i++) {
			if (*p != -1) {
				sound = gm_LookupEntityRecordById(*p);
				if (sound != 0) {
					gm_ApplyEntityHealthDelta(*(unsigned short*) sound, -1001);
					found = 1;
				}
			}
			p++;
		}
		if (found == 0) {
			gm_ApplyEntityHealthDelta(*(unsigned short*) entity, -1001);
		}
		he_FreeAction(action);
	}
	he_FreeAction(action);
}
