


void __cdecl cm_EnqueueClientPacket(void*);

/* ADDRESS: GOLDDE 0x004b3250 */
void __cdecl cm_RequestLinkEvidence(int evidenceKey, int ownerId)
{
	char buf[0x9c];

	buf[0] = 0x24;
	*(int*) (buf + 0x14) = ownerId;
	*(int*) (buf + 0x10) = evidenceKey;
	cm_EnqueueClientPacket(buf);
}
