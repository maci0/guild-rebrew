extern unsigned char* g_868050;
// FUNCTION: GOLD 0x00502060
// SIZE: 61
// FUNCTION: GOLDTL 0x00504eb0
// SIZE: 61

int __cdecl fcn_0065f220(const char*, const char*);

int __cdecl fcn_00504eb0(const char* name)
{
	int i;

	for (i = 0; i < 0x58; i++) {
		if (fcn_0065f220(name, ((char*)g_868050) + i * 0x24d + 1) == 0) {
			return i;
		}
	}
	return 0;
}
