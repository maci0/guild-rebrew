


void __cdecl cm_EnqueueClientPacket(void*);

void __cdecl cm_RequestMoveCredits(int dst_id, int src_id, char kind, int amount)
{
	char buf[0x9c];

	buf[0] = 0x0f;
	*(int*) (buf + 0x10) = dst_id;
	*(int*) (buf + 0x14) = src_id;
	*(char*) (buf + 0x1c) = kind;
	*(int*) (buf + 0x1d) = amount;
	cm_EnqueueClientPacket(buf);
}
