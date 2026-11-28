


void __cdecl cm_EnqueueClientPacket(void*);

/* ADDRESS: GOLDDE 0x004b3bf0 */
void __cdecl cm_RequestUpdateResidenceDecor(int entityId)
{
	char buf[0x9c];

	buf[0] = 0x43;
	*(int*) (buf + 0x10) = entityId;
	cm_EnqueueClientPacket(buf);
}
