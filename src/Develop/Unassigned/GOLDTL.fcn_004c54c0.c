extern float g_67db50;
extern float g_67db54;



void __cdecl cm_EnqueueClientPacket(void*);

void __cdecl cm_RequestCopyEntityData(int targetId, int sourceId, int value, int mode)
{
	char buf[0x9c];

	buf[0] = 0x1b;
	*(int*) (buf + 0x10) = targetId;
	*(int*) (buf + 0x14) = sourceId;
	*(int*) (buf + 0x18) = value;
	*(int*) (buf + 0x1c) = mode;
	*(int*) (buf + 0x20) = (*(int*)&g_67db54);
	*(int*) (buf + 0x24) = (int) g_67db50;
	cm_EnqueueClientPacket(buf);
}
