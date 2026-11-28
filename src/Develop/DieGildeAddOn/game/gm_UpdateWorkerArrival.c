typedef struct Ent {
	unsigned short id;
	unsigned char kind;
	char pad3[0x165 - 3];
	unsigned char role;
	char pad166[0x16c - 0x166];
	char* home;
	char pad170[0x184 - 0x170];
	char* job;
	char pad188[0x1b4 - 0x188];
	unsigned int flags;
	char pad1b8[0x21c - 0x1b8];
} Ent;
// SIZE 0x21c

extern char gm_EntitySlotTable[];
extern unsigned short gm_GameTimeHour;

float __cdecl gm_RandomFloat01(void);
void __cdecl he_SetEntityScriptFlag(Ent* e, int a2);

/* ADDRESS: GOLDTL 0x004833a0 */
/* ADDRESS: GOLDDE 0x00472350 */
void __cdecl gm_UpdateWorkerArrival(Ent* entity)
{
	Ent* found;
	int i;

	found = 0;
	if ((*(short*)&gm_GameTimeHour) != 7 && (*(short*)&gm_GameTimeHour) != 0xc && (*(short*)&gm_GameTimeHour) != 0x12) {
		entity->flags &= ~0x1000;
		return;
	}
	if (entity->flags & 0x1000) {
		return;
	}
	entity->flags |= 0x1000;
	for (i = 0; found == 0 && i < 768; i++) {
		if (((Ent*)gm_EntitySlotTable)[i].id != 0xffff && ((Ent*)gm_EntitySlotTable)[i].home == entity->home && ((Ent*)gm_EntitySlotTable)[i].role == 0x1c && ((Ent*)gm_EntitySlotTable)[i].kind == 0x14
		    && (((Ent*)gm_EntitySlotTable)[i].flags & 1) && ((Ent*)gm_EntitySlotTable)[i].job && *(int*) (((Ent*)gm_EntitySlotTable)[i].job + 0x2c) == *(int*) (((Ent*)gm_EntitySlotTable)[i].home + 1)) {
			found = &((Ent*)gm_EntitySlotTable)[i];
		}
	}
	if (found && gm_RandomFloat01() > 0.75f) {
		he_SetEntityScriptFlag(found, 0);
	}
}
