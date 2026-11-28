


void __cdecl cm_EnqueueClientPacket(void*);

/* ADDRESS: GOLDDE 0x004b3860 */
void __cdecl cm_SendSetGebUpgrade(int building_id)
{
	char buf[0x9c];

	buf[0] = 0x3a;
	*(int*) (buf + 0x10) = building_id;
	cm_EnqueueClientPacket(buf);
}
