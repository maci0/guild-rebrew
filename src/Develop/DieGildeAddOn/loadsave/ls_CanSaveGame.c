extern char gm_InWorldHud;
extern char gm_InWorldHud;



extern char gm_EntitySlotTable[];

/* ADDRESS: GOLDDE 0x005c5470 */
int __cdecl ls_CanSaveGame(void)
{
	unsigned char* entity;
	int canSave;

	canSave = 1;
	if (*(char*) ((char*)&gm_InWorldHud) != 0) {
		for (entity = (unsigned char*) gm_EntitySlotTable + 2; (int) entity < (int) gm_EntitySlotTable + 0x65402; entity += 0x21c) {
			if (entity[6] > 0 && (entity[0] == 6 || entity[0] == 7) && *(int*) (entity + 0x20a) != -1) {
				canSave = 0;
				break;
			}
		}
	} else {
		canSave = 0;
	}
	return canSave;
}
