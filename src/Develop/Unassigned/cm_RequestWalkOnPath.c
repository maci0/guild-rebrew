


void __cdecl cm_EnqueueClientPacket(void*);

void __cdecl cm_RequestWalkOnPath(int entity_id, int x, int y, int target_id)
{
	char buf[0x9c];

	buf[0] = 0x2e;
	*(int*) (buf + 0x10) = entity_id;
	*(int*) (buf + 0x14) = x;
	*(int*) (buf + 0x18) = y;
	*(int*) (buf + 0x1c) = target_id;
	cm_EnqueueClientPacket(buf);
}
