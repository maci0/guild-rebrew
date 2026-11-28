


int __cdecl cm_EnqueueClientPacket(char*);

/* ADDRESS: GOLDDE 0x004b29d0 */
int __cdecl cm_RequestAllocSpieler(char type, int motherId, int fatherId, short parentId, int locationId, char statA, char statB, char flags)
{
	char buf[0x9c];

	buf[0] = 0xb;
	buf[0x14] = type;
	*(int*) (buf + 0x15) = motherId;
	*(int*) (buf + 0x19) = fatherId;
	*(short*) (buf + 0x1d) = parentId;
	*(int*) (buf + 0x1f) = locationId;
	buf[0x23] = statA;
	buf[0x24] = statB;
	buf[0x25] = flags;
	return cm_EnqueueClientPacket(buf);
}
