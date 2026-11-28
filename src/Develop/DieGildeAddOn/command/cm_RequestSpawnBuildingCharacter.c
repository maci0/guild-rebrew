


void __cdecl cm_EnqueueClientPacket(void*);

/* ADDRESS: GOLDDE 0x004b3620 */
void __cdecl cm_RequestSpawnBuildingCharacter(int id, int type, int sub)
{
	char buf[0x9c];

	buf[0] = 0x34;
	*(int*) (buf + 0x10) = id;
	*(int*) (buf + 0x14) = type;
	*(int*) (buf + 0x18) = sub;
	cm_EnqueueClientPacket(buf);
}
