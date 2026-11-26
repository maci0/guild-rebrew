


void __cdecl cm_EnqueueClientPacket(void*);

void __cdecl fcn_004c6300(int a1)
{
	char buf[0x9c];

	buf[0] = 0x42;
	*(int*) (buf + 0x10) = a1;
	cm_EnqueueClientPacket(buf);
}
