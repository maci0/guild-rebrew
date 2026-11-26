


void __cdecl cm_EnqueueClientPacket(void*);

void __cdecl fcn_004c6000(int a1, int a2)
{
	char buf[0x9c];

	buf[0] = 0x39;
	*(int*) (buf + 0x14) = a1;
	*(int*) (buf + 0x10) = a2;
	cm_EnqueueClientPacket(buf);
}
