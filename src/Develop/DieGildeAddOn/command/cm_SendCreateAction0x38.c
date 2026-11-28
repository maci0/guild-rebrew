


void __cdecl cm_EnqueueClientPacket(void*);

/* ADDRESS: GOLDDE 0x004b35e0 */
void __cdecl cm_SendCreateAction0x38(int actor_id, int target_id)
{
	char buf[0x9c];

	buf[0] = 0x33;
	*(int*) (buf + 0x10) = actor_id;
	*(int*) (buf + 0x14) = target_id;
	cm_EnqueueClientPacket(buf);
}
