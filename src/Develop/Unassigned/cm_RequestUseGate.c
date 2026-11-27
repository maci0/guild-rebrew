


void __cdecl cm_EnqueueClientPacket(void*);

void __cdecl cm_RequestUseGate(int actorId, int buildingId, int value)
{
	char buf[0x9c];

	buf[0] = 0x36;
	*(int*) (buf + 0x10) = actorId;
	*(int*) (buf + 0x14) = buildingId;
	*(int*) (buf + 0x18) = value;
	cm_EnqueueClientPacket(buf);
}
