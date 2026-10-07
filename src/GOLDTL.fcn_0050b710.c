// FUNCTION: GOLD 0x005085b0
// FUNCTION: GOLDTL 0x0050b710

extern char g_8680b4[];
extern int g_6995bc[];

int __cdecl fcn_0050b710(int a, unsigned char k)
{
	return (int) ((float) a / g_6995bc[*(unsigned short*) (g_8680b4 + k * 0x2f4)] + 0.5);
}
