


void __cdecl cm_EnqueueClientPacket(void*);

void __cdecl cm_SendRemoveStraftat(int a1, int a2)
{
	char buf[0x9c];

	buf[0] = 0x23;
	*(int*) (buf + 0x10) = a1;
	*(int*) (buf + 0x14) = a2;
	cm_EnqueueClientPacket(buf);
}
