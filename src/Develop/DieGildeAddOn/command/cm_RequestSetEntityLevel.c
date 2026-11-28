


void __cdecl cm_EnqueueClientPacket(void*);

/* ADDRESS: GOLDDE 0x004b3d30 */
void __cdecl cm_RequestSetEntityLevel(int entityId, char level)
{
	char buf[0x9c];

	buf[0] = 0x48;
	*(int*) (buf + 0x10) = entityId;
	*(char*) (buf + 0x14) = level;
	cm_EnqueueClientPacket(buf);
}
