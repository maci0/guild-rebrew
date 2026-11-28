


void __cdecl cm_EnqueueClientPacket(void*);

/* ADDRESS: GOLDDE 0x004b2af0 */
void __cdecl cm_SendChangePlayerIdentity(int player_id, int identity_id)
{
	char buf[0x9c];

	buf[0] = 0x0d;
	*(int*) (buf + 0x10) = player_id;
	*(int*) (buf + 0x14) = identity_id;
	cm_EnqueueClientPacket(buf);
}
