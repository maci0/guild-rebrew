extern int g_7746a0;
extern int g_7746a0;



int __cdecl fcn_005373e0(void*, int);
int __cdecl fcn_0065f220(void*, int);
void __cdecl d2_RunTechTreeDialog(int, int);

void __cdecl fcn_0059b050(int a)
{
	while (fcn_005373e0(fcn_0059b050, 0x67fff)) {
		if (g_7746a0 != 0 && fcn_0065f220((void*) "UPGRADE", g_7746a0) == 0) {
			d2_RunTechTreeDialog(a, 0x2c);
		}
	}
}
