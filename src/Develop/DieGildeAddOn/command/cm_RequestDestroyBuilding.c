


void __cdecl cm_EnqueueClientPacket(void*);

void __cdecl cm_RequestDestroyBuilding(int value)
{
	char buf[0x9c];

	buf[0] = 0x3b;
	*(int*) (buf + 0x10) = value;
	cm_EnqueueClientPacket(buf);
}
