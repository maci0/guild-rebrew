int __cdecl fcn_00426fd0(const char* name);
int __cdecl evt_RunScript(char* script);

/* ADDRESS: GOLDTL 0x0040cfb0 */

/* Task callback for PlayCharacterAniScript(): loads the script named in the
 * task, runs it, and passes the task parameter to it. */
void __cdecl fcn_0040cfb0(char* task)
{
	char* script;

	script = (char*) fcn_00426fd0(task + 0x90);
	if (script != 0) {
		evt_RunScript(script);
		*(int*) (script + 0x104) = *(int*) (task + 0x17c);
	}
}
