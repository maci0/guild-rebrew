


extern int cut_SkipMode;

int __cdecl main_RunFrameLoop(int, int);
int __cdecl evt_FindScriptById(int);

void __cdecl cut_WaitForScriptExit(int script_id)
{
	if (cut_SkipMode == 0 && main_RunFrameLoop(0, 0x79706) != 0) {
		while (evt_FindScriptById(script_id) != 0 && main_RunFrameLoop(0, 0x79706) != 0) {
		}
	}
}
