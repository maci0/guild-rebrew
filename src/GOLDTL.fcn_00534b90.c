extern int g_7e4300;
extern int g_7e4304;
extern int g_7e4308;
extern int g_7e430c;
extern int g_7e4310;



void __cdecl fcn_0041b5b0(void);
void __cdecl fcn_0041b5f0(int, int, int, int, int);
void __cdecl fcn_0041b700(void);

void __cdecl fcn_00534b90(void)
{
	if (g_7e4300 != 0) {
		fcn_0041b5b0();
		fcn_0041b5f0(g_7e4304, g_7e4308, g_7e430c, g_7e4308, -1);
		fcn_0041b5f0(g_7e430c, g_7e4308, g_7e430c, g_7e4310 + 1, -1);
		fcn_0041b5f0(g_7e430c, g_7e4310, g_7e4304, g_7e4310, -1);
		fcn_0041b5f0(g_7e4304, g_7e4310, g_7e4304, g_7e4308, -1);
		fcn_0041b700();
	}
}
