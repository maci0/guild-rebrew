// FUNCTION: GOLDTL 0x005259f0
// SIZE: 332

#include <windows.h>

extern char g_6a24d0[];
extern int g_6b7fdc;
extern int g_1005760;

void* __cdecl fcn_0042ff50(char*, char*, int);
void __cdecl fcn_00430a80(void*, int, int);
int __cdecl fcn_00430c50(void*);
char* __cdecl fcn_0041db70(int, char*);
void __cdecl CloseVfsStream(void*);
int __cdecl vfs_ReadData(char*, int, int, void*);
void __cdecl fcn_0041ddd0(char*);
void __cdecl fcn_004c4e40(int);
int __cdecl fcn_004c4e70(char*);
void __cdecl fcn_005356e0(void);
void __cdecl fcn_00535960(void);

int __cdecl fcn_005259f0(char* path)
{
	int n;
	void* h;
	int size;
	int total;
	char* buf;
	char* p;
	int sent;

	n = 0;
	h = fcn_0042ff50(path, g_6a24d0, g_6b7fdc);
	if (h == 0) {
		return 0;
	}
	fcn_00430a80(h, 0, 2);
	size = fcn_00430c50(h);
	total = (size / 128 + 1) * 128;
	fcn_00430a80(h, 0, 0);
	buf = fcn_0041db70(total, "ls_SendGame");
	if (buf == 0) {
		CloseVfsStream(h);
		return 0;
	}
	if (vfs_ReadData(buf, size, 1, h) == -1) {
		fcn_0041ddd0(buf);
		CloseVfsStream(h);
		return 0;
	}
	fcn_004c4e40(total);
	p = buf;
	sent = 0;
	while (sent < total) {
		if (fcn_004c4e70(p) != -1) {
			p += 0x80;
			sent += 0x80;
			if (n++ % 16 == 0) {
				Sleep(15);
			}
		}
		fcn_005356e0();
		fcn_00535960();
	}
	while (g_1005760 != 0) {
		fcn_005356e0();
		fcn_00535960();
	}
	fcn_0041ddd0(buf);
	CloseVfsStream(h);
	return 1;
}
