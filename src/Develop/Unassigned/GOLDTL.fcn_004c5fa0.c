


void __cdecl cm_EnqueueClientPacket(void*);

void __cdecl cm_SendSetGebUpgrade(int a1)
{
	char buf[0x9c];

	buf[0] = 0x3a;
	*(int*) (buf + 0x10) = a1;
	cm_EnqueueClientPacket(buf);
}
