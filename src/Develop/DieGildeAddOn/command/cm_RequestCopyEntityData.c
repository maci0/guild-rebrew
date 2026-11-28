extern float ai_DifficultyFactor;
extern float ai_DifficultyRate;



void __cdecl cm_EnqueueClientPacket(void*);

/* ADDRESS: GOLDDE 0x004b2e80 */
void __cdecl cm_RequestCopyEntityData(int targetId, int sourceId, int value, int mode)
{
	char buf[0x9c];

	buf[0] = 0x1b;
	*(int*) (buf + 0x10) = targetId;
	*(int*) (buf + 0x14) = sourceId;
	*(int*) (buf + 0x18) = value;
	*(int*) (buf + 0x1c) = mode;
	*(int*) (buf + 0x20) = (*(int*)&ai_DifficultyRate);
	*(int*) (buf + 0x24) = (int) ai_DifficultyFactor;
	cm_EnqueueClientPacket(buf);
}
