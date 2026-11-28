


void __cdecl cm_EnqueueClientPacket(void*);

/* ADDRESS: GOLDDE 0x004b33d0 */
void __cdecl cm_SendChainRecordLookup(int target_id, char op, char mode, short slot, char flag, int param)
{
	char buf[0x9c];

	buf[0] = 0x2c;
	*(int*) (buf + 0x14) = target_id;
	*(char*) (buf + 0x18) = op;
	*(char*) (buf + 0x19) = mode;
	*(short*) (buf + 0x1a) = slot;
	*(char*) (buf + 0x1c) = flag;
	*(int*) (buf + 0x1d) = param;
	cm_EnqueueClientPacket(buf);
}
