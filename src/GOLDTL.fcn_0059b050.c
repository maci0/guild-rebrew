// GLOBAL: GOLDTL 0x7746a0
extern int g_7746a0;
// GLOBAL: GOLD 0x6f22e4
extern int g_7746a0;
// FUNCTION: GOLD 0x00592310
// FUNCTION: GOLDTL 0x59b050

int __cdecl fcn_005373e0(void*, int);
int __cdecl fcn_0065f220(void*, int);
void __cdecl fcn_0059aa10(int, int);

void __cdecl fcn_0059b050(int a)
{
	while (fcn_005373e0(fcn_0059b050, 0x67fff)) {
		if (g_7746a0 != 0 && fcn_0065f220((void*) "UPGRADE", g_7746a0) == 0) {
			fcn_0059aa10(a, 0x2c);
		}
	}
}
