

void __cdecl cm_EnqueueClientPacket(void*);

void __cdecl cm_RequestExitToFrameLoop(void)
{
	char buf[0x9c];

	buf[0] = 0x1f;
	cm_EnqueueClientPacket(buf);
}
