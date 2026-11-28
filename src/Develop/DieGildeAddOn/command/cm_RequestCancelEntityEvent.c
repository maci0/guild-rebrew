


void __cdecl cm_EnqueueClientPacket(void*);

/* ADDRESS: GOLDDE 0x004b3f10 */
void __cdecl cm_RequestCancelEntityEvent(int entity_id)
{
	char buf[0x9c];

	buf[0] = 0x4d;
	*(int*) (buf + 0x10) = entity_id;
	cm_EnqueueClientPacket(buf);
}
