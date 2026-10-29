


extern int g_14cbca0;
extern char* g_14cbca4;
extern int g_772e80;
extern char g_1005780;

void __cdecl nt_Recv(void);
int __cdecl fcn_004c49f0(char*);

int __cdecl fcn_004c4940(void)
{
	if (g_14cbca0 == -1) {
		return 0;
	}
	if (g_14cbca4 != 0) {
		nt_Recv();
		if (g_14cbca4 != 0) {
			return 0;
		}
	}
	do {
		g_772e80++;
		if (fcn_004c49f0(((char*)&g_1005780)) != 0) {
			return 1;
		}
		g_14cbca4 = ((char*)&g_1005780);
		nt_Recv();
	} while (g_14cbca4 == 0);
	return 0;
}
