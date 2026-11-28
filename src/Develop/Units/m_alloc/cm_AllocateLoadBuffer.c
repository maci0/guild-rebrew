char str_cm_LoadBuf[] = "cm_LoadBuf";
extern unsigned int g_aed328;
extern char* cm_LoadBuf;
extern unsigned int cm_LoadBufOffset;



int __cdecl m_alloc(int, char*);

/* ADDRESS: GOLDDE 0x004b4e10 */
int __cdecl cm_AllocateLoadBuffer(void* packet, char* reply)
{
	int n;

	n = *(int*) ((char*) packet + 0x10);
	g_aed328 = n;
	cm_LoadBuf = (char*) m_alloc(n, str_cm_LoadBuf);
	cm_LoadBufOffset = 0;
	if (reply != 0) {
		*reply = 1;
	}
	return 0;
}
