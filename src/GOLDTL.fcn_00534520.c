extern short g_14ce8c0;
extern short g_14ce8c2;
extern int g_1042570;
extern int g_1042574;
extern int g_1042578;
extern int g_104257c;
extern int g_7e4300;
extern int g_7e4304;
extern int g_7e4308;
extern int g_7e430c;
extern int g_7e4310;

// FUNCTION: GOLD 0x52ee80
// FUNCTION: GOLDTL 0x534520

#define MAX_(a, b) ((a) > (b) ? (a) : (b))
#define MIN_(a, b) ((a) < (b) ? (a) : (b))

void __cdecl fcn_00534520(void)
{
	int a;
	int b;

	a = MIN_(MAX_(g_1042570, g_14ce8c0), g_1042578 - 1);
	b = MIN_(MAX_(g_1042574, g_14ce8c2), g_104257c - 1);
	g_7e4304 = a;
	g_7e430c = a;
	g_7e4300 = 1;
	g_7e4308 = b;
	g_7e4310 = b;
}
