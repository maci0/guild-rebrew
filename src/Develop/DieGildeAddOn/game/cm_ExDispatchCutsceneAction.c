extern int* cut_ActiveCutscene;

char* __cdecl gm_LookupEntityRecordIn32SlotTable(int);
void __cdecl cut_SyncEntityTransform(char*, float*, float*, int);
void __cdecl cut_StartCombatAttack(int*);
void __cdecl gm_CancelEntityActionQueue(int*);
void __cdecl cut_QueueHideCharacter(int*);
void __cdecl gm_StartGroundCollectAction(int*);
void __cdecl gm_StartGroundPickupAnimation(int*);
void __cdecl cut_CancelActorActions(int*);
void __cdecl d3_UpdateConquerFlag(int*);


/* ADDRESS: GOLDTL 0x004cd330 */
/* ADDRESS: GOLDDE 0x004bab10 */
int __cdecl cm_ExDispatchCutsceneAction(unsigned char* command, char* result)
{
	char* e;

	if (cut_ActiveCutscene == 0 || *cut_ActiveCutscene != *(int*) (command + 0x10))
		return 1;
	e = gm_LookupEntityRecordIn32SlotTable(*(int*) (command + 0x35));
	switch (command[0x14]) {
	case 2:
		if (e[8] != 0) {
			cut_SyncEntityTransform(e, (float*) (command + 0x15), (float*) (command + 0x25), *(int*) (command + 0x31));
			cut_StartCombatAttack((int*) (command + 0x35));
		}
		break;
	case 6:
		if (e[8] != 0) {
			cut_SyncEntityTransform(e, (float*) (command + 0x15), (float*) (command + 0x25), *(int*) (command + 0x31));
			gm_CancelEntityActionQueue((int*) (command + 0x35));
		}
		break;
	case 1:
		if (e[8] != 0)
			cut_QueueHideCharacter((int*) (command + 0x35));
		break;
	case 4:
		if (e[8] != 0)
			gm_StartGroundCollectAction((int*) (command + 0x35));
		break;
	case 5:
		if (e[8] != 0)
			gm_StartGroundPickupAnimation((int*) (command + 0x35));
		break;
	case 7:
		cut_CancelActorActions((int*) (command + 0x35));
		break;
	case 3:
		if (e[8] != 0) {
			cut_SyncEntityTransform(e, (float*) (command + 0x15), (float*) (command + 0x25), *(int*) (command + 0x31));
			d3_UpdateConquerFlag((int*) (command + 0x35));
		}
		break;
	}
	if (result != 0) {
		result[0] = 1;
		result[1] = 8;
		*(int*) (result + 6) = 0;
	}
	return 0;
}
