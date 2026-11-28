


void __cdecl cm_EnqueueClientPacket(void*);

void __cdecl fcn_0064d530(void*, int, int);

void __cdecl cm_RequestPlayAnimation(int entity_id, int anim_name, char count)
{
	char buf[0x9c];

	*(int*) (buf + 0x10) = entity_id;
	buf[0] = 0x37;
	*(char*) (buf + 0x44) = count;
	fcn_0064d530(buf + 0x14, anim_name, 0x2f);
	cm_EnqueueClientPacket(buf);
}
