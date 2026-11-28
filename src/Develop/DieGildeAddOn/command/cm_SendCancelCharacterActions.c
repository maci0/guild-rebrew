


void __cdecl cm_EnqueueClientPacket(void*);

/* ADDRESS: GOLDDE 0x004b35b0 */
void __cdecl cm_SendCancelCharacterActions(int characterId)
{
	char buf[0x9c];

	buf[0] = 0x31;
	*(int*) (buf + 0x10) = characterId;
	cm_EnqueueClientPacket(buf);
}
