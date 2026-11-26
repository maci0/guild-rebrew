


void __cdecl cm_EnqueueClientPacket(void*);

void __cdecl cm_SendKillTransporter(int a1)
{
	char buf[0x9c];

	buf[0] = 0x4a;
	*(int*) (buf + 0x10) = a1;
	cm_EnqueueClientPacket(buf);
}
