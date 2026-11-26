

int __cdecl cm_EnqueueClientPacket(char*);
void __cdecl cm_StageRawPacketPayload(int, void*);

int __cdecl fcn_004c5980(void* data)
{
	char buf[0x9c];

	buf[0] = 0x27;
	cm_StageRawPacketPayload(0x114, data);
	return cm_EnqueueClientPacket(buf);
}
