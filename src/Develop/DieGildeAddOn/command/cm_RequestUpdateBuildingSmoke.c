


void __cdecl cm_EnqueueClientPacket(void*);

/* ADDRESS: GOLDDE 0x004b3bc0 */
void __cdecl cm_RequestUpdateBuildingSmoke(int building_id)
{
	char buf[0x9c];

	buf[0] = 0x42;
	*(int*) (buf + 0x10) = building_id;
	cm_EnqueueClientPacket(buf);
}
