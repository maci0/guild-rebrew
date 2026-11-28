#include <stdio.h>
#include <string.h>

// SIZE 0x84
struct log_428230 {
	int shown;
	char text[0x80];
};

extern int g_6b7eb0;
extern void* evt_ScriptErrorLog;

int __cdecl evt_ParseScript(char*);
void __cdecl evt_FreeScript(char*);
int __cdecl evt_FindDefinition(char*, const char*);
void __cdecl evt_LogScriptError(char*, int, const char*);
void __cdecl evt_EnterFunction(char*, int);


/* Starts a loaded script at its main entry point and logs the start. */
/* ADDRESS: GOLDTL 0x00428230 */
int __cdecl evt_RunScript(char* script)
{
	int entry;
	char msg[0x200];

	if (script == 0) {
		return 0;
	}
	if (evt_ParseScript(script) == 0) {
		evt_FreeScript(script);
		return 0;
	}
	entry = evt_FindDefinition(script, "main");
	if (entry == 0) {
		evt_LogScriptError(script, entry, "evt_RunScript:No entrypoint(main) found in script...");
		return 0;
	}
	evt_EnterFunction(script, entry);
	*(int*) (script + 0x124) |= 1;
	*(int*) (script + 0xc84) = 0;
	*(char**) (script + 0xc28) = script + 0x128;
	sprintf(msg, "Run script: %s", script);
	strncpy(((struct log_428230*)evt_ScriptErrorLog)[g_6b7eb0].text, msg, 0x7f);
	((struct log_428230*)evt_ScriptErrorLog)[g_6b7eb0].shown = 0;
	g_6b7eb0++;
	if (g_6b7eb0 > 0x1e) {
		g_6b7eb0 = 0;
	}
	return 1;
}
