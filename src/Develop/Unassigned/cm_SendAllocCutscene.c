void __cdecl cm_StageRawPacketPayload(int, void*);
int __cdecl cm_EnqueueClientPacket(char*);

/* ADDRESS: GOLD 0x004c4fa0 */
int __cdecl cm_SendAllocCutscene(void* source)
{
	char buf[0x9c];

	buf[0] = 0x27;
	cm_StageRawPacketPayload(0x114, source);
	return cm_EnqueueClientPacket(buf);
}
