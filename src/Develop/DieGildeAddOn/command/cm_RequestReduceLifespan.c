


void __cdecl cm_EnqueueClientPacket(void*);

/* ADDRESS: GOLDDE 0x004b4080 */
void __cdecl cm_RequestReduceLifespan(int entityId, int amount, int flag)
{
	char buf[0x9c];

	buf[0] = 0x52;
	*(int*) (buf + 0x10) = entityId;
	*(int*) (buf + 0x14) = amount;
	*(int*) (buf + 0x18) = flag;
	cm_EnqueueClientPacket(buf);
}
