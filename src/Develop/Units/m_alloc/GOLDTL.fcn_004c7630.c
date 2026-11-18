char g_68aec4[] = "cm_LoadBuf";
extern unsigned int g_aed328;
extern char* cm_LoadBuf;
extern unsigned int g_1005820;



int __cdecl m_alloc(int, char*);

int __cdecl fcn_004c7630(void* packet, char* reply)
{
	int n;

	n = *(int*) ((char*) packet + 0x10);
	g_aed328 = n;
	cm_LoadBuf = (char*) m_alloc(n, g_68aec4);
	g_1005820 = 0;
	if (reply != 0) {
		*reply = 1;
	}
	return 0;
}
