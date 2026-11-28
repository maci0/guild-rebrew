


void __cdecl cm_EnqueueClientPacket(void*);

/* ADDRESS: GOLDDE 0x004b3210 */
void __cdecl cm_SendRemoveStraftat(int crime_id, int entity_id)
{
	char buf[0x9c];

	buf[0] = 0x23;
	*(int*) (buf + 0x10) = crime_id;
	*(int*) (buf + 0x14) = entity_id;
	cm_EnqueueClientPacket(buf);
}
