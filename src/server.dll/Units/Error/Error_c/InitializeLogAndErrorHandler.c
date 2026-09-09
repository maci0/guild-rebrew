/* Initializes the log/error handler: stores the module/severity
 * settings, installs the crash-dump filter, resolves the log file
 * directory, and installs per-level log file handles. */

// FUNCTION: SERVER 0x10003320
// InitializeLogAndErrorHandler
// SIZE: 404

#include <windows.h>

extern int g_10034610;
extern int g_10034614;
extern int g_10034618;
extern char g_1003461c;
extern int g_117660e0;
extern int g_11766204;
extern int __cdecl sprintf(char* buf, const char* fmt, ...);
extern int __cdecl fcn_1001a567(int);
extern char* __cdecl fcn_1001a527(char*);
extern char* __cdecl fcn_1001a286(char* buf, const char* mode);
extern int __cdecl fcn_1001a46e(char* f, int a, int b);
extern int __cdecl fcn_1001a2eb(char* f);
extern int __cdecl fcn_1001a18a(char* f);
extern int __cdecl fcn_1001a207(const char* msg, char* f);
extern char* __cdecl fcn_1001a540(const char* s, int c);
extern void __cdecl fcn_10002640(char* msg, int flags, int severity);

void __cdecl InitializeLogAndErrorHandler(int a, int b, unsigned int c, unsigned int d)
{
	int h;
	char buf[0x104]; /* target frame: h@0, buf@4..0x108, path@0x108 */
	char path[0x100];
	char* f;
	char* sp;

	g_10034610 = a;
	g_10034618 = d;
	g_10034614 = b;
	g_117660e0 = c;
	g_1003461c = (d >> 4) & 1;
	SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER) 0x10002770);
	h = fcn_1001a567(0);
	GetWindowTextA((HWND) c, path, 0x100);
	((void (__stdcall*)(int, const char*, int)) *(void**) 0x1002403c)(0, (const char*) 0x11766100, 0x104);
	*fcn_1001a540((char*) 0x11766100, 0x5c) = 0;
	sprintf((char*) 0x117640e0, (char*) 0x1002735c, path, fcn_1001a527((char*) &h));
	if (g_10034618 & 1) {
		sp = (char*) 0x10027084;
		do {
			sprintf(buf, (char*) 0x100270fc, (char*) 0x11766100, sp);
			f = fcn_1001a286(buf, "at");
			if (f != 0) {
				fcn_1001a46e(f, 0, 2);
				if (fcn_1001a2eb(f) > 0x10000) {
					fcn_1001a18a(f);
					f = fcn_1001a286(buf, "wt");
					fcn_1001a207((char*) 0x1002733c, f);
				}
				fcn_1001a18a(f);
			}
			sp += 0x20;
		} while ((int) sp < 0x100270e4);
	}
	if (g_10034618 & 8) {
		((void (__stdcall*)(void)) *(void**) 0x10024048)();
		g_11766204 = ((int (__stdcall*)(int)) *(void**) 0x10024044)(-0xb);
	}
	sp = (char*) 0x10027078;
	do {
		fcn_10002640((char*) 0x117640e0, g_10034618, *(int*) sp);
		sp += 4;
	} while ((int) sp < 0x10027084);
}
