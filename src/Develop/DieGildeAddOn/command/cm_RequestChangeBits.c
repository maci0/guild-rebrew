


void __cdecl cm_EnqueueClientPacket(void*);

/* ADDRESS: GOLDDE 0x004b2de0 */
void __cdecl cm_RequestChangeBits(int entityId, int offset, int size, int setMask, int clearMask)
{
	char buf[0x9c];

	buf[0] = 0x19;
	*(int*) (buf + 0x10) = entityId;
	*(int*) (buf + 0x14) = offset;
	*(int*) (buf + 0x18) = size;
	*(int*) (buf + 0x1c) = setMask;
	*(int*) (buf + 0x20) = clearMask;
	cm_EnqueueClientPacket(buf);
}
