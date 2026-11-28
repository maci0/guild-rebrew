


void __cdecl cm_EnqueueClientPacket(void*);

/* ADDRESS: GOLDDE 0x004b43a0 */
void __cdecl cm_RequestModifyEntityLevel(int entityId, int index, int delta)
{
	char buf[0x9c];

	buf[0] = 0x5d;
	*(int*) (buf + 0x10) = entityId;
	*(int*) (buf + 0x14) = index;
	*(int*) (buf + 0x18) = delta;
	cm_EnqueueClientPacket(buf);
}
