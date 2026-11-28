

int __cdecl main_RunRainierProtectionCheck(void);
void __stdcall fcn_0064e66a(int);

int __cdecl main_VerifyMath64Protection(void)
{
	if (main_RunRainierProtectionCheck() != 0) {
		fcn_0064e66a(-1);
	}
	return 0;
}
