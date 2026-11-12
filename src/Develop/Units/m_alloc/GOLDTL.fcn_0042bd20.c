#include <string.h>

extern char g_6b5c60[];
extern char g_1052f00[];
extern int g_1052de0;
extern int g_6b7f98;
extern void* g_6b7fa0;

char* __cdecl fcn_0064d1a0(char*, int);
char* __cdecl fcn_0064e790(char*, int);
char* __cdecl fcn_0064e2f9(char*, char*);
int __cdecl fcn_0064e1fd(char*);
char* __cdecl fgets(char*, int, char*);
void __cdecl fcn_0064d710(void);
void __cdecl m_FreeTracked(void*);
int __cdecl txt_loadTextFile(char*);
int __stdcall MessageBoxA(void*, char*, char*, int);

/* ADDRESS: GOLDTL 0x0042bd20 */
int __cdecl fcn_0042bd20(char* path)
{
	char* p;
	char* inc;
	char line[0xc8];
	char names[0x80][0x200];
	char* f;
	char* q;
	char* r;
	int n;
	int i;
	int len;

	g_6b7f98 = 0;
	p = fcn_0064d1a0(path, '\\');
	if (p) {
		len = (int) (p - path) + 1;
		memcpy(g_1052f00, path, len);
		g_1052f00[len] = 0;
	} else {
		g_1052f00[0] = g_6b5c60[0];
	}
	f = fcn_0064e2f9(path, "rt");
	n = 0;
	if (!f) {
		MessageBoxA(0, "Could not open Textfiledefinition!", "Error", 0x30);
		m_FreeTracked(g_6b7fa0);
		g_6b7fa0 = 0;
		return 0;
	}
	do {
		memset(line, 0, 0xc8);
		fgets(line, 0xc8, f);
		if (!strstr(line, "//")) {
			inc = strstr(line, "#include");
			if (inc) {
				p = fcn_0064e790(inc, '"');
				if (!p)
					{ m_FreeTracked(g_6b7fa0); g_6b7fa0 = 0; return 0; }
				p++; q = fcn_0064e790(p, '"');
				if (!q)
					{ m_FreeTracked(g_6b7fa0); g_6b7fa0 = 0; return 0; }
				*q = 0;
				r = fcn_0064d1a0(p, '.');
				*r = 0;
				strcpy(names[n], p);
				n++;
				if (n > 0x80)
					{ m_FreeTracked(g_6b7fa0); g_6b7fa0 = 0; return 0; }
			}
		}
	} while (!(f[0xc] & 0x10));
	fcn_0064e1fd(f);
	for (i = 0; i < n; i++) {
		if (!txt_loadTextFile(names[i]))
			return 0;
	}
	g_1052de0 = 1;
	return 1;




}
