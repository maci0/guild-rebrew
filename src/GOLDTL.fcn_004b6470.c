extern int g_14cbca0;
extern unsigned short g_774970;
extern int g_6a3760;
extern char g_7f4ca0[];

int __cdecl fcn_004b60c0(void);
int __cdecl fcn_004b62c0(void);
int __cdecl fcn_004b62e0(void);

// FUNCTION: GOLDTL 0x4b6470
// SIZE: 57

int __cdecl fcn_004b6470(void)
{
	if (g_14cbca0 != -1) {
		if (*(int*) (g_7f4ca0 + g_774970 * 540 + 4) == g_6a3760)
			return fcn_004b60c0();
		return fcn_004b62c0();
	}
	return fcn_004b62e0();
}
