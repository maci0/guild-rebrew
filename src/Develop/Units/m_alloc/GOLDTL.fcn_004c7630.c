char g_68aec4[] = "cm_LoadBuf";
extern unsigned int g_aed328;
extern char* cm_LoadBuf;
extern unsigned int g_1005820;



int __cdecl m_alloc(int, char*);

int __cdecl fcn_004c7630(void* a1, char* a2)
{
	int n;

	n = *(int*) ((char*) a1 + 0x10);
	g_aed328 = n;
	cm_LoadBuf = (char*) m_alloc(n, g_68aec4);
	g_1005820 = 0;
	if (a2 != 0) {
		*a2 = 1;
	}
	return 0;
}
