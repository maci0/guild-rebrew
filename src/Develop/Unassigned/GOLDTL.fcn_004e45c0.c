


extern int g_772f3c;

int __cdecl main_RunFrameLoop(int, int);
int __cdecl evt_FindScriptById(int);

void __cdecl fcn_004e45c0(int a1)
{
	if (g_772f3c == 0 && main_RunFrameLoop(0, 0x79706) != 0) {
		while (evt_FindScriptById(a1) != 0 && main_RunFrameLoop(0, 0x79706) != 0) {
		}
	}
}
