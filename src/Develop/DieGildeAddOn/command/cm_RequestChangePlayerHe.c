


void __cdecl cm_EnqueueClientPacket(void*);

/* ADDRESS: GOLDDE 0x004b3cf0 */
void __cdecl cm_RequestChangePlayerHe(int entity_id, int kind, int unused)
{
	char buf[0x9c];

	buf[0] = 0x47;
	*(int*) (buf + 0x10) = entity_id;
	*(int*) (buf + 0x14) = kind;
	*(int*) (buf + 0x18) = unused;
	cm_EnqueueClientPacket(buf);
}
