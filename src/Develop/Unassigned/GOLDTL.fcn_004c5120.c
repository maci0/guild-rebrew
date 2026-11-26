

void __cdecl cm_EnqueueClientPacket(void*);

void __cdecl cm_RequestFreeEntity(unsigned short entityId)
{
	char buf[0x9c];

	buf[0] = 0xe;
	*(unsigned short*) (buf + 0x10) = entityId;
	cm_EnqueueClientPacket(buf);
}
