int __cdecl cm_StageRawPacketPayload(unsigned short n, void* src);
int __cdecl cm_EnqueueClientPacket(void*);

/* ADDRESS: GOLDTL 0x004c59b0 */
void __cdecl fcn_004c59b0(void* source)
{
	char buf[0x9c];

	buf[0] = 0x28;
	cm_StageRawPacketPayload(0x114, source);
	cm_EnqueueClientPacket(buf);
}
