

void __cdecl cm_EnqueueClientPacket(void*);

void __cdecl fcn_004c5770(void)
{
	char buf[0x9c];

	buf[0] = 0x1f;
	cm_EnqueueClientPacket(buf);
}
