


void __cdecl cm_EnqueueClientPacket(void*);

/* ADDRESS: GOLDDE 0x004b4240 */
void __cdecl cm_SendEntityLookup(int entity_id)
{
	char buf[0x9c];

	buf[0] = 0x57;
	*(int*) (buf + 0x10) = entity_id;
	cm_EnqueueClientPacket(buf);
}
