// FUNCTION: GOLDTL 0x005e3ed0

extern unsigned short g_7ea3c0[];
extern int g_6b7fdc;
extern char g_6790b0[];
extern char g_6a23b0[];

void __cdecl fcn_00469e30(int);
void __cdecl fcn_005e3d20(void);
int __cdecl fcn_0042ff50(char*, char*, int);
unsigned char* __cdecl fcn_0041db70(int, char*);
void __cdecl fcn_0041bb70(int, unsigned char*, unsigned char*, unsigned char*);
int __cdecl fcn_00430910(void*, int, int, int);
void __cdecl m_FreeTracked(void*);
void __cdecl CloseVfsStream(int);

void __cdecl fcn_005e3ed0(int a1, char* name)
{
	int fh;
	unsigned char* buf;
	int n;
	int x;
	int y;

	n = 0;
	fcn_00469e30(a1);
	fcn_005e3d20();
	fh = fcn_0042ff50(name, g_6790b0, g_6b7fdc);
	if (fh != 0) {
		buf = fcn_0041db70(0xe100, g_6a23b0);
		for (y = 0; y < 120; y++) {
			for (x = 0; x < 160; x++) {
				fcn_0041bb70(g_7ea3c0[n], &buf[n * 3], &buf[n * 3 + 1], &buf[n * 3 + 2]);
				n++;
			}
		}
		fcn_00430910(buf, 0xe100, 1, fh);
		if (buf != 0) {
			m_FreeTracked(buf);
		}
		CloseVfsStream(fh);
	}
}
