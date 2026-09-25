// FUNCTION: GOLDTL 0x005e3fa0
// SIZE: 182

extern unsigned short g_7ea3c0[];
extern int g_6b7fdc;
extern char g_6750e8[];
extern char g_6a23b0[];

int __cdecl fcn_0042ff50(char*, char*, int);
unsigned char* __cdecl fcn_0041db70(int, char*);
int __cdecl ls_ReadVfsDataChecked(void*, int, int, int);
unsigned short __cdecl fcn_0041bac0(unsigned char, unsigned char, unsigned char);
void __cdecl fcn_0041ddd0(void*);
void __cdecl CloseVfsStream(int);

void __cdecl fcn_005e3fa0(char* name)
{
	int fh;
	unsigned char* buf;
	int n;
	int x;
	int y;

	n = 0;
	fh = fcn_0042ff50(name, g_6750e8, g_6b7fdc);
	if (fh != 0) {
		buf = fcn_0041db70(0xe100, g_6a23b0);
		ls_ReadVfsDataChecked(buf, 0xe100, 1, fh);
		for (y = 0; y < 120; y++) {
			for (x = 0; x < 160; x++) {
				g_7ea3c0[n] = fcn_0041bac0(buf[n * 3], buf[n * 3 + 1], buf[n * 3 + 2]);
				n++;
			}
		}
		if (buf != 0) {
			fcn_0041ddd0(buf);
		}
		CloseVfsStream(fh);
	}
}
