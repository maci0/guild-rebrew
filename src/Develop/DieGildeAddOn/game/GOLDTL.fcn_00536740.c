extern char g_14cf736;
extern int g_14ce8d8;
extern int g_14ce8e0;
extern short g_7725c4;
extern char* g_7746b4;
extern int g_7ea360;
extern int g_67a370;
extern int g_100f1e8;
extern int g_100f1ec;



void __cdecl fcn_004cf180(void);
void __cdecl fcn_004234e0(int, char*, int, int, int, int, int);
void __cdecl fcn_00536640(int);
char __cdecl fcn_0045bad0(int, int, int, int*, int*);
char __cdecl fcn_0045b920(int, int, int, char*);
void __cdecl fcn_004cf110(char*);
void __cdecl fcn_00412830(int);

void __cdecl fcn_00536740(void)
{
	int a;
	int b;
	char buf[16];
	int p;

	fcn_004cf180();
	if (g_14cf736 != 0) {
		g_7725c4 = 0x21;
		if (g_14ce8d8 != 0) {
			fcn_004234e0(0, "schuss_s", 1, 0x3f, 0x7f, 0, 0);
			if ((*(int*)&g_7746b4) != 0) {
				fcn_00536640((*(int*)&g_7746b4));
			}
			g_7ea360 = 0;
		}
		if (g_14ce8e0 != 0) {
			p = *(int*) (((char*)g_67a370) + 0xb0);
			if (fcn_0045bad0(p, g_100f1e8, g_100f1ec, &b, &a) != 0 &&
			    fcn_0045b920(p, b, a, buf) != 0) {
				fcn_004cf110(buf);
			}
			fcn_00412830(0x10);
		}
	}
}
