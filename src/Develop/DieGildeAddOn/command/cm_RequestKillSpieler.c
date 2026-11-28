


void __cdecl cm_EnqueueClientPacket(void*);

/* ADDRESS: GOLDDE 0x004b3180 */
void __cdecl cm_RequestKillSpieler(int entityId, int flag)
{
	char buf[0x9c];

	buf[0] = 0x21;
	*(int*) (buf + 0x10) = entityId;
	*(int*) (buf + 0x14) = flag;
	cm_EnqueueClientPacket(buf);
}
