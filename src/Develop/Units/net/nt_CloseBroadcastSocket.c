extern int g_675170;

extern int (__stdcall *g_66234c)(int);

void __cdecl nt_CloseBroadcastSocket(void)
{
	int h;

	h = g_675170;
	if (h != -1) {
		g_66234c(h);
		g_675170 = -1;
	}
}
