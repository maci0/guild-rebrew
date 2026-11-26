


void __cdecl cm_EnqueueClientPacket(void*);

void __cdecl cm_RequestUpdateStraftatState(int a1, int a2, int a3, int a4)
{
	char buf[0x9c];

	buf[0] = 0x3c;
	*(int*) (buf + 0x10) = a1;
	*(int*) (buf + 0x14) = a2;
	*(int*) (buf + 0x18) = a3;
	*(int*) (buf + 0x1c) = a4;
	cm_EnqueueClientPacket(buf);
}
