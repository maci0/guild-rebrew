


void __cdecl cm_EnqueueClientPacket(void*);

void __cdecl fcn_0064d530(void*, int, int);

void __cdecl cm_SendLogAction(int source)
{
	char buf[0x9c];

	buf[0] = 5;
	fcn_0064d530(buf + 0x10, source, 0x80);
	cm_EnqueueClientPacket(buf);
}
