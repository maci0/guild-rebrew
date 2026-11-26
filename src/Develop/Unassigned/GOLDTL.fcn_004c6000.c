


void __cdecl cm_EnqueueClientPacket(void*);

void __cdecl cm_RequestSetWohnsitz(int entity_id, int building_id)
{
	char buf[0x9c];

	buf[0] = 0x39;
	*(int*) (buf + 0x14) = entity_id;
	*(int*) (buf + 0x10) = building_id;
	cm_EnqueueClientPacket(buf);
}
