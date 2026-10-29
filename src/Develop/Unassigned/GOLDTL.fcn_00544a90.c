

#include <windows.h>

typedef unsigned int (__cdecl* CheckProc)(void);

#pragma optimize("", off)
int __cdecl fcn_00544a90(void)
{
	HMODULE hmod;
	CheckProc proc;
	int t;
	unsigned int u;
	char libname[0x40];
	char entryname[0x40];
	int j;
	int k;
	int m;
	int n;

	t = 0;
	strcpy(libname, "math64.dll");
	hmod = LoadLibraryA(libname);
	if (hmod != 0) {
		strcpy(entryname, "_Rainier@0");
		proc = (CheckProc) GetProcAddress(hmod, entryname);
		if (proc == 0) {
			FreeLibrary(hmod);
			return -1;
		}
		k = 0x65;
		m = 0xf9e;
		n = 0;
		j = 0x3e7;
		u = proc();
		u = u * 3;
		if (u > 0x7d0) {
			n = k + 1;
		}
		for (t = 1; t <= 10; t++) {
			j = j + k - 1;
		}
		n = n + j;
		j = j + m;
		j = j + 0x10;
		if (u + 0x14 - j != 10) {
			return -1;
		}
		FreeLibrary(hmod);
	} else {
		MessageBoxA(0, "Es ist ein LoadLibrary-Fehler aufgetreten. Bitte beenden sie alle Antiviren-Programme und starten sie Die Gilde Gold-Edition erneut.", "Fehler", 0x40);
		return -1;
	}
	return 0;
}
#pragma optimize("", on)
