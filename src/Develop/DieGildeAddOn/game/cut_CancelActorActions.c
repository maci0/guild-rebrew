extern int cut_CombatCancelledEntity;



int __cdecl gm_LookupEntityRecordById(int);
void __cdecl io_FormatTextBuffer(void*, int, int);
void __cdecl d2_ShowStatusBanner(void*);

/* ADDRESS: GOLDDE 0x004c54a0 */
void __cdecl cut_CancelActorActions(void* request)
{
	char buf[0x100];

	cut_CombatCancelledEntity = gm_LookupEntityRecordById(*(int*) request);
	io_FormatTextBuffer(buf, 0x11b7, *(unsigned short*) cut_CombatCancelledEntity);
	d2_ShowStatusBanner(buf);
}
