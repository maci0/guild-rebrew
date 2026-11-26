


void __cdecl cm_EnqueueClientPacket(void*);

void __cdecl cm_SendSetGebBesitzer(int gebId, int eigentuemerId, int besitzerId)
{
	char buf[0x9c];

	buf[0] = 0x38;
	*(int*) (buf + 0x10) = gebId;
	*(int*) (buf + 0x14) = eigentuemerId;
	*(int*) (buf + 0x18) = besitzerId;
	cm_EnqueueClientPacket(buf);
}
