


void __cdecl cm_EnqueueClientPacket(void*);

void __cdecl cm_RequestClearLagerslot(int entity_id, unsigned short item_id)
{
	char buf[0x9c];

	buf[0] = 0x14;
	*(int*) (buf + 0x10) = entity_id;
	*(unsigned short*) (buf + 0x14) = item_id;
	cm_EnqueueClientPacket(buf);
}
