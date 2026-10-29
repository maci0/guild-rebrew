int __cdecl fcn_005373e0(void*, const char*);
int __cdecl fcn_005338d0(const char*, int, int);
void __cdecl fcn_0059fe60(int);
extern int g_14abc58;
extern int g_7746a0;

/* ADDRESS: GOLDTL 0x005a0250 */
void __cdecl fcn_005a0250(int arg)
{
	int status;
	int value;

	status = fcn_005373e0((void*) fcn_005a0250, (const char*) 0x67fff);
	if (status == 0) {
		return;
	}
	while (status != 0) {
		value = fcn_005338d0((const char*) 0x6aa7f8, g_14abc58, 0x16);
		if (g_7746a0 != 0 && g_7746a0 == value) {
			fcn_0059fe60(arg);
		}
		status = fcn_005373e0((void*) fcn_005a0250, (const char*) 0x67fff);
	}
}
