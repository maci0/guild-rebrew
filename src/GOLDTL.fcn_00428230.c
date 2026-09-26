#include <stdio.h>
#include <string.h>

// SIZE 0x84
struct log_428230 {
	int shown;
	char text[0x80];
};

extern int g_6b7eb0;
extern void* g_14cb8f0;

int __cdecl fcn_00427f00(char*);
void __cdecl fcn_00429d30(char*);
int __cdecl fcn_004262b0(char*, const char*);
void __cdecl fcn_00425bf0(char*, int, const char*);
void __cdecl fcn_00427c40(char*, int);

// FUNCTION: GOLD 0x004299a0
// SIZE: 265
// FUNCTION: GOLDTL 0x428230
// SIZE: 265

/* Starts a loaded script at its main entry point and logs the start. */
int __cdecl fcn_00428230(char* script)
{
	int entry;
	char msg[0x200];

	if (script == 0) {
		return 0;
	}
	if (fcn_00427f00(script) == 0) {
		fcn_00429d30(script);
		return 0;
	}
	entry = fcn_004262b0(script, "main");
	if (entry == 0) {
		fcn_00425bf0(script, entry, "evt_RunScript:No entrypoint(main) found in script...");
		return 0;
	}
	fcn_00427c40(script, entry);
	*(int*) (script + 0x124) |= 1;
	*(int*) (script + 0xc84) = 0;
	*(char**) (script + 0xc28) = script + 0x128;
	sprintf(msg, "Run script: %s", script);
	strncpy(((struct log_428230*)g_14cb8f0)[g_6b7eb0].text, msg, 0x7f);
	((struct log_428230*)g_14cb8f0)[g_6b7eb0].shown = 0;
	g_6b7eb0++;
	if (g_6b7eb0 > 0x1e) {
		g_6b7eb0 = 0;
	}
	return 1;
}
