

void __cdecl cm_EnqueueClientPacket(void*);

void __cdecl fcn_004c6ea0(char* source)
{
	char buf[0x9c];

	buf[0] = 0x69;
	*(int*) (buf + 0x10) = *(int*) (source + 2);
	cm_EnqueueClientPacket(buf);
}
