


void __cdecl cm_EnqueueClientPacket(void*);

void __cdecl cm_RequestUpdateStraftatState(int actorId, int targetId, int actionId, int mode)
{
	char buf[0x9c];

	buf[0] = 0x3c;
	*(int*) (buf + 0x10) = actorId;
	*(int*) (buf + 0x14) = targetId;
	*(int*) (buf + 0x18) = actionId;
	*(int*) (buf + 0x1c) = mode;
	cm_EnqueueClientPacket(buf);
}
