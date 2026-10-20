/* Reads one network packet fragment into the receive buffer. */

extern int g_14cbca0;
extern char* g_14cbca4;
extern unsigned short g_14cbcac;
extern int g_6b7d54;
extern int g_14cbc84;

extern int (__stdcall* g_662384)(unsigned int s, char* buf, int len, int flags);
extern int (__stdcall* g_662364)(void);

void __cdecl fcn_00421050(void);
void __cdecl fcn_004208a0(int err);
void __cdecl fcn_0064d41a(char* buf, char* fmt, int a, int b);
void __cdecl fcn_00420ba0(char* buf, int len, int flag);

/* ADDRESS: GOLDTL 0x004210a0 */
int __cdecl nt_Recv(void)
{
	char buf[256];
	int n;
	int err;

	if (g_14cbca0 == -1) {
		return 1;
	}
	if (g_14cbca4 == 0) {
		return 0;
	}
	if (g_14cbcac < 3) {
		n = g_662384(g_14cbca0, g_14cbca4 + (g_14cbcac & 0xffff),
		             3 - (g_14cbcac & 0xffff), 0);
		if (n == 0) {
			fcn_00421050();
			return 1;
		}
		if (n == -1) {
			goto got_error;
		}
		g_6b7d54 += n;
		g_14cbcac = g_14cbcac + n;
		if (g_14cbcac < 3) {
			return 0;
		}
	}
	n = g_662384(g_14cbca0, g_14cbca4 + (g_14cbcac & 0xffff),
	             *(unsigned short*) (g_14cbca4 + 1) - (g_14cbcac & 0xffff), 0);
	if (n == 0) {
		fcn_00421050();
		return 1;
	}
	if (n == -1) {
got_error:
		err = g_662364();
		if (err == 0x2733) {
			return 0;
		}
		fcn_004208a0(err);
		fcn_00421050();
		return 1;
	}
	g_6b7d54 += n;
	g_14cbcac = g_14cbcac + n;
	if (g_14cbcac != *(unsigned short*) (g_14cbca4 + 1)) {
		return 0;
	}
	if (*(int*) (g_14cbca4 + 4) == -1) {
		fcn_00420ba0(g_14cbca4, g_14cbcac & 0xffff, 1);
		g_14cbca4 = 0;
		g_14cbcac = 0;
		return 0;
	}
	n = *(int*) (g_14cbca4 + 8);
	if (n != g_14cbc84 + 1) {
		if (n == *(int*) 0xaecde0) {
			fcn_0064d41a(buf, (char*) 0x678ba0, n, g_14cbc84);
			goto purge;
		}
		if (*(unsigned char*) g_14cbca4 == ' ' &&
		    *(unsigned char*) (g_14cbca4 + 0x10) == 0x0e) {
			fcn_0064d41a(buf, (char*) 0x678b60, n, g_14cbc84);
			goto purge;
		}
		fcn_0064d41a(buf, (char*) 0x678b18, n, g_14cbc84);
	}
	g_14cbc84 = n;
purge:
	fcn_00420ba0(g_14cbca4, g_14cbcac & 0xffff, 1);
	g_14cbca4 = 0;
	g_14cbcac = 0;
	return 0;
}
