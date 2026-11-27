


void __cdecl cm_EnqueueClientPacket(void*);

void __cdecl cm_RequestTransferCurrencyNoKill(int destId, int srcId, char slotKind, int amount)
{
	char buf[0x9c];

	buf[0] = 0x10;
	*(int*) (buf + 0x10) = destId;
	*(int*) (buf + 0x14) = srcId;
	*(char*) (buf + 0x1c) = slotKind;
	*(int*) (buf + 0x1d) = amount;
	cm_EnqueueClientPacket(buf);
}
