


void __cdecl cm_EnqueueClientPacket(void*);

void __cdecl cm_RequestSendGameHeader(int totalBytes)
{
	char buf[0x9c];

	buf[0] = 8;
	*(int*) (buf + 0x10) = totalBytes;
	cm_EnqueueClientPacket(buf);
}
