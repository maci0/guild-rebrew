

extern int g_14ce8e0;
extern int g_774654;

void __cdecl fcn_00535570(void);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00535630(void);
void __cdecl fcn_005355f0(void);

void __cdecl fcn_005b4460(void)
{
	fcn_00535570();
	while (fcn_005373e0(fcn_005b4460, 0x657c7) != 0) {
		fcn_00535630();
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
	}
	fcn_005355f0();
}
