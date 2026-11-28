


void __cdecl cm_EnqueueClientPacket(void*);

/* ADDRESS: GOLDDE 0x004b3350 */
void __cdecl cm_RequestRemoveCutsceneParticipant(int cutsceneId, int participantId)
{
	char buf[0x9c];

	buf[0] = 0x2a;
	*(int*) (buf + 0x10) = cutsceneId;
	*(int*) (buf + 0x14) = participantId;
	cm_EnqueueClientPacket(buf);
}
