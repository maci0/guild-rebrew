


void __cdecl cm_EnqueueClientPacket(void*);

void __cdecl cm_SendSetGebUpgrade(int building_id)
{
	char buf[0x9c];

	buf[0] = 0x3a;
	*(int*) (buf + 0x10) = building_id;
	cm_EnqueueClientPacket(buf);
}
