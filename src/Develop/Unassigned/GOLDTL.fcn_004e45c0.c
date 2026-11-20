


extern int g_772f3c;

int __cdecl fcn_005373e0(int, int);
int __cdecl evt_FindScriptById(int);

void __cdecl fcn_004e45c0(int a1)
{
	if (g_772f3c == 0 && fcn_005373e0(0, 0x79706) != 0) {
		while (evt_FindScriptById(a1) != 0 && fcn_005373e0(0, 0x79706) != 0) {
		}
	}
}
