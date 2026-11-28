


void __cdecl cm_EnqueueClientPacket(void*);

/* ADDRESS: GOLDDE 0x004b4270 */
void __cdecl cm_RequestRemoveCutscene(int cutsceneId)
{
	char buf[0x9c];

	buf[0] = 0x58;
	*(int*) (buf + 0x10) = cutsceneId;
	cm_EnqueueClientPacket(buf);
}
