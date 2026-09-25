extern unsigned int g_9b0820;
extern char g_68d6dc[];

int __cdecl fcn_0064d41a(char*, char*, ...);

// FUNCTION: GOLD 0x004e5360
// SIZE: 127
// FUNCTION: GOLDTL 0x4e6d20
// SIZE: 127

float __cdecl fcn_004e6d20(void)
{
	char buf[0x40];

	g_9b0820 = g_9b0820 * 0x41c64e6d + 0x3039;
	fcn_0064d41a(buf, g_68d6dc, ((unsigned short*) &g_9b0820)[1] % 0x7fffu * (1.0f / 32767.0f));
	return ((unsigned short*) &g_9b0820)[1] % 0x7fffu * (1.0f / 32767.0f);
}
