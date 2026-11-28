


void __cdecl cm_EnqueueClientPacket(void*);

void __cdecl fcn_0064d530(void*, int, int);

/* ADDRESS: GOLDDE 0x004b2900 */
void __cdecl cm_SendTraceEnd(int source)
{
	char buf[0x9c];

	buf[0] = 6;
	fcn_0064d530(buf + 0x10, source, 0x80);
	cm_EnqueueClientPacket(buf);
}
