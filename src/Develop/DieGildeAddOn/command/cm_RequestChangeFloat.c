

void __cdecl cm_EnqueueClientPacket(void*);

/* ADDRESS: GOLDDE 0x004b2e40 */
void __cdecl cm_RequestChangeFloat(int entity_id, int offset, int delta)
{
	char buf[0x9c];

	buf[0] = 0x1a;
	*(int*) (buf + 0x10) = entity_id;
	*(int*) (buf + 0x14) = offset;
	*(int*) (buf + 0x18) = delta;
	cm_EnqueueClientPacket(buf);
}
