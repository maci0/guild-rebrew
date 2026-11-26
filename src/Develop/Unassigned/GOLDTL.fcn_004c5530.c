


void __cdecl cm_StageRawPacketPayload(int, int);
int __cdecl cm_EnqueueClientPacket(void*);

void __cdecl cm_SendCopyEntityData(int packet)
{
	char buf[0x9c];
	int i;
	int* cursor;

	buf[0] = 0x1c;
	cursor = (int*) (packet + 0x38);
	for (i = 8; i != 0; i--) {
		if (*cursor == 0) {
			*cursor = -1;
		}
		cursor++;
	}
	cm_StageRawPacketPayload(0xf8, packet);
	cm_EnqueueClientPacket(buf);
}
