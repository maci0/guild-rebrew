


typedef struct
{
	int a;
	int b;
	int c;
	char flag;
	char pad[0x1f];
} CUT_ENTITY_SLOT_MSG;
// SIZE 0x2c

CUT_ENTITY_SLOT_MSG* __cdecl gm_FindOrCreateEntitySlot(char*, char*);
void __cdecl cm_SendUpdateCutsceneEntitySlot(int, CUT_ENTITY_SLOT_MSG*);

/* ADDRESS: GOLDDE 0x004be860 */
void __cdecl cut_SendExitSlotCommand(char* ctx, char* entity)
{
	CUT_ENTITY_SLOT_MSG* s;
	CUT_ENTITY_SLOT_MSG r;

	s = gm_FindOrCreateEntitySlot(ctx, entity);
	s->flag = 0;
	r = *s;
	r.a = *(int*) (entity + 4);
	r.b = 8;
	cm_SendUpdateCutsceneEntitySlot(*(int*) (ctx + 0x10), &r);
}
