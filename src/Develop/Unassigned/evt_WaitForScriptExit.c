extern int main_LoopFlags;



char* __cdecl evt_FindScriptById(int);
void __cdecl main_RunFrameLoop(int, unsigned int);

void __cdecl evt_WaitForScriptExit(int script_id)
{
	unsigned int fl;
	char* script;

	fl = ((*(unsigned int*)&main_LoopFlags) & 0xffffff3f) | 0x100200;
	for (script = evt_FindScriptById(script_id); script != 0 && (script[0x124] & 1) != 0; script = evt_FindScriptById(script_id)) {
		main_RunFrameLoop(0, fl);
	}
}
