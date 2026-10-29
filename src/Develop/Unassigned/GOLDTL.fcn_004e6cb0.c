


extern unsigned int g_9b0820;
extern char g_68d6d0[];

int __cdecl fcn_0064d41a(char*, char*, ...);

unsigned int __cdecl fcn_004e6cb0(unsigned int n)
{
	char buf[0x40];

	if (n == 0)
		return 0;
	g_9b0820 = g_9b0820 * 0x41c64e6d + 0x3039;
	fcn_0064d41a(buf, g_68d6d0, ((unsigned short*) &g_9b0820)[1] % 0x7fffu);
	return ((unsigned short*) &g_9b0820)[1] % 0x7fffu % n;
}
unsigned char _dpad_9afde4[2620];
