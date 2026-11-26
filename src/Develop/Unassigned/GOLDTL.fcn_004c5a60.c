

void __cdecl cm_EnqueueClientPacket(void*);

void __cdecl cm_SendRemoveLinkedObject(int entityId, int slotKind, int nodeId)
{
	char buf[0x9c];

	buf[0] = 0x2b;
	*(int*) (buf + 0x10) = entityId;
	*(int*) (buf + 0x14) = slotKind;
	*(int*) (buf + 0x18) = nodeId;
	cm_EnqueueClientPacket(buf);
}
