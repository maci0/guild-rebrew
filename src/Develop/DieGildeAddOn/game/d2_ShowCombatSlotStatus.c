extern char* d3_ActiveScene;

char* __cdecl gm_FindOrCreateEntitySlot(int, char*);
char* __cdecl gm_GetEquippedCombatGear(char*);
char* __cdecl gm_LookupEntityRecordIn32SlotTable(int);
char __cdecl d3sm_SampleHeight(int, int, void*, void*, void*);
void __cdecl d3_SetObjectColorRgb(int, int, int, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl d2_ShowStatusBanner(char*);

/* ADDRESS: GOLDTL 0x004cfe60 */
void __cdecl d2_ShowCombatSlotStatus(int slotId, char* entity)
{
	char buf[0x100];
	char* rec;
	char* gear;
	char* opponent;
	int top;
	int sceneObj;
	int col;
	int row;
	int height;

	top = *(int*) (d3_ActiveScene + 0xb0);
	rec = gm_FindOrCreateEntitySlot(slotId, entity);
	gear = gm_GetEquippedCombatGear(entity);
	if (rec == 0) {
		return;
	}
	switch (*(int*) (rec + 4)) {
	case 1:
		io_FormatTextBuffer(buf, 0x1174, *(int*) (gear + 0x54), *(unsigned short*) entity);
		d2_ShowStatusBanner(buf);
		return;
	case 2:
		opponent = gm_LookupEntityRecordIn32SlotTable(*(int*) (rec + 0x10));
		sceneObj = *(int*) (*(int*) (opponent + 0x184) + 0x34);
		if (d3sm_SampleHeight(top, sceneObj + 0x4c, &col, &row, &height)) {
			d3_SetObjectColorRgb(sceneObj, 0xff, 0, 0);
		}
		{
			char* oppGear = gm_GetEquippedCombatGear(opponent);
			io_FormatTextBuffer(buf, 0x1177, *(int*) (gear + 0x54), *(unsigned short*) entity,
				*(int*) (oppGear + 0x54), *(unsigned short*) opponent);
		}
		d2_ShowStatusBanner(buf);
		return;
	case 3:
		io_FormatTextBuffer(buf, 0x1175, *(int*) (gear + 0x54), *(unsigned short*) entity);
		d2_ShowStatusBanner(buf);
		return;
	case 4:
		io_FormatTextBuffer(buf, 0x117c, *(int*) (gear + 0x54), *(unsigned short*) entity);
		d2_ShowStatusBanner(buf);
		return;
	}
}
