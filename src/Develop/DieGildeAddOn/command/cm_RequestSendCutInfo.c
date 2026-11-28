


extern volatile int gm_GameTicks;
extern char g_68ae34[];

int __cdecl sprintf(char*, const char*, ...);
int __cdecl cm_EnqueueClientPacket(void*);

/* ADDRESS: GOLDDE 0x004b32d0 */
int __cdecl cm_RequestSendCutInfo(int a1, int a2)
{
	char buf[0x19c];

	buf[0] = 0x26;
	*(int*) (buf + 0x10) = a1;
	*(int*) (buf + 0x14) = a2;
	sprintf(buf + 0x9c, g_68ae34, a1, gm_GameTicks);
	return cm_EnqueueClientPacket(buf);
}
