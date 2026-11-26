


void __cdecl cm_EnqueueClientPacket(void*);

void __cdecl cm_RequestUpdateResidenceDecor(int entityId)
{
	char buf[0x9c];

	buf[0] = 0x43;
	*(int*) (buf + 0x10) = entityId;
	cm_EnqueueClientPacket(buf);
}
