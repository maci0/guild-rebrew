// FUNCTION: GOLD 0x4dff80
// FUNCTION: GOLDTL 0x4e1890

extern int g_772f2c;

unsigned int __cdecl fcn_004e6cb0(unsigned int);

void __cdecl fcn_004e1890(char* x)
{
	int r;

	if (g_772f2c == 0) {
		if (fcn_004e6cb0(10) > 7)
			x[0x94] = 1;
		else
			x[0x94] = 0;
	} else {
		r = fcn_004e6cb0(100);
		if (r > 50)
			x[0x94] = 4;
		else if (r > 15)
			x[0x94] = 2;
		else
			x[0x94] = 3;
	}
}
