


void __cdecl cm_EnqueueClientPacket(void*);

void __cdecl cm_SendBlockCharacter(int entityId, int delta, int vacateOffices)
{
	char buf[0x9c];

	buf[0] = 0x5b;
	*(int*) (buf + 0x10) = entityId;
	*(int*) (buf + 0x14) = delta;
	*(int*) (buf + 0x18) = vacateOffices;
	cm_EnqueueClientPacket(buf);
}
