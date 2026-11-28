


void __cdecl cm_EnqueueClientPacket(void*);

/* ADDRESS: GOLDDE 0x004b4570 */
void __cdecl cm_RequestSetCutsceneMaster(char* event, char* entity)
{
	char buf[0x9c];

	buf[0] = 0x65;
	*(int*) (buf + 0x10) = *(int*) event;
	*(int*) (buf + 0x14) = *(int*) (entity + 4);
	cm_EnqueueClientPacket(buf);
}
