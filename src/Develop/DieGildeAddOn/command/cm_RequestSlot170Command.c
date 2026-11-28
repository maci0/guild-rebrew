


void __cdecl cm_EnqueueClientPacket(void*);

/* ADDRESS: GOLDDE 0x004b45b0 */
void __cdecl cm_RequestSlot170Command(int* values)
{
	char buf[0x9c];

	buf[0] = 0x66;
	*(int*) (buf + 0x10) = values[0];
	*(int*) (buf + 0x14) = values[1];
	cm_EnqueueClientPacket(buf);
}
